#include "stdafx.h"

void CRPCVehicle::SetStandardColor(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCVehicle::SetStandardColor" << std::endl;
	int entity, layer, paintType, color;

	bitStream->Read(entity);
	bitStream->Read(layer);
	bitStream->Read(paintType);
	bitStream->Read(color);

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetColor(layer, paintType, color);
				return;
			}
		}
	}
}

void CRPCVehicle::SetCustomColor(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCVehicle::SetCustomColor" << std::endl;
	int entity, layer;
	Color color;

	bitStream->Read(entity);
	bitStream->Read(layer);
	bitStream->Read(color.Red);
	bitStream->Read(color.Green);
	bitStream->Read(color.Blue);

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetColor(layer, color);
				return;
			}
		}
	}
}

void CRPCVehicle::SetNumberPlate(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCVehicle::SetNumberPlate" << std::endl;
	int entity;
	RakWString plate;

	bitStream->Read(entity);
	bitStream->Read(plate);
	
	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetNumberPlate(plate.C_String());
				return;
			}
		}
	}
}

void CRPCVehicle::SetMod(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCVehicle::SetMod" << std::endl;
	int entity, modType, modIndex;

	bitStream->Read(entity);
	bitStream->Read(modType);
	bitStream->Read(modIndex);

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetMod(modType, modIndex);
				return;
			}
		}
	}
}

void CRPCVehicle::SetEngineState(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCVehicle::SetEngineState" << std::endl;
	int entity;
	bool state;

	bitStream->Read(entity);
	bitStream->Read(state);

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetEngineState(state);
				return;
			}
		}
	}
}

void CRPCVehicle::SetDoorsLockState(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCVehicle::SetDoorsLockState" << std::endl;
	int entity, state;

	bitStream->Read(entity);
	bitStream->Read(state);

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetDoorsLockState(state);
				return;
			}
		}
	}
}

void CRPCVehicle::SetNumberPlateStyle(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCVehicle::SetNumberPlateStyle" << std::endl;
	int entity, state;

	bitStream->Read(entity);
	bitStream->Read(state);

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetNumberPlateStyle(state);
				return;
			}
		}
	}
}

void CRPCVehicle::SetExtra(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity, extra;
	bool toggle;

	bitStream->Read(entity);
	bitStream->Read(extra);
	bitStream->Read(toggle);

	std::cout << "CRPCVehicle::SetExtra"<< std::endl;

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetExtra(extra, toggle);
				return;
			}
		}
	}
}