#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <iostream>
using namespace std;

// Shared
#include <Common.h>
#include <CVector3.h>

// Vendor.RakNet
#include <RakNet/RakPeerInterface.h>
#include <RakNet/BitStream.h>
#include <RakNet/MessageIdentifiers.h>
#include <RakNet/RPC4Plugin.h>
#include <RakNet/DirectoryDeltaTransfer.h>
#include <RakNet/FileListTransfer.h>
#include <RakNet/IncrementalReadInterface.h>
using namespace RakNet;

// Server.Launcher
	// Server
	#include "CServer.h"

	// API
	#include "CAPI.h"

	#include "API_Server.h"

	// Network
	#include "CNetworkManager.h"
	//#include "CEntityManager.h"
	#include "CPlayer.h"
// End of Server.Launcher