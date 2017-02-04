#include "stdafx.h"

int CPlayerEntity::Amount = 0;

void CPlayerEntity::Create(std::string Name, RakNetGUID GUID, SystemAddress Ip)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.Player);
	//newServerEntity.SetEntity(this);

	Information.Name = RakString(Name.c_str());
	Information.Entity = newServerEntity.Create();
	Network.GUID = GUID;
	Network.Ip = Ip;

	Data.Model.Model = "u_m_y_pogo_01";

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
	Information.PlayerID = -1;

	Data.Vehicle.VehicleID = -1;
	Data.Vehicle.Seat = -1;

	Amount--;

	std::cout << "[CPlayerEntity] Players Online: " << Amount << std::endl;
}

void CPlayerEntity::Pulse()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(Network.LastSyncSent.time_since_epoch()).count() + (1000 / CServer::GetInstance()->GetSyncRate()) 
		<= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() && Information.Entity != -1 && Information.PlayerID != -1)
	{
		BitStream bitstream;
		bitstream.Write((unsigned char)ID_PACKET_PLAYER);
		bitstream.Write(Network.GUID);

		bitstream.Write(Information.Entity);
		bitstream.Write(Information.Name);

		bitstream.Write(Statistics.Score);

		bitstream.Write(RakString( Data.Model.Model.c_str()));
		bitstream.Write(Data.Model.Type);

		bitstream.Write(Data.Weapon.Weapon);
		bitstream.Write(Data.Weapon.Reload);

		bitstream.Write(Data.ForwardSpeed);

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

		bitstream.Write(Data.Vehicle.VehicleID);
		bitstream.Write(Data.Vehicle.Seat);

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

	bitstream.Read(Data.Position.fX);
	bitstream.Read(Data.Position.fY);
	bitstream.Read(Data.Position.fZ);

	bitstream.Read(Data.Velocity.fX);
	bitstream.Read(Data.Velocity.fY);
	bitstream.Read(Data.Velocity.fZ);

	bitstream.Read(Data.Quaternion.fX);
	bitstream.Read(Data.Quaternion.fY);
	bitstream.Read(Data.Quaternion.fZ);
	bitstream.Read(Data.Quaternion.fW);

	bitstream.Read(Data.Vehicle.VehicleID);
	bitstream.Read(Data.Vehicle.Seat);

	Network.GUID = packet->guid;
	Network.Ip = packet->systemAddress;
	packet->deleteData;
	
	if (lastVehicle != Data.Vehicle.VehicleID)
	{
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (Data.Vehicle.VehicleID != -1)
			{
				if (g_Vehicles[i].GetId() == Data.Vehicle.VehicleID && g_Vehicles[i].GetOccupant(Data.Vehicle.Seat) != Information.PlayerID)
				{
					g_Vehicles[i].SetOccupant(Data.Vehicle.Seat, Information.PlayerID);

					//OnPlayerEnterVehicle(player,vehicle,seat);
				}
			}

			if (lastSeat != -1 && lastVehicle != -1)
			{
				if (g_Vehicles[i].GetId() == lastVehicle)
				{
					g_Vehicles[i].SetOccupant(lastSeat, -1);
				}
			}
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
	g_Server->GetNetworkManager()->GetRPC().Signal("PlayerHeadBlend", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	for (int i = 0; i < SizeOfArray(Data.ModelComponents); i++)
	{
		sData.Reset();
		sData.Write(Information.Entity);
		sData.Write(i);
		sData.Write(Data.ModelComponents[i].drawableid);
		sData.Write(Data.ModelComponents[i].paletteid);
		sData.Write(Data.ModelComponents[i].textureid);
		g_Server->GetNetworkManager()->GetRPC().Signal("PlayerComponent", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	for (int i = 0; i < SizeOfArray(Data.ModelFaceFeature); i++)
	{
		sData.Reset();
		sData.Write(Information.Entity);
		sData.Write(i);
		sData.Write(Data.ModelFaceFeature[i].scale);
		g_Server->GetNetworkManager()->GetRPC().Signal("PlayerFaceFeature", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
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
		g_Server->GetNetworkManager()->GetRPC().Signal("PlayerHeadOverlay", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	for (int i = 0; i < SizeOfArray(Data.ModelProp); i++)
	{
		sData.Reset();
		sData.Write(Information.Entity);
		sData.Write(i);
		sData.Write(Data.ModelProp[i].drawableid);
		sData.Write(Data.ModelProp[i].textureid);
		g_Server->GetNetworkManager()->GetRPC().Signal("PlayerProp", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);
	}
}