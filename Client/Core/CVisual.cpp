#include "stdafx.h"

void CVisual::ShowMessageAboveMap(const char *message)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT((char*)message);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
}