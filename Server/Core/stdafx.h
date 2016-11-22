#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <iostream>
using namespace std;

// Shared
#include "SharedUtility.h"
#include "Common.h"

// Server.Launcher


// Server.Core
#include "CServer.h"