#pragma once

// Windows
#include <winsock2.h>
#include <Windows.h>
#include <stdint.h>
#include <time.h>

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

	// Client
	#include "CCore.h"
	#include "CConfig.h"

extern CCore *g_Core;
extern CConfig *g_Config;