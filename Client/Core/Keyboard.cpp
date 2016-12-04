//keyboard.cpp
#include "stdafx.h"

const int KEYS_SIZE = 255;

DWORD trainerResetTime = 0;

bool gameInputDisabledByUs = false;
bool gameInputBlockedByUs = false;

struct {
	DWORD time;
	BOOL isWithAlt;
	BOOL wasDownBefore;
	BOOL isUpNow;
} keyStates[KEYS_SIZE];

void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (key < KEYS_SIZE)
	{
		keyStates[key].time = GetTickCount();
		keyStates[key].isWithAlt = isWithAlt;
		keyStates[key].wasDownBefore = wasDownBefore;
		keyStates[key].isUpNow = isUpNow;
	}
}

const int NOW_PERIOD = 100, MAX_DOWN = 5000; // ms

bool KeyDown(DWORD key)
{
	return (key < KEYS_SIZE) ? ((GetTickCount() < keyStates[key].time + MAX_DOWN) && !keyStates[key].isUpNow) : false;
}

bool KeyJustUp(DWORD key, bool exclusive)
{
	bool b = (key < KEYS_SIZE) ? (GetTickCount() < keyStates[key].time + NOW_PERIOD && keyStates[key].isUpNow) : false;
	if (b && exclusive)
		ResetKeyState(key);
	return b;
}

void ResetKeyState(DWORD key)
{
	if (key < KEYS_SIZE)
		memset(&keyStates[key], 0, sizeof(keyStates[0]));
}
#define IsKeyPressed(key) GetAsyncKeyState(key) & 0x8000
bool KeyPressedOnce(bool& bIsPressed, DWORD vk)
{
	if (IsKeyPressed(vk))
	{
		if (bIsPressed == false)
		{
			bIsPressed = true;
			return true;
		}
	}
	else if (bIsPressed == true)
	{
		bIsPressed = false;
	}
	return false;
}

bool trainer_switch_pressed()
{
	bool result = KeyJustUp(VK_F4);
	return result;
}

void reset_trainer_switch()
{
	trainerResetTime = GetTickCount();
}

void get_button_state(bool *a, bool *b, bool *up, bool *down, bool *l, bool *r)
{
	if (a) *a = KeyDown(VK_NUMPAD5);
	if (b) *b = KeyJustUp(VK_NUMPAD0);
	if (up) *up = KeyDown(VK_NUMPAD8);
	if (down) *down = KeyDown(VK_NUMPAD2);
	if (r) *r = KeyDown(VK_NUMPAD6);
	if (l) *l = KeyDown(VK_NUMPAD4);
}