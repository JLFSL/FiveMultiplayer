#include "stdafx.h"

void CVisual::ShowMessageAboveMap(const char *message, const char *pic, int icontype, const char *sender, const char *subject)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT((char*)message);
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG((char*)pic, (char*)pic, false, icontype, (char*)sender, (char*)subject, 1.0f, "");
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
}