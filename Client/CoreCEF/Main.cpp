#include "stdafx.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	CCef *g_CEF = new CCef();

	if (!g_CEF->Initialize(hInstance))
		MessageBeep(-1);
	//g_CEF->Pulse();
	return 1;
}