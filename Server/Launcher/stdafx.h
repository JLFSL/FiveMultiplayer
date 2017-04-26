#pragma once

// Windows/UNIX
#ifdef _WIN32
#include <winsock2.h>
#include <Windows.h>
#else
#define _BSD_SOURCE

#include <dlfcn.h>
#include <sys/time.h>
#include <unistd.h>
#endif
#include <stdio.h>

// C++
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <memory>
#include <chrono>
#include <atomic>
#include <thread>
#define _USE_MATH_DEFINES
#include <math.h>

// Math
#include "CVector3.h"

// Shared
#include <Common.h>
//#include <CVector4.h>
#include <CMaths.h>
#include <SharedUtility.h>
#include <APIStructs.h>

// Vendor
	// Vendor.RakNet
	#include <RakNet/RakPeerInterface.h>
	#include <RakNet/BitStream.h>
	#include <RakNet/MessageIdentifiers.h>
	#include <RakNet/RPC4Plugin.h>
	#include <RakNet/DirectoryDeltaTransfer.h>
	#include <RakNet/FileListTransfer.h>
	#include <RakNet/IncrementalReadInterface.h>
	#include <RakNet/RakNetStatistics.h>
	using namespace RakNet;

	// Vendor.LibCurl
	#include <LibCurl/curl/curl.h>
// End of Vendor

// Server.Launcher
	// Include
	#include "IniReader.h"
	#include "ini.h"

	// Network
	#include "CNetworkManager.h"
	#include "CPlayerEntity.h"
	#include "CVehicleEntity.h"
	#include "CObjectEntity.h"
	#include "CNPCEntity.h"
	#include "CCheckpointEntity.h"
	#include "CServerEntity.h"
	#include "NetworkSync.h"

	// Server
	#include "CConfig.h"
	#include "CWorld.h"
	#include "CServer.h"
	#include "CModelCache.h"

	// API
	#include "CAPI.h"
	// Callbacks
	#include "API_Callback_Network.h"
	#include "API_Callback_Checkpoint.h"
	// Functions
	#include "API_Server.h"
	#include "API_World.h"
	#include "API_Entity.h"
	#include "API_Vehicle.h"
	#include "API_Visual.h"
	#include "API_Player.h"
	#include "API_Object.h"
	#include "API_NPC.h"
	#include "API_Checkpoint.h"
	#include "API_CEF.h"

// End of Server.Launcher

extern CServer* g_Server;
extern CConfig*	g_Config;