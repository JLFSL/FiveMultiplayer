#include "stdafx.h"

WNDPROC CefInput::Hook = nullptr;
bool CefInput::Visible = true;
MSG CefInput::msg;

void CefInput::InstallHook() {
	Hook = (WNDPROC)SetWindowLongPtr(FindWindowA(0, "Grand Theft Auto V"), GWLP_WNDPROC, (LONG_PTR)HookedWndProc);
}

void CefInput::UninstallHook() {
	//UnhookWindowsHookEx(Hook);
}

int CefInput::Messages() {
	
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


void CefInput::ForegroundCheck() {
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

bool isKeyDown(WPARAM wparam)
{
	return (GetKeyState(wparam) & 0x8000) != 0;
}

int GetCefKeyboardModifiers(WPARAM wparam, LPARAM lparam)
{
	int modifiers = 0;
	if (isKeyDown(VK_SHIFT))
		modifiers |= EVENTFLAG_SHIFT_DOWN;
	if (isKeyDown(VK_CONTROL))
		modifiers |= EVENTFLAG_CONTROL_DOWN;
	if (isKeyDown(VK_MENU))
		modifiers |= EVENTFLAG_ALT_DOWN;

	// Low bit set from GetKeyState indicates "toggled".
	if (::GetKeyState(VK_NUMLOCK) & 1)
		modifiers |= EVENTFLAG_NUM_LOCK_ON;
	if (::GetKeyState(VK_CAPITAL) & 1)
		modifiers |= EVENTFLAG_CAPS_LOCK_ON;

	switch (wparam)
	{
	case VK_RETURN:
		if ((lparam >> 16) & KF_EXTENDED)
			modifiers |= EVENTFLAG_IS_KEY_PAD;
		break;
	case VK_INSERT:
	case VK_DELETE:
	case VK_HOME:
	case VK_END:
	case VK_PRIOR:
	case VK_NEXT:
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
		if (!((lparam >> 16) & KF_EXTENDED))
			modifiers |= EVENTFLAG_IS_KEY_PAD;
		break;
	case VK_NUMLOCK:
	case VK_NUMPAD0:
	case VK_NUMPAD1:
	case VK_NUMPAD2:
	case VK_NUMPAD3:
	case VK_NUMPAD4:
	case VK_NUMPAD5:
	case VK_NUMPAD6:
	case VK_NUMPAD7:
	case VK_NUMPAD8:
	case VK_NUMPAD9:
	case VK_DIVIDE:
	case VK_MULTIPLY:
	case VK_SUBTRACT:
	case VK_ADD:
	case VK_DECIMAL:
	case VK_CLEAR:
		modifiers |= EVENTFLAG_IS_KEY_PAD;
		break;
	case VK_SHIFT:
		if (isKeyDown(VK_LSHIFT))
			modifiers |= EVENTFLAG_IS_LEFT;
		else if (isKeyDown(VK_RSHIFT))
			modifiers |= EVENTFLAG_IS_RIGHT;
		break;
	case VK_CONTROL:
		if (isKeyDown(VK_LCONTROL))
			modifiers |= EVENTFLAG_IS_LEFT;
		else if (isKeyDown(VK_RCONTROL))
			modifiers |= EVENTFLAG_IS_RIGHT;
		break;
	case VK_MENU:
		if (isKeyDown(VK_LMENU))
			modifiers |= EVENTFLAG_IS_LEFT;
		else if (isKeyDown(VK_RMENU))
			modifiers |= EVENTFLAG_IS_RIGHT;
		break;
	case VK_LWIN:
		modifiers |= EVENTFLAG_IS_LEFT;
		break;
	case VK_RWIN:
		modifiers |= EVENTFLAG_IS_RIGHT;
		break;
	}
	return modifiers;
}

LRESULT WINAPI HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	if (CefInput::IsVisible()) 
	{
		ImGuiIO& io = ImGui::GetIO();
		
		CefKeyEvent keyEvent;
		CefMouseEvent mouseEvent;

		POINT pos;
		RECT rect;
		int delta;

		switch (uMsg)
		{
			case WM_LBUTTONDOWN:
				io.MouseDown[0] = true;

				GetWindowRect(CefRenderer::getProcess(), &rect);
				GetCursorPos(&pos);

				mouseEvent.x = (pos.x - rect.left);
				mouseEvent.y = (pos.y - rect.top);
				mouseEvent.modifiers = EVENTFLAG_LEFT_MOUSE_BUTTON;

				CefRenderer::getBrowser()->GetHost()->SendMouseClickEvent(mouseEvent, MBT_LEFT, false, 1);
				break;
			case WM_LBUTTONUP:
				io.MouseDown[0] = false;

				GetWindowRect(CefRenderer::getProcess(), &rect);
				GetCursorPos(&pos);

				mouseEvent.x = (pos.x - rect.left);
				mouseEvent.y = (pos.y - rect.top);
				mouseEvent.modifiers = EVENTFLAG_LEFT_MOUSE_BUTTON;

				CefRenderer::getBrowser()->GetHost()->SendMouseClickEvent(mouseEvent, MBT_LEFT, true, 1);
				break;
			case WM_RBUTTONDOWN:
				io.MouseDown[1] = true;

				/*
					GetWindowRect(CefRenderer::getProcess(), &rect);

					GetCursorPos(&pos);
					mouseEvent.x = (pos.x - rect.left);
					mouseEvent.y = (pos.y - rect.top);
					mouseEvent.modifiers = EVENTFLAG_RIGHT_MOUSE_BUTTON;

					CefRenderer::getBrowser()->GetHost()->SendMouseClickEvent(mouseEvent, MBT_RIGHT, false, 1);
				*/
				break;
			case WM_RBUTTONUP:
				io.MouseDown[1] = false;

				/*
					GetWindowRect(CefRenderer::getProcess(), &rect);
					GetCursorPos(&pos);

					mouseEvent.x = (pos.x - rect.left);
					mouseEvent.y = (pos.y - rect.top);
					mouseEvent.modifiers = EVENTFLAG_RIGHT_MOUSE_BUTTON;

					CefRenderer::getBrowser()->GetHost()->SendMouseClickEvent(mouseEvent, MBT_RIGHT, true, 1);
				*/
				break;
			case WM_MBUTTONDOWN:
				io.MouseDown[2] = true;

				GetWindowRect(CefRenderer::getProcess(), &rect);
				GetCursorPos(&pos);

				mouseEvent.x = (pos.x - rect.left);
				mouseEvent.y = (pos.y - rect.top);
				mouseEvent.modifiers = EVENTFLAG_MIDDLE_MOUSE_BUTTON;

				CefRenderer::getBrowser()->GetHost()->SendMouseClickEvent(mouseEvent, MBT_MIDDLE, false, 1);
				break;
			case WM_MBUTTONUP:
				io.MouseDown[2] = false;

				GetWindowRect(CefRenderer::getProcess(), &rect);
				GetCursorPos(&pos);

				mouseEvent.x = (pos.x - rect.left);
				mouseEvent.y = (pos.y - rect.top);
				mouseEvent.modifiers = EVENTFLAG_MIDDLE_MOUSE_BUTTON;

				CefRenderer::getBrowser()->GetHost()->SendMouseClickEvent(mouseEvent, MBT_MIDDLE, true, 1);
				break;
			case WM_MOUSEWHEEL:
				delta = GET_WHEEL_DELTA_WPARAM(wParam);
				
				GetWindowRect(CefRenderer::getProcess(), &rect);
				GetCursorPos(&pos);

				mouseEvent.x = (pos.x - rect.left);
				mouseEvent.y = (pos.y - rect.top);

				CefRenderer::getBrowser()->GetHost()->SendMouseWheelEvent(mouseEvent, 0, delta);
				break;
			case WM_MOUSEMOVE:
				io.MousePos.x = (signed short)(lParam);
				io.MousePos.y = (signed short)(lParam >> 16);
				GetWindowRect(CefRenderer::getProcess(), &rect);

				GetCursorPos(&pos);
				mouseEvent.x = (pos.x - rect.left);
				mouseEvent.y = (pos.y - rect.top);
				mouseEvent.modifiers = EVENTFLAG_NONE;

				CefRenderer::getBrowser()->GetHost()->SendMouseMoveEvent(mouseEvent, false);
				break;
			case WM_KEYDOWN:
				if (wParam < 256)
					io.KeysDown[wParam] = 1;

				keyEvent.windows_key_code = wParam;
				keyEvent.native_key_code = lParam;
				keyEvent.modifiers = GetCefKeyboardModifiers(wParam, lParam);

				if (uMsg != WM_CHAR)
				{
					keyEvent.type = (uMsg == WM_KEYDOWN) ? KEYEVENT_RAWKEYDOWN : KEYEVENT_KEYUP;
				}
				else
				{
					keyEvent.type = KEYEVENT_CHAR;
				}

				CefRenderer::getBrowser()->GetHost()->SendKeyEvent(keyEvent);
				break;
			case WM_KEYUP:
				if (wParam < 256)
					io.KeysDown[wParam] = 0;

				if (wParam < 256)
					io.KeysDown[wParam] = 1;

				keyEvent.windows_key_code = wParam;
				keyEvent.native_key_code = lParam;
				keyEvent.modifiers = GetCefKeyboardModifiers(wParam, lParam);

				if (uMsg != WM_CHAR)
				{
					keyEvent.type = (uMsg == WM_KEYDOWN) ? KEYEVENT_RAWKEYDOWN : KEYEVENT_KEYUP;
				}
				else
				{
					keyEvent.type = KEYEVENT_CHAR;
				}

				CefRenderer::getBrowser()->GetHost()->SendKeyEvent(keyEvent);
				break;
			case WM_CHAR:
				if (wParam > 0 && wParam < 0x10000)
					io.AddInputCharacter((unsigned short)wParam);

				if (wParam < 256)
					io.KeysDown[wParam] = 1;

				keyEvent.windows_key_code = wParam;
				keyEvent.native_key_code = lParam;
				keyEvent.modifiers = GetCefKeyboardModifiers(wParam, lParam);

				if (uMsg != WM_CHAR)
				{
					keyEvent.type = (uMsg == WM_KEYDOWN) ? KEYEVENT_RAWKEYDOWN : KEYEVENT_KEYUP;
				}
				else
				{
					keyEvent.type = KEYEVENT_CHAR;
				}

				CefRenderer::getBrowser()->GetHost()->SendKeyEvent(keyEvent);
				break;
		}
	}
	return CallWindowProc(CefInput::GetHook(), hWnd, uMsg, wParam, lParam);
}