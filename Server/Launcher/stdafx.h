#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <iostream>
using namespace std;

// Shared
#include "Common.h"

// Server.Core
#include "CServer.h"

// Server.Launcher
#include "CModule.h"