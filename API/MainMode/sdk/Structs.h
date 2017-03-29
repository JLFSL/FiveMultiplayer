#pragma once

struct Color {
	int Red;
	int Green;
	int Blue;
	int Alpha;
};

struct PedComponent
{
	int drawableid = -1;
	int textureid = -1;
	int paletteid = -1;
};

struct PedHeadBlend
{
	int shapeFirst = 0;
	int shapeSecond = 0;
	int shapeThird = 0;
	int skinFirst = 0;
	int skinSecond = 0;
	int skinThird = 0;
	float shapeMix = 0;
	float skinMix = 0;
	float thirdMix = 0;
};

struct PedHeadOverlay
{
	int index = 0;
	float opacity = 0.0f;
	int colorType = 0;
	int colorID = 0;
	int secondColorID = 0;
};

struct PedProp
{
	int drawableid = 0;
	int textureid = 0;
};

struct PedFeature
{
	float scale = 0.0f;
};