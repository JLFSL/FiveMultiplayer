#pragma once
class CCore
{
private:
	static unsigned long LastCleanUp;
	static unsigned long LastUnlock;

public:
	static bool Initialize();
	static void OnGameTick();

	static void CleanUp();
	static void CleanUpTick();

	static void PreventCheat();
	static void KeyCheck();
};

