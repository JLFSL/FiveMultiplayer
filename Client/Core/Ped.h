#pragma once

namespace GamePed
{
	int GetVehicleID(Ped ped);
	int GetVehicleSeat(Ped ped);
	Vehicle GetVehicle(Ped ped);
	
	void SetPedComponentVariation(Ped ped, const int componentid, const int drawableid, const int textureid, const int paletteid);
	void SetPedHeadBlend(Ped ped, const int shapeFirst, const int shapeSecond, const int shapeThird, const int skinFirst, const int skinSecond, const int skinThird, const float shapeMix, const float skinMix, const float thirdMix);
	void SetPedHeadOverlayColor(Ped ped, const int overlayid, const int index, const int colorType, const int colorid, const int secondColorid, const float opacity);
	void SetPedProp(Ped ped, const int componentid, const int drawableid, const int textureid);
	void SetPedFaceFeature(Ped ped, const int index, const float scale);
}