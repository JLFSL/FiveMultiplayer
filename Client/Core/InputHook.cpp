//InputHook.cpp
#include "stdafx.h"

#define GXLPARAM(lp) ((short)LOWORD(lp))
#define GYLPARAM(lp) ((short)HIWORD(lp))

InputHook iHook;
WNDPROC	oWndProc;

//using namespace Utility;

static std::set<InputHook::TKeyboardFn> g_keyboardFunctions;

void InputHook::keyboardHandlerRegister(TKeyboardFn function) {

	g_keyboardFunctions.insert(function);
}

void InputHook::keyboardHandlerUnregister(TKeyboardFn function) {

	g_keyboardFunctions.erase(function);
}

bool InputHook::Initialize() {

	hWindow = NULL;
	while (hWindow == NULL) {

		hWindow = FindWindow("grcWindow", NULL);
		Sleep(100);
	}
	oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
	if (oWndProc == NULL) {

		Logger::Error("Failed to attach input hook");
		return false;
	}
	else {

		keyboardHandlerRegister(OnKeyboardMessage);
		DEBUGMSG("Input hook attached:  WndProc 0x%p", (DWORD_PTR)oWndProc);
		return true;
	}
}

void InputHook::Remove() {

	SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
	DEBUGMSG("Removed input hook");
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ImGuiIO& io = ImGui::GetIO();
	switch (uMsg)
	{
	case WM_SIZE:
		break;
	case WM_LBUTTONDOWN:
		io.MouseDown[0] = true;
		break;
	case WM_LBUTTONUP:
		io.MouseDown[0] = false;
		break;
	case WM_RBUTTONDOWN:
		io.MouseDown[1] = true;
		break;
	case WM_RBUTTONUP:
		io.MouseDown[1] = false;
		break;
	case WM_MBUTTONDOWN:
		io.MouseDown[2] = true;
		break;
	case WM_MBUTTONUP:
		io.MouseDown[2] = false;
		break;
	case WM_MOUSEWHEEL:
		io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = (signed short)(lParam);
		io.MousePos.y = (signed short)(lParam >> 16);
		break;
	case WM_KEYDOWN: case WM_KEYUP: case WM_SYSKEYDOWN: case WM_SYSKEYUP:
	{
		if (uMsg == WM_KEYUP && wParam < 256)
			io.KeysDown[wParam] = 0;

		if (uMsg == WM_KEYDOWN && wParam < 256)
			io.KeysDown[wParam] = 1;

		auto functions = g_keyboardFunctions; for (auto & function : functions) function((DWORD)wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFF, (lParam >> 24) & 1, (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP), (lParam >> 30) & 1, (uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP));
	}
	break;
	case WM_CHAR:
		if (wParam > 0 && wParam < 0x10000)
			io.AddInputCharacter((unsigned short)wParam);
		break;
	}

	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}
