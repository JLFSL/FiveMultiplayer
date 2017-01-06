#pragma once

// Windows
#include <winsock2.h>
#include <Windows.h>
#include <stdint.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// DirectX // DirectInput
#include <d3d11.h>
#include <d3dcompiler.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// Windows C++
#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>

// Shared
#include "CVector3.h"
#include "CVector4.h"
#include "CMaths.h"
#include "Common.h"

// Vendor
	// Vendor.MinHook
	#include <MinHook/include/MinHook.h>

	// Vendor.RakNet
	#include <RakNet/RakPeerInterface.h>
	#include <RakNet/BitStream.h>
	#include <RakNet/MessageIdentifiers.h>
	#include <RakNet/RPC4Plugin.h>
	#include <RakNet/DirectoryDeltaTransfer.h>
	#include <RakNet/FileListTransfer.h>
	#include <RakNet/IncrementalReadInterface.h>
	using namespace RakNet;

	// Vendor.CEF
	#include <include/cef_app.h>
	#include <include/cef_client.h>
	#include <include/cef_render_handler.h>
	#include <include/cef_sandbox_win.h>

	// Vendor.FW1FontWrapper
	#include <FW1FontWrapper/FW1FontWrapper.h>

// Client.Core
	// Hooks
		// SudoMod
		#include "Logger.h"
		#include "Memory.h"
		#include "types.h"
		#include "enums.h"
		#include "InputHook.h"
		#include "keyboard.h"
		#include "CrossMapping.h"
		#include "NativeInvoker.h"
		#include "nativeCaller.h"
		#include "natives.h"
		#include "Hooking.h"
		#include "Structs.h"
		#include "script.h"
	
	// Include
	#include "IniReader.h"
	#include "ini.h"

	// Game
	#include "Scripts.h"
	#include "Doors.h"
	#include "Animations.h"

	// Entity
	#include "CPlayerEntity.h"
	#include "CLocalPlayer.h"

	// Network
	#include "CNetworkManager.h"
	#include "CRPCManager.h"
		// RPC Handlers
		#include "CRPCVisual.h"

	// Client
	#include "CCore.h"
	#include "CConfig.h"
	#include "CVisual.h"

	// Graphics
		// UI
			// CEF
			#include "RenderHandler.h"
			#include "CefRenderer.h"
			
			// ImGui
			#include "imgui/imgui.h"
			#include "imgui/imgui_impl_dx11.h"
			#define IMGUI_DEFINE_MATH_OPERATORS
			#define IMGUI_DEFINE_PLACEMENT_NEW
			#include "imgui/imgui_internal.h"

		// Direct X 11
		#include "DirectXRenderer.h"
		#include "DirectXDraw.h"

extern CCore *g_Core;
extern CConfig *g_Config;