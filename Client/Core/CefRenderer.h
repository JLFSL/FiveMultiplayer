#pragma once
class CefRenderer
{
private:
	static HHOOK msgHook;

	static CefMainArgs args;
	static CefRefPtr<OffscreenClient> offscreenClient;
	static CefSettings settings;
	static CefWindowInfo window_info;
	static CefBrowserSettings browserSettings;

public:
	static bool Initialize();
	static void Start();

	static void OnTick();
};

