#pragma once

namespace GamePed
{
	int GetVehicleID(Ped ped);
	int GetVehicleSeat(Ped ped);
	Vehicle GetVehicle(Ped ped);
	
	void SetPedComponentVariation(Ped ped, const int componentid, const int drawableid, const int textureid, const int paletteid);
	void SetPedHeadBlend(Ped ped, int shapeFirst, int shapeSecond, int shapeThird, int skinFirst, int skinSecond, int skinThird, float shapeMix, float skinMix, float thirdMix);
	void SetPedHeadOverlayColor(Ped ped, int overlayid, int index, int colorType, int colorid, int secondColorid, float opacity);
	void SetPedProp(Ped ped, int componentid, int drawableid, int textureid);
	void SetPedFaceFeature(Ped ped, int index, float scale);
}