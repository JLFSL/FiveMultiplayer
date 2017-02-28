#pragma once
class CefMouseHook
{
private:
	static HHOOK Hook;
	static bool Visible;
	static MSG msg;

public:

	static void InstallHook();
	static void UninstallHook();
	static int Messages();
	static void ForegroundCheck();

	static bool IsVisible() { return Visible; }
	static HHOOK GetHook() { return Hook; }
};

LRESULT WINAPI MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam);