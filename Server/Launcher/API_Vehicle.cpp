#include "stdafx.h"

namespace API
{
	const char *Vehicle::ThisNamespace = "API::Vehicle";

	const int Vehicle::Create(const std::wstring model, const CVector3 position, const float heading)
	{
		CVehicleEntity newVehicle;
		newVehicle.Create(model, position, heading);
		g_Vehicles.push_back(newVehicle);

		return newVehicle.GetId();
	}
	const int Vehicle::Create(const std::wstring model, const CVector3 position, const CVector3 rotation)
	{
		CVehicleEntity newVehicle;
		newVehicle.Create(model, position, rotation);
		g_Vehicles.push_back(newVehicle);

		return newVehicle.GetId();
	}

	void Vehicle::SetColor(const int entity, const int layer, const int painttype, const int color)
	{
		if (layer == 1 || layer == 2)
		{
			const int index = ServerEntity::GetIndex(entity);
			if (index > -1) {
				switch (g_Entities[index].GetType())
				{
				case CServerEntity::Vehicle:
					for (int i = 0; i < g_Vehicles.size(); i++)
					{
						if (g_Vehicles[i].GetId() == entity)
						{
							g_Vehicles[i].SetColor(layer, painttype, color);

							RakNet::BitStream sData;
							sData.Write(entity);
							sData.Write(layer);
							sData.Write(painttype);
							sData.Write(color);

							g_Server->GetNetworkManager()->GetRPC().Signal("SetStandardColor", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
							return;
						}
					}
					break;
				default:
					std::wcout << L"Entity " << entity << L" is not of type Vehicle." << std::endl;
					break;
				}
			}
			else {
				std::wcout << L"Invalid Entity: " << entity << std::endl;
			}
		}
		else {
			std::wcout << L"Invalid Layer, Layers are 1 or 2." << std::endl;
		}
	}

	void Vehicle::SetColor(const int entity, const int layer, const Color color)
	{
		if (layer == 1 || layer == 2)
		{
			const int index = ServerEntity::GetIndex(entity);
			if (index > -1) {
				switch (g_Entities[index].GetType())
				{
				case CServerEntity::Vehicle:
					for (int i = 0; i < g_Vehicles.size(); i++)
					{
						if (g_Vehicles[i].GetId() == entity)
						{
							g_Vehicles[i].SetColor(layer, color);

							RakNet::BitStream sData;
							sData.Write(entity);
							sData.Write(layer);
							sData.Write(color.Red);
							sData.Write(color.Green);
							sData.Write(color.Blue);

							g_Server->GetNetworkManager()->GetRPC().Signal("SetCustomColor", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
							return;
						}
					}
					break;
				default:
					std::wcout << L"Entity " << entity << L" is not of type Vehicle." << std::endl;
					break;
				}
			}
			else {
				std::wcout << L"Invalid Entity: " << entity << std::endl;
			}
		}
		else {
			std::wcout << L"Invalid Layer, Layers are 1 or 2." << std::endl;
		}
	}
}
