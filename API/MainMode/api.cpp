#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport)
#endif
#else
#define DLL_PUBLIC 
#endif

#include <iostream>

#include "../../Shared/Common.h"

extern "C" DLL_PUBLIC bool API_Initialize(void) {
	// When Plugin gets loaded
	std::cout << "init" << std::endl;
	return true;
}

extern "C" DLL_PUBLIC bool API_Close(void) {
	// When plugin gets unloaded
	std::cout << "close" << std::endl;
	return true;
}

extern "C" DLL_PUBLIC bool API_OnTick(void) {
	// Every server tick this gets called

	DLL_PUBLIC_I int ShowMessageAboveMap(const char *message);
	std::cout << ShowMessageAboveMap("I don't like people!") << std::endl;
	return true;
}
