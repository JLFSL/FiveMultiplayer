#pragma once
class CefRenderer
{
private:
	static HHOOK msgHook;
	static HWND curProc;

	static CefMainArgs args;
	static CefRefPtr<OffscreenClient> offscreenClient;
	static CefSettings settings;
	static CefWindowInfo window_info;
	static CefBrowserSettings browserSettings;
	static CefRefPtr<CefBrowser> browser;

public:
	static bool Initialize();
	static void Start();

	static void OnTick();

	static CefRefPtr<CefBrowser> getBrowser() { return browser; }
	static HWND getProcess() { return curProc; }
};

