#pragma once

// Windows
#include <Windows.h>
#include <stdint.h>
#include <time.h>
#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_map>

// Client.Core
	// Hooks
		// SudoMod
		#include "Logger.h"
		#include "Memory.h"
		#include "CrossMapping.h"
		#include "NativeInvoker.h"
		#include "Hooking.h"
		#include "NativeCaller.h"

		#include "Types.h"
		#include "Enums.h"
		#include "Natives.h"
		#include "Structs.h"

// Vendor
	// Vendor.MinHook
	#include "MinHook.h"