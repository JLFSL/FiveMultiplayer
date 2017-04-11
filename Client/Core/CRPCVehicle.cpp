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