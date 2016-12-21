// Game Information
#define INFO_GAME_NAME			"Grand Theft Auto 5"
#define INFO_GAME_EXECUTABLE	"GTAVLauncher.exe"
#define INFO_GAME_STEAMAPPID	"271590"

	// Game Path
	#define INFO_GAME_LOC_REG		"SOFTWARE\\WOW6432Node\\Rockstar Games\\Grand Theft Auto VA"
	#define INFO_GAME_LOC_REG2		"InstallFolder"

// Modification Information
#define INFO_NAME			"Five Multiplayer"
#define INFO_NAME_SHORT		"FiveMP"
#define INFO_VERSION		"0.2a DEV"

	// Client Path
	#define INFO_LOC_REG "Software\\" INFO_NAME_SHORT
	#define INFO_LOC_REG2 INFO_NAME_SHORT

// Modification Files
#define INFO_CLIENT_CORE	"Client.Core" LIBRARY_EXTENSION

// Server Defines
#define MAX_PLAYERS			50

// Connection
#define CON_IP		"127.0.0.1"
#define CON_PORT	2322
#define CON_PORT_C	"0"
#define CON_PASS	""

// Connection Status
#define CONSTATE_DISC	0
#define CONSTATE_CONN	1
#define CONSTATE_COND	2
#define CONSTATE_FAIL	3

#ifdef WIN32
#define LIBRARY_EXTENSION ".dll"
#else
#define LIBRARY_EXTENSION ".so"
#endif

#ifdef _WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C"
#endif

#define SAFE_DELETE(memory) if(memory) { delete memory; memory = NULL; }

#ifdef NDEBUG
#define INFO_BUILD "Release"
#else
#define INFO_BUILD "Debug"
#endif

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport)
#endif
#else
#define DLL_PUBLIC 
#endif

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC_I __attribute__ ((dllimport))
#else
#define DLL_PUBLIC_I __declspec(dllimport)
#endif
#else
#define DLL_PUBLIC_I 
#endif

#ifndef _WIN32
unsigned int timeGetTime()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return now.tv_usec / 1000;
}
#endif