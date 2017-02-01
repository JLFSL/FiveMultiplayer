#include "stdafx.h"

bool WorldToScreenRel(CVector3 worldCoords, Vector2 screenCoords)
{
	float screenX, screenY;
	if (!GRAPHICS::_WORLD3D_TO_SCREEN2D( worldCoords.fX, worldCoords.fY, worldCoords.fZ, &screenX, &screenY))
	{
		screenCoords = Vector2();
		return false;
	}
	screenCoords = Vector2((screenX - 0.5f) * 2, (screenY - 0.5f) * 2 );
	return true;
}