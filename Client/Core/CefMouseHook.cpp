#include "stdafx.h"

HHOOK CefMouseHook::Hook = nullptr;
bool CefMouseHook::Visible = true;
MSG CefMouseHook::msg;

void CefMouseHook::InstallHook() {
	if (!(Hook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookCallback, NULL, 0))) {
		std::cout << "cef: couldnt install mouse hook" << std::endl;
	}
	if (ShowCursor(true) == 1)
		ShowCursor(true);
}

void CefMouseHook::UninstallHook() {
	UnhookWindowsHookEx(Hook);
}

int CefMouseHook::Messages() {
	
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1);
	}
	UninstallHook();
	return (int)msg.wParam;
}


void CefMouseHook::ForegroundCheck() {
	while (msg.message != WM_QUIT) {
		HWND forgnd = GetForegroundWindow();

		int bufferLen = GetWindowTextLength(forgnd) + 1;
		std::string wnd_ftitle(bufferLen, '\0');
		GetWindowTextA(forgnd, &wnd_ftitle[0], bufferLen);

		if (std::strcmp((char*)wnd_ftitle.c_str(), "Grand Theft Auto V") == 0) {
			if (!Visible)
				Visible = true;
		}
		else {
			if (Visible)
				Visible = false;
		}

		Sleep(100); //10th of a second sleep as we don't need to check that frequently
	}
	return;
}

LRESULT WINAPI MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == 0 && CefMouseHook::IsVisible()) {
		//ImGuiIO& io = ImGui::GetIO();

		CefMouseEvent mouseEvent;
		POINT pos;
		RECT rect;

		switch (wParam) {
		case WM_LBUTTONDOWN:
			//io.MouseDown[0] = true;

			GetCursorPos(&pos);
			mouseEvent.x = pos.x;
			mouseEvent.y = pos.y;
			mouseEvent.modifiers = EVENTFLAG_LEFT_MOUSE_BUTTON;
			CefRenderer::getBrowser()->GetHost()->SendMouseClickEvent(mouseEvent, MBT_LEFT, false, 1);
			break;
		case WM_LBUTTONUP:
			//io.MouseDown[0] = false;

			GetCursorPos(&pos);
			mouseEvent.x = pos.x;
			mouseEvent.y = pos.y;
			mouseEvent.modifiers = EVENTFLAG_LEFT_MOUSE_BUTTON;
			CefRenderer::getBrowser()->GetHost()->SendMouseClickEvent(mouseEvent, MBT_LEFT, true, 1);
			break;
		case WM_RBUTTONDOWN:
			//io.MouseDown[1] = true;
			break;
		case WM_RBUTTONUP:
			//io.MouseDown[1] = false;

			GetCursorPos(&pos);
			mouseEvent.x = pos.x;
			mouseEvent.y = pos.y;
			mouseEvent.modifiers = EVENTFLAG_RIGHT_MOUSE_BUTTON;
			CefRenderer::getBrowser()->GetHost()->SendMouseClickEvent(mouseEvent, MBT_RIGHT, true, 1);
			break;
		case WM_MBUTTONDOWN:
			//io.MouseDown[2] = true;
			break;
		case WM_MBUTTONUP:
			//io.MouseDown[2] = false;

			GetCursorPos(&pos);
			mouseEvent.x = pos.x;
			mouseEvent.y = pos.y;
			mouseEvent.modifiers = EVENTFLAG_MIDDLE_MOUSE_BUTTON;
			CefRenderer::getBrowser()->GetHost()->SendMouseClickEvent(mouseEvent, MBT_MIDDLE, true, 1);
			break;
		case WM_MOUSEWHEEL: {
			MSLLHOOKSTRUCT *pMhs = (MSLLHOOKSTRUCT *)lParam;
			short zDelta = HIWORD(pMhs->mouseData);

			if (zDelta > 0) {
				//io.MouseWheel += 0.2f;
			}
			else {
				//io.MouseWheel -= 0.2f;
			}
			break;
		}
		case WM_MOUSEMOVE:
			//io.MousePos.x = (signed short)(lParam);
			//io.MousePos.y = (signed short)(lParam >> 16);

			
			GetWindowRect(CefRenderer::getProcess(), &rect);

			GetCursorPos(&pos);
			mouseEvent.x = ( pos.x - rect.left);
			mouseEvent.y = ( pos.y - rect.top);
			mouseEvent.modifiers = EVENTFLAG_NONE;
			
			CefRenderer::getBrowser()->GetHost()->SendMouseMoveEvent(mouseEvent, false);
			break;
		case WM_KEYDOWN:
			if (wParam < 256)
				//io.KeysDown[wParam] = 1;
			break;
		case WM_KEYUP:
			if (wParam < 256)
				//io.KeysDown[wParam] = 0;
			break;
		case WM_CHAR:
			// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
			if (wParam > 0 && wParam < 0x10000)
				//io.AddInputCharacter((unsigned short)wParam);
			break;
		}
	}
	return CallNextHookEx(CefMouseHook::GetHook(), nCode, wParam, lParam);
}