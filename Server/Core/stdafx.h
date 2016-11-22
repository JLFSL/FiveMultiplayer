#pragma once

#ifndef BUILDING_DLL
#define BUILDING_DLL
#endif
#if defined _WIN32 || defined __CYGWIN__
#include <Windows.h>
#define API_WIN
#else
#if __GNUC__ >= 4
#include <dlfcn.h>
#define API_OTHER
#else
#endif
#endif

#include <iostream>

using namespace std;