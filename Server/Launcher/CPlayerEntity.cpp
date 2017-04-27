#include "stdafx.h"

int CPlayerEntity::Amount = 0;

void CPlayerEntity::Create(std::string Name, RakNetGUID GUID, SystemAddress Ip)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.Player);

	Information.Name = RakString(Name.c_str());
	Information.Entity = newServerEntity.Create();
	Network.GUID = GUID;
	Network.Ip = Ip;

	Data.Model.Model = L"u_m_y_pogo_01";

	Data.Vehicle.VehicleID = -1;
	Data.Vehicle.Seat = -1;
	
	g_Entities.push_back(newServerEntity);

	Amount++;

	std::cout << "[CPlayerEntity] Added Player: " << Information.Name.C_String() << " [" << Network.Ip.ToString(false) << "]" << std::endl;
	std::cout << "[CPlayerEntity] Players Online: " << Amount << std::endl;

	Network.LastSyncSent = std::chrono::system_clock::now();
	Network.Synchronized = true;
}

void CPlayerEntity::Destroy()
{
	std::cout << "[CPlayerEntity] Removing Player: " << Information.Name << " [" << Network.Ip.ToString(false) << "]" << std::endl;

	BitStream bitstream;
	bitstream.Write((unsigned char)ID_PLAYER_LEFT);
	bitstream.Write(Information.Entity);
	g_Server->GetNetworkManager()->GetInterface()->Send(&bitstream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_RAKNET_GUID, true);

	Information = {};
	Statistics = {};
	Data = {};
	Network = {};

	Information.Entity = -1;

	Data.Vehicle.VehicleID = -1;
	Data.Vehicle.Seat = -1;

	Amount--;

	std::cout << "[CPlayerEntity] Players Online: " << Amount << std::endl;
}

void CPlayerEntity::Pulse()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(Network.LastSyncSent.time_since_epoch()).count() + (1000 / CServer::GetInstance()->GetSyncRate()) 
		<= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() && Information.Entity != -1)
	{
		BitStream bitstream;
		bitstream.Write((unsigned char)ID_PACKET_PLAYER);
		bitstream.Write(Network.GUID);

		bitstream.Write(Information.Entity);
		bitstream.Write(Information.Name);

		bitstream.Write(Statistics.Score);

		bitstream.Write(RakWString(Data.Model.Model.c_str()));
		bitstream.Write(Data.Model.Type);

		bitstream.Write(Data.Weapon.Weapon);
		bitstream.Write(Data.Weapon.Reload);

		bitstream.Write(Data.ForwardSpeed);

		bitstream.Write(Data.Position.x);
		bitstream.Write(Data.Position.y);
		bitstream.Write(Data.Position.z);

		bitstream.Write(Data.Velocity.x);
		bitstream.Write(Data.Velocity.y);
		bitstream.Write(Data.Velocity.z);

		bitstream.Write(Data.Rotation.x);
		bitstream.Write(Data.Rotation.y);
		bitstream.Write(Data.Rotation.z);

		bitstream.Write(Data.Vehicle.VehicleID);
		bitstream.Write(Data.Vehicle.Seat);

		bitstream.Write(Data.Task);

		g_Server->GetNetworkManager()->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_RAKNET_GUID, true);

		Network.LastSyncSent = std::chrono::system_clock::now();
		//timeGetTime();
	}
}

void CPlayerEntity::Update(Packet *packet)
{
	
	int lastVehicle = Data.Vehicle.VehicleID;
	int lastSeat = Data.Vehicle.Seat;

	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	/*bitstream.Read(Information.Entity);
	bitstream.Read(Information.Name);*/
	
	bitstream.Read(Statistics.Score);
	
	bitstream.Read(Data.Model.Type);

	bitstream.Read(Data.Weapon.Weapon);
	bitstream.Read(Data.Weapon.Reload);

	bitstream.Read(Data.ForwardSpeed);

	bitstream.Read(Data.Position.x);
	bitstream.Read(Data.Position.y);
	bitstream.Read(Data.Position.z);

	bitstream.Read(Data.Velocity.x);
	bitstream.Read(Data.Velocity.y);
	bitstream.Read(Data.Velocity.z);

	bitstream.Read(Data.Rotation.x);
	bitstream.Read(Data.Rotation.y);
	bitstream.Read(Data.Rotation.z);

	bitstream.Read(Data.Vehicle.VehicleID);
	bitstream.Read(Data.Vehicle.Seat);

	bitstream.Read(Data.Task);

	Network.GUID = packet->guid;
	Network.Ip = packet->systemAddress;
	packet->deleteData;
	
	if (lastVehicle != Data.Vehicle.VehicleID)
	{
		bool doneOne, doneTwo = false;
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (Data.Vehicle.VehicleID != -1)
			{
				if (g_Vehicles[i].GetId() == Data.Vehicle.VehicleID && g_Vehicles[i].GetOccupant(Data.Vehicle.Seat) != Information.Entity)
				{
					g_Vehicles[i].SetOccupant(Data.Vehicle.Seat, Information.Entity);

					//OnPlayerEnterVehicle(player,vehicle,seat);
					doneOne = true;
				}
			}

			if (lastSeat != -1 && lastVehicle != -1)
			{
				if (g_Vehicles[i].GetId() == lastVehicle)
				{
					g_Vehicles[i].SetOccupant(lastSeat, -1);
					doneTwo = true;
				}
			}

			if (doneOne && doneTwo)
				break;
		}
	}
}

void CPlayerEntity::RequestData(RakNetGUID requester)
{
	RakNet::BitStream sData;

	sData.Reset();
	sData.Write(Information.Entity);
	sData.Write(Data.ModelHeadBlend.shapeFirst);
	sData.Write(Data.ModelHeadBlend.shapeMix);
	sData.Write(Data.ModelHeadBlend.shapeSecond);
	sData.Write(Data.ModelHeadBlend.shapeThird);
	sData.Write(Data.ModelHeadBlend.skinFirst);
	sData.Write(Data.ModelHeadBlend.skinMix);
	sData.Write(Data.ModelHeadBlend.skinSecond);
	sData.Write(Data.ModelHeadBlend.skinThird);
	sData.Write(Data.ModelHeadBlend.thirdMix);
	g_Server->GetNetworkManager()->GetRPC().Signal("PedHeadBlend", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	for (int i = 0; i < SizeOfArray(Data.ModelComponents); i++)
	{
		sData.Reset();
		sData.Write(Information.Entity);
		sData.Write(i);
		sData.Write(Data.ModelComponents[i].drawableid);
		sData.Write(Data.ModelComponents[i].paletteid);
		sData.Write(Data.ModelComponents[i].textureid);
		g_Server->GetNetworkManager()->GetRPC().Signal("PedComponent", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	for (int i = 0; i < SizeOfArray(Data.ModelFaceFeature); i++)
	{
		sData.Reset();
		sData.Write(Information.Entity);
		sData.Write(i);
		sData.Write(Data.ModelFaceFeature[i].scale);
		g_Server->GetNetworkManager()->GetRPC().Signal("PedFaceFeature", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	for (int i = 0; i < SizeOfArray(Data.ModelHeadOverlay); i++)
	{
		sData.Reset();
		sData.Write(Information.Entity);
		sData.Write(i);
		sData.Write(Data.ModelHeadOverlay[i].index);
		sData.Write(Data.ModelHeadOverlay[i].colorType);
		sData.Write(Data.ModelHeadOverlay[i].colorID);
		sData.Write(Data.ModelHeadOverlay[i].secondColorID);
		sData.Write(Data.ModelHeadOverlay[i].opacity);
		g_Server->GetNetworkManager()->GetRPC().Signal("PedHeadOverlay", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	for (int i = 0; i < SizeOfArray(Data.ModelProp); i++)
	{
		sData.Reset();
		sData.Write(Information.Entity);
		sData.Write(i);
		sData.Write(Data.ModelProp[i].drawableid);
		sData.Write(Data.ModelProp[i].textureid);
		g_Server->GetNetworkManager()->GetRPC().Signal("PedProp", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}
}