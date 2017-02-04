#include "stdafx.h"

namespace GamePed
{
	int GetVehicleID(Ped ped)
	{
		Vehicle t_CurrentVehicle = GetVehicle(ped);

		if (t_CurrentVehicle > 0)
		{
			for (int i = 0; i < g_Vehicles.size(); i++)
			{
				if (g_Vehicles[i].GetEntity() == t_CurrentVehicle)
				{
					return g_Vehicles[i].GetId();
				}
			}
		}
		return -1;
	}

	int GetVehicleSeat(Ped ped)
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);

		if (GetVehicle(ped))
		{
			for (int i = -1; i < 10; i++)
			{
				if (ped == VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, i))
				{
					return i + 1;  // makes it so 0 is driver and 1+ passengers
				}
			}
		}
		return -1;

		// Non-Native (need to convert this)
		/*if (!g_Config->GetLatestVersion()) // 1.36 / 877
		{
			if (IsInVehicle(ped))
			{
				if (*(int *)(getScriptHandleBaseAddress(ped) + 0x158A) > 1000)
					*(int *)(getScriptHandleBaseAddress(ped) + 0x158A) = *(int *)(getScriptHandleBaseAddress(ped) + 0x158A) - 262144;

				return *(int *)(getScriptHandleBaseAddress(ped) + 0x158A);
			}
			else
				return -1;
		}
		else // Latest
		{
			if (IsInVehicle(ped))
			{
				if (*(int *)(getScriptHandleBaseAddress(ped) + 0x159A) > 1000)
					*(int *)(getScriptHandleBaseAddress(ped) + 0x159A) = *(int *)(getScriptHandleBaseAddress(ped) + 0x159A) - 262144;

				return *(int *)(getScriptHandleBaseAddress(ped) + 0x159A);
			}
			else
				return -1;
		}*/
	}
	
	/*bool IsInVehicle(Ped ped)
	{
		if (Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false) > 0)
		{
			return true;
		}
		return false;
	}*/

	Vehicle GetVehicle(Ped ped)
	{
		return PED::GET_VEHICLE_PED_IS_IN(ped, false);
	}

	void SetPedComponentVariation(Ped ped, const int componentid, const int drawableid, const int textureid, const int paletteid)
	{
		if (ENTITY::DOES_ENTITY_EXIST(ped))
			PED::SET_PED_COMPONENT_VARIATION(ped, componentid, drawableid, textureid, paletteid);
	}

	void SetPedHeadBlend(Ped ped, int shapeFirst, int shapeSecond, int shapeThird, int skinFirst, int skinSecond, int skinThird, float shapeMix, float skinMix, float thirdMix)
	{
		if (ENTITY::DOES_ENTITY_EXIST(ped))
			PED::SET_PED_HEAD_BLEND_DATA(ped, shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix, 0);
	}

	void SetPedHeadOverlayColor(Ped ped, int overlayid, int index, int colorType, int colorid, int secondColorid, float opacity)
	{
		if (ENTITY::DOES_ENTITY_EXIST(ped))
		{
			PED::SET_PED_HEAD_OVERLAY(ped, overlayid, index, opacity);
			PED::_SET_PED_HEAD_OVERLAY_COLOR(ped, overlayid, colorType, colorid, secondColorid);
		}
	}

	void SetPedProp(Ped ped, int componentid, int drawableid, int textureid)
	{
		if (ENTITY::DOES_ENTITY_EXIST(ped))
			PED::SET_PED_PROP_INDEX(ped, componentid, drawableid, textureid, true);
	}

	void SetPedFaceFeature(Ped ped, int index, float scale)
	{
		if (ENTITY::DOES_ENTITY_EXIST(ped))
			PED::_SET_PED_FACE_FEATURE(ped, index, scale);
	}
}