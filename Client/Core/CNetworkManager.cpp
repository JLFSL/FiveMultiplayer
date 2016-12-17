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

void CNetworkManager::Connect(const char *ip, const char *pass, int port)
{
	// Disconnect if we're already connected
	if (g_ConnectionState == CONSTATE_COND)
		Disconnect();

	// Set our last connection so we can connect again later and we set our state to connecting
	LastConnection(ip, pass, port);
	g_ConnectionState = CONSTATE_CONN;

	// Connect to the server, leaving the result
	int Result = g_RakPeer->Connect(ip, port, pass, sizeof(pass));

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

float vx;
float vy;
float vz;

float rx;
float ry;
float rz;
float rw;

bool cloned = false;
bool veh = true;
Ped clonedped;
Vehicle clonedveh;

int returnclone() {
	if (veh)
		return clonedveh;
	if (!veh)
		return clonedped;
}

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

	if (!veh)
	{
		PED::DELETE_PED(&clonedped);
		cloned = false;
		clonedped = NULL;
	}
	else
	{
		VEHICLE::DELETE_VEHICLE(&clonedveh);
		cloned = false;
		clonedveh = NULL;
	}
}

void CNetworkManager::Update()
{
	//cout << m_pInterpolationData->pPosition.ulFinishTime << endl;
	if (m_pInterpolationData->pPosition.ulFinishTime != 0) {
		// Get our position
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(returnclone(), ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_ID()));
		CVector3 vecCurrentPosition;
		if (!veh)
		{
			vecCurrentPosition.fX = coords.x;
			vecCurrentPosition.fY = coords.y;
			vecCurrentPosition.fZ = coords.z-1.0f;
		}
		else
		{
			vecCurrentPosition.fX = coords.x;
			vecCurrentPosition.fY = coords.y;
			vecCurrentPosition.fZ = coords.z;
		}

		// Get the factor of time spent from the interpolation start
		// to the current time.
		unsigned long ulCurrentTime = timeGetTime();
		float fAlpha = Math::Unlerp(m_pInterpolationData->pPosition.ulStartTime, ulCurrentTime, m_pInterpolationData->pPosition.ulFinishTime);

		float alphathing;
		if (!veh)
			alphathing = 1.0f;
		if (veh)
			alphathing = 1.5f;

		// Don't let it overcompensate the error
		fAlpha = Math::Clamp(0.0f, fAlpha, alphathing);

		// Get the current error portion to compensate
		float fCurrentAlpha = (fAlpha - m_pInterpolationData->pPosition.fLastAlpha);
		m_pInterpolationData->pPosition.fLastAlpha = fAlpha;

		// Apply the error compensation
		CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_pInterpolationData->pPosition.vecError);

		// If we finished compensating the error, finish it for the next pulse
		if (fAlpha == alphathing)
			m_pInterpolationData->pPosition.ulFinishTime = 0;

		// Calculate the new position
		CVector3 vecNewPosition = vecCurrentPosition + vecCompensation;

		// Check if the distance to interpolate is too far
		if ((vecCurrentPosition - m_pInterpolationData->pPosition.vecTarget).Length() > 750.0f)
		{
			// Abort all interpolation
			m_pInterpolationData->pPosition.ulFinishTime = 0;
			vecNewPosition = m_pInterpolationData->pPosition.vecTarget;
		}

		// Set our new position
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(returnclone(), vecNewPosition.fX, vecNewPosition.fY, vecNewPosition.fZ, false, false, false);
		ENTITY::SET_ENTITY_VELOCITY(returnclone(), vx, vy, vz);

		//cout << "cur " << vecCurrentPosition.fX << vecCurrentPosition.fY << vecCurrentPosition.fZ << endl;
		//cout << "com " << vecCompensation.fX << vecCompensation.fY << vecCompensation.fZ << endl;
		//cout << "new " << vecNewPosition.fX << vecNewPosition.fY << vecNewPosition.fZ << endl;
	}
}

void CNetworkManager::UpdateRotation()
{
	//cout << m_pInterpolationData->pPosition.ulFinishTime << endl;
	if (m_pInterpolationData->pRotation.ulFinishTime != 0) {
		CVector3 vecCurrentRotation;

		// Get our rotation
		float unusedw;
		ENTITY::GET_ENTITY_QUATERNION(returnclone(), &vecCurrentRotation.fX, &vecCurrentRotation.fY, &vecCurrentRotation.fZ, &unusedw);

		// Get the factor of time spent from the interpolation start
		// to the current time.
		unsigned long ulCurrentTime = timeGetTime();
		float fAlpha = Math::Unlerp(m_pInterpolationData->pRotation.ulStartTime, ulCurrentTime, m_pInterpolationData->pRotation.ulFinishTime);

		// Don't let it overcompensate the error
		fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

		// Get the current error portion to compensate
		float fCurrentAlpha = (fAlpha - m_pInterpolationData->pRotation.fLastAlpha);
		m_pInterpolationData->pRotation.fLastAlpha = fAlpha;

		// Apply the error compensation
		CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_pInterpolationData->pRotation.fError);

		// If we finished compensating the error, finish it for the next pulse
		if (fAlpha == 1.0f)
			m_pInterpolationData->pRotation.ulFinishTime = 0;

		// Calculate the new position
		CVector3 vecNewRotation = vecCurrentRotation + vecCompensation;

		// Set our new position
		ENTITY::SET_ENTITY_QUATERNION(returnclone(), vecNewRotation.fX, vecNewRotation.fY, vecNewRotation.fZ, unusedw);

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
		if (!veh) 
		{
			char *name = "a_f_y_tourist_02";
			int PedHash = GAMEPLAY::GET_HASH_KEY(name);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(PedHash) && STREAMING::IS_MODEL_VALID(PedHash))
			{
				STREAMING::REQUEST_MODEL(PedHash);
				while (!STREAMING::HAS_MODEL_LOADED(PedHash)) WAIT(0);
				clonedped = PED::CREATE_PED(26, PedHash, x, y, z, 0.0f, false, true);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);

				ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), clonedped, false);
				ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(clonedped, PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), false);

				m_pInterpolationData = new sPlayerEntity_InterpolationData;

				cloned = true;
			}
		}
		else
		{
			char *name = "BUFFALO2";
			int VehHash = GAMEPLAY::GET_HASH_KEY(name);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(VehHash) && STREAMING::IS_MODEL_VALID(VehHash))
			{
				STREAMING::REQUEST_MODEL(VehHash);
				while (!STREAMING::HAS_MODEL_LOADED(VehHash)) WAIT(0);

				clonedveh = VEHICLE::CREATE_VEHICLE(VehHash, x, y, z, 0.0f, false, true);

				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(VehHash);

				ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), false), clonedveh, false);
				ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(clonedveh, PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), false), false);

				m_pInterpolationData = new sPlayerEntity_InterpolationData;

				cloned = true;
			}
		}
	} else {
		Update();
		UpdateRotation();
	}

	unsigned long ulCurrentTime = timeGetTime();
	if (ulCurrentTime >= m_ulLastPureSyncTime + (1000.0f / 50 ))
	{
		//if (g_ConnectionState == CONSTATE_CONN)
		//	return;

		Vector3 coords;
		Vector4 rotation;
		Vector3 velocity;

		Player player = PLAYER::PLAYER_ID();
		Ped playerped = PLAYER::GET_PLAYER_PED(player);

		if (!veh)
		{
			coords = ENTITY::GET_ENTITY_COORDS(playerped, ENTITY::IS_ENTITY_DEAD(playerped));
			ENTITY::GET_ENTITY_QUATERNION(playerped, &rotation.fX, &rotation.fY, &rotation.fZ, &rotation.fW);
			velocity = ENTITY::GET_ENTITY_VELOCITY(playerped);
		}
		else
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerped, false);

			coords = ENTITY::GET_ENTITY_COORDS(veh, ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_ID()));
			ENTITY::GET_ENTITY_QUATERNION(veh, &rotation.fX, &rotation.fY, &rotation.fZ, &rotation.fW);
			velocity = ENTITY::GET_ENTITY_VELOCITY(veh);
		}

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

		playerpack.Write(velocity.x);
		playerpack.Write(velocity.y);
		playerpack.Write(velocity.z);

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
				playerpackrec.Read(vx);
				playerpackrec.Read(vy);
				playerpackrec.Read(vz);

				//cout << "packetreceived" << endl;

				//Update();

				// position interpolation
				{
					unsigned int interpolationtime = timeGetTime() - m_ulLastSyncReceived;
					unsigned long ulTime = timeGetTime();

					// Get our position
					CVector3 vecCurrentPosition;
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(returnclone(), ENTITY::IS_ENTITY_DEAD(returnclone()));
					vecCurrentPosition.fX = coords.x;
					vecCurrentPosition.fY = coords.y;
					if (!veh) {
						vecCurrentPosition.fZ = coords.z - 1.0f;
					}
					else {
						vecCurrentPosition.fZ = coords.z;
					}

					// Set the target position
					CVector3 vecPosition = { x, y, z };
					if (!veh)
						vecPosition = { x, y, z - 1.0f };
					m_pInterpolationData->pPosition.vecTarget = vecPosition;

					// Calculate the relative error
					m_pInterpolationData->pPosition.vecError = vecPosition - vecCurrentPosition;

					if (veh) {
						// Apply the error over 400ms (i.e. 1/4 per 100ms)
						m_pInterpolationData->pPosition.vecError *= Math::Lerp<const float>(0.25f, Math::UnlerpClamped(100, interpolationtime, 400), 1.0f);
					}

					// Get the interpolation interval
					m_pInterpolationData->pPosition.ulStartTime = ulTime;
					m_pInterpolationData->pPosition.ulFinishTime = (ulTime + interpolationtime);

					// Initialize the interpolation
					m_pInterpolationData->pPosition.fLastAlpha = 0.0f;

					//cout << m_pInterpolationData->pPosition.ulFinishTime << " " << interpolationtime << " " << ulTime << endl;
				}

				//UpdateRotation();

				// rotation interpolation
				{
					unsigned int interpolationtime = timeGetTime() - m_ulLastSyncReceived;
					unsigned long ulTime = timeGetTime();

					// Get our position
					CVector3 vecLocalRotation;
					float unusedw;
					ENTITY::GET_ENTITY_QUATERNION(returnclone(), &vecLocalRotation.fX, &vecLocalRotation.fY, &vecLocalRotation.fZ, &unusedw);

					// Set the target rotation
					CVector3 vecRotation = { rx, ry, rz };
					m_pInterpolationData->pRotation.fTarget = vecRotation;

					// Get the error
					m_pInterpolationData->pRotation.fError = Math::GetOffsetDegrees(vecLocalRotation, vecRotation);
					m_pInterpolationData->pRotation.fError *= Math::Lerp < const float >(0.40f, Math::UnlerpClamped(100, interpolationtime, 400), 1.0f);

					// Get the interpolation interval
					m_pInterpolationData->pRotation.ulStartTime = ulTime;
					m_pInterpolationData->pRotation.ulFinishTime = (ulTime + interpolationtime);

					// Initialize the interpolation
					m_pInterpolationData->pRotation.fLastAlpha = 0.0f;
				}

				m_ulLastSyncReceived = timeGetTime();
				break;
			}
			Logger::Msg("%d", g_Packet->data[0]);
		}
		g_RakPeer->DeallocatePacket(g_Packet);
	}
}

