#pragma once
class CefInput
{
private:
	static WNDPROC Hook;
	static bool Visible;
	static MSG msg;

public:

	static void InstallHook();
	static void UninstallHook();
	static int Messages();
	static void ForegroundCheck();

	static bool IsVisible() { return Visible; }
	static WNDPROC GetHook() { return Hook; }
};

LRESULT WINAPI HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);