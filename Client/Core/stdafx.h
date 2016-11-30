#pragma once

// Windows
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

using namespace std;

// Client.Core
	// Network
	#include "CNetworkManager.h"

	// Client
	#include "CCore.h"

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

// Shared
#include "../../Shared/CVector3.h"
#include "../../Shared/Common.h"

// Vendor
	// Vendor.MinHook
	#include "MinHook.h"