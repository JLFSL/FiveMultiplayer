#include "stdafx.h"

int CPlayerEntity::Amount = 0;

CNetworkManager* g_Network;

void CPlayerEntity::Create(string Name, RakNetGUID GUID, SystemAddress Ip)
{
	Information.Name = Name;
	Information.Id = Amount;
	Network.GUID = GUID;
	Network.Ip = Ip;

	Amount++;

	cout << "[CPlayerEntity] Added Player: " << Information.Name << " [" << Network.Ip.ToString(false) << "]" << endl;
	cout << "[CPlayerEntity] Players Online: " << Amount << endl;

	Network.LastSyncSent = timeGetTime();
	Network.Synchronized = true;
}

void CPlayerEntity::Destroy()
{
	cout << "[CPlayerEntity] Removing Player: " << Information.Name << " [" << Network.Ip.ToString(false) << "]" << endl;

	Information = {};
	Statistics = {};
	Data = {};
	Network = {};

	Information.Id = -1;

	Amount--;

	cout << "[CPlayerEntity] Players Online: " << Amount << endl;
}

void CPlayerEntity::Pulse()
{
	if (Network.LastSyncSent + (1000 / CServer::GetInstance()->GetSyncRate()) <= timeGetTime())
	{
		BitStream bitstream;
		bitstream.Write((unsigned char)ID_PACKET_TEST);
		bitstream.Write(Information.Id);
		bitstream.Write(Information.Name);

		bitstream.Write(Statistics.Score);

		bitstream.Write(Data.Position.fX);
		bitstream.Write(Data.Position.fY);
		bitstream.Write(Data.Position.fZ);

		bitstream.Write(Data.Velocity.fX);
		bitstream.Write(Data.Velocity.fY);
		bitstream.Write(Data.Velocity.fZ);

		bitstream.Write(Data.Quaternion.fX);
		bitstream.Write(Data.Quaternion.fY);
		bitstream.Write(Data.Quaternion.fZ);
		bitstream.Write(Data.Quaternion.fW);
		//g_Network->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_RAKNET_GUID, true);

		Network.LastSyncSent = timeGetTime();
	}
}

void CPlayerEntity::Update(Packet *packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Information);
	bitstream.Read(Statistics);
	bitstream.Read(Data);

	Network.GUID = packet->guid;
	Network.Ip = packet->systemAddress;
}