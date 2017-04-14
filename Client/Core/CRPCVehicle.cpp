#include "stdafx.h"

void CRPCVehicle::SetStandardColor(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
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
				break;
			}
		}
	}
}

void CRPCVehicle::SetCustomColor(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
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
				break;
			}
		}
	}
}

void CRPCVehicle::SetNumberPlate(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity;
	RakWString plate;

	bitStream->Read(entity);
	bitStream->Read(plate);
	
	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetNumberPlate(plate.C_String());
				break;
			}
		}
	}
}

void CRPCVehicle::SetMod(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity, modType, modIndex;

	bitStream->Read(entity);
	bitStream->Read(modType);
	bitStream->Read(modIndex);

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetMod(modType, modIndex);
				break;
			}
		}
	}
}

void CRPCVehicle::SetEngineState(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity;
	bool state;

	bitStream->Read(entity);
	bitStream->Read(state);

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetEngineState(state);
				break;
			}
		}
	}
}

void CRPCVehicle::SetDoorsLockState(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity, state;

	bitStream->Read(entity);
	bitStream->Read(state);

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetDoorsLockState(state);
				break;
			}
		}
	}
}

void CRPCVehicle::SetNumberPlateStyle(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity, state;

	bitStream->Read(entity);
	bitStream->Read(state);

	if (CServerEntity::IsValid(entity))
	{
		for (int i = 0; i < g_Vehicles.size(); i++) {
			if (g_Vehicles[i].GetId() == entity) {
				g_Vehicles[i].SetNumberPlateStyle(state);
				break;
			}
		}
	}
}