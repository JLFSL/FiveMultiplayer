#pragma once

class Hooking
{
public:
	static void Start(HMODULE hmoduleDLL);
	static void Cleanup();

	// Native function handler type
	typedef void(__cdecl * NativeHandler)(scrNativeCallContext * context);
	static NativeHandler GetNativeHandler(uint64_t origHash);

private:
	static bool InitializeHooks();
	static void FindPatterns();
	static void FailPatterns(const char* name, Memory::pattern ptn);
};
