#pragma once
class CVisual
{
public:
	static void ShowMessageAboveMap(const char *message, const char *pic, int icontype, const char *sender, const char *subject);
	static void ShowSubtitle(const char *message, const int duration, const bool shownow);
};