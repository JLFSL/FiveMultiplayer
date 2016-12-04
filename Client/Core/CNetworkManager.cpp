#include "stdafx.h"

CNetworkManager::CNetworkManager()
{
	// Get RakPeerInterface
	g_RakPeer = RakPeerInterface::GetInstance();

	// Get RPC4
	g_RPC = RPC4::GetInstance();

	// Attach RPC4 to RakPeerInterface
	g_RakPeer->AttachPlugin(g_RPC);

	// RakPeerInterface Settings
	g_RakPeer->SetSplitMessageProgressInterval(100);

	Logger::Msg("CNetworkManager::Constructed");

	g_ConnectionState = CONSTATE_DISC;
}


CNetworkManager::~CNetworkManager()
{
	// Stop RakNet, stops synchronization
	g_RakPeer->Shutdown(2000);

	// Detach RPC4 from RakPeerInterface
	g_RakPeer->DetachPlugin(g_RPC);

	// Destroy RPC4
	RPC4::DestroyInstance(g_RPC);

	// Destroy RakPeerInterface
	RakPeerInterface::DestroyInstance(g_RakPeer);

	Logger::Msg("CNetworkManager::Deconstructed");
}

bool CNetworkManager::Start()
{
	Logger::Msg("CNetworkManager::Started");

	// Return whether Startup worked or not
	return (g_RakPeer->Startup(1, &SocketDescriptor(), 1, THREAD_PRIORITY_NORMAL) == RAKNET_STARTED);
}

void CNetworkManager::Stop()
{
	// Disconnect if we're connected
	if (g_ConnectionState == CONSTATE_COND)
		Disconnect();

	// Stop our RakPeerInterface
	g_RakPeer->Shutdown(500);

	Logger::Msg("CNetworkManager::Stopped");
}

void CNetworkManager::Connect()
{
	// Disconnect if we're already connected
	if (g_ConnectionState == CONSTATE_COND)
		Disconnect();

	// Set our last connection so we can connect again later and we set our state to connecting
	LastConnection(CON_IP, CON_PASS, CON_PORT);
	g_ConnectionState = CONSTATE_CONN;

	// Connect to the server, leaving the result
	int Result = g_RakPeer->Connect(CON_IP, CON_PORT, CON_PASS, sizeof(CON_PASS));

	// Check if connection failed, then set our state to failed
	if (Result != 0)
	{
		g_ConnectionState = CONSTATE_FAIL;
		Logger::Msg("Failed to connect, errorcode: %d", Result);
		return;
	}
}

unsigned long m_ulLastPureSyncTime = 0;
unsigned long m_ulLastSyncReceived = 0;

float x;
float y;
float z;

float rx;
float ry;
float rz;
float rw;

bool cloned = false;
Ped clonedped;

void CNetworkManager::Disconnect()
{
	// Don't do anything if we're not connected
	if (g_ConnectionState == CONSTATE_DISC)
		return;

	// Stop RakPeer from accepting anymore incoming packets
	g_RakPeer->CloseConnection(g_SystemAddr, true);

	// Set our state to disconnected
	g_ConnectionState = CONSTATE_DISC;

	// Reinitialize our RakPeerInterface
	Stop();
	Start();

	// Clean the server GUID
	g_SystemAddr = UNASSIGNED_SYSTEM_ADDRESS;

	Logger::Msg("CNetworkManager::Disconnected");

	PED::DELETE_PED(&clonedped);
	cloned = !cloned;
	clonedped = NULL;
}

void CNetworkManager::Update()
{
	//cout << m_pInterpolationData->pPosition.ulFinishTime << endl;
	if (m_pInterpolationData->pPosition.ulFinishTime != 0) {
		ENTITY::SET_ENTITY_QUATERNION(clonedped, rx, ry, rz, rw);

		unsigned long ulCurrentTime = timeGetTime();

		// Get our position
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(clonedped, ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_ID()));;
		CVector3 vecCurrentPosition(coords.x, coords.y, coords.z-1.0f);

		// Get the factor of time spent from the interpolation start
		// to the current time.
		float fAlpha = Math::Unlerp(m_pInterpolationData->pPosition.ulStartTime, ulCurrentTime, m_pInterpolationData->pPosition.ulFinishTime);

		// Don't let it overcompensate the error
		fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

		// Get the current error portion to compensate
		float fCurrentAlpha = (fAlpha - m_pInterpolationData->pPosition.fLastAlpha);
		m_pInterpolationData->pPosition.fLastAlpha = fAlpha;

		// Apply the error compensation
		CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_pInterpolationData->pPosition.vecError);

		// If we finished compensating the error, finish it for the next pulse
		if (fAlpha == 1.0f)
			m_pInterpolationData->pPosition.ulFinishTime = 0;

		// Calculate the new position
		CVector3 vecNewPosition = (vecCurrentPosition + vecCompensation);

		// Check if the distance to interpolate is too far
		if ((vecCurrentPosition - m_pInterpolationData->pPosition.vecTarget).Length() > 750.0f)
		{
			// Abort all interpolation
			m_pInterpolationData->pPosition.ulFinishTime = 0;
			vecNewPosition = m_pInterpolationData->pPosition.vecTarget;
		}

		// Set our new position
		ENTITY::SET_ENTITY_COORDS(clonedped, vecNewPosition.fX, vecNewPosition.fY, vecNewPosition.fZ, false, false, false, false);

		//cout << "cur " << vecCurrentPosition.fX << vecCurrentPosition.fY << vecCurrentPosition.fZ << endl;
		//cout << "com " << vecCompensation.fX << vecCompensation.fY << vecCompensation.fZ << endl;
		//cout << "new " << vecNewPosition.fX << vecNewPosition.fY << vecNewPosition.fZ << endl;
	}
}

void CNetworkManager::Pulse()
{
	// Don't do anything if we're disconnected
	if (g_ConnectionState == CONSTATE_DISC || g_ConnectionState == CONSTATE_FAIL)
		return;

	if (!cloned)
	{
		char *name = "a_f_y_tourist_02";
		int PedHash = GAMEPLAY::GET_HASH_KEY(name);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(PedHash) && STREAMING::IS_MODEL_VALID(PedHash))
		{
			STREAMING::REQUEST_MODEL(PedHash);
			while (!STREAMING::HAS_MODEL_LOADED(PedHash)) WAIT(0);
			clonedped = PED::CREATE_PED(26, PedHash, x, y, z, 0.0f, 1, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);

			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), clonedped, false);
			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(clonedped, PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), false);

			m_pInterpolationData = new sPlayerEntity_InterpolationData;

			cloned = !cloned;
		}
		cout << "cloned" << endl;
	} else {
		Update();
	}

	unsigned long ulCurrentTime = timeGetTime();
	if (ulCurrentTime >= m_ulLastPureSyncTime + (1000.0f / 100))
	{
		//if (g_ConnectionState == CONSTATE_CONN)
		//	return;

		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_ID()));;
		Vector4 rotation;

		ENTITY::GET_ENTITY_QUATERNION(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), &rotation.fX, &rotation.fY, &rotation.fZ, &rotation.fW);

		m_ulLastPureSyncTime = ulCurrentTime;

		BitStream playerpack;

		playerpack.Write((unsigned char)ID_PACKET_TEST);
		playerpack.Write(coords.x);
		playerpack.Write(coords.y);
		playerpack.Write(coords.z);

		playerpack.Write(rotation.fX);
		playerpack.Write(rotation.fY);
		playerpack.Write(rotation.fZ);
		playerpack.Write(rotation.fW);

		g_RakPeer->Send(&playerpack, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, g_SystemAddr, false);

		//cout << ulCurrentTime << " " << m_ulLastPureSyncTime << endl;
	}

	Packet *g_Packet = NULL;

	while (g_Packet = g_RakPeer->Receive())
	{
		BitStream playerpackrec(g_Packet->data + 1, g_Packet->length + 1, false);

		switch (g_Packet->data[0])
		{
			case ID_NO_FREE_INCOMING_CONNECTIONS:
			{
				Logger::Msg("Failed to connect, max client", g_Packet->data[0]);
				break;
			}
			case ID_INVALID_PASSWORD:
			{
				Logger::Msg("Failed to connect, invalid password", g_Packet->data[0]);
				break;
			}
			case ID_CONNECTION_ATTEMPT_FAILED:
			{
				Logger::Msg("Failed to connect, failed", g_Packet->data[0]);
				break;
			}
			case ID_CONNECTION_BANNED:
			{
				Logger::Msg("Failed to connect, banned", g_Packet->data[0]);
				break;
			}
			case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				// Set the server GUID
				g_SystemAddr = g_Packet->systemAddress;

				// Set our state to connected
				g_ConnectionState = CONSTATE_COND;

				Logger::Msg("CNetworkManager::Connected");

				m_ulLastSyncReceived = timeGetTime();
				break;
			}
			case ID_PACKET_TEST:
			{
				playerpackrec.Read(x);
				playerpackrec.Read(y);
				playerpackrec.Read(z);
				playerpackrec.Read(rx);
				playerpackrec.Read(ry);
				playerpackrec.Read(rz);
				playerpackrec.Read(rw);

				//cout << "packetreceived" << endl;

				Update();

				unsigned int interpolationtime = timeGetTime() - m_ulLastSyncReceived;

				// Get our position
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(clonedped, ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_ID()));;
				CVector3 vecCurrentPosition(coords.x, coords.y, coords.z - 1.0f);

				// Set the target position
				CVector3 vecPosition = { x, y, z };
				m_pInterpolationData->pPosition.vecTarget = vecPosition;

				// Calculate the relative error
				m_pInterpolationData->pPosition.vecError = (vecPosition - vecCurrentPosition);

				// Get the interpolation interval
				unsigned long ulTime = timeGetTime();
				m_pInterpolationData->pPosition.ulStartTime = ulTime;
				m_pInterpolationData->pPosition.ulFinishTime = (ulTime + interpolationtime);

				// Initialize the interpolation
				m_pInterpolationData->pPosition.fLastAlpha = 0.0f;

				m_ulLastSyncReceived = timeGetTime();

				//cout << m_pInterpolationData->pPosition.ulFinishTime << " " << interpolationtime << " " << ulTime << endl;
				break;
			}
			Logger::Msg("%d", g_Packet->data[0]);
		}
		g_RakPeer->DeallocatePacket(g_Packet);
	}
}

