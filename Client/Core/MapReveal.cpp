#include "stdafx.h"

using namespace Memory;

void MapReveal::RevealFullMap()
{
	// GTA:Online Full Map
	auto checkMultiplayerDrawMapFrame = pattern("40 8A 35 ? ? ? ? 84 C0 74 05 45 84 FF");
	uint8_t original[7] = { 0 };

	Memory::nop(checkMultiplayerDrawMapFrame.count(1).get(0).get<void>(0), 7);
}