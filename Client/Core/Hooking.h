#pragma once

class Hooking
{
public:
	static void Start(HMODULE hmoduleDLL);
	static void Cleanup();

	// Native function handler type
	typedef void(__cdecl * NativeHandler)(scrNativeCallContext * context);
	static NativeHandler GetNativeHandler(uint64_t origHash);
	static eGameState GetGameState();
	static BlipList* GetBlipList();

	static void InitNativeHook();
	static void onTickInit();
	static bool HookNatives();

private:
	static BOOL InitializeHooks();
	static void FindPatterns();
	static void FailPatterns(const char* name, Memory::pattern ptn);

};	void WAIT(DWORD ms);
