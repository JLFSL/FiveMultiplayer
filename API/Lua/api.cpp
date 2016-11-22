#include "inc_lua/lua.hpp"

#include <iostream>
using namespace std;

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#define DLL_PUBLIC 
#endif

extern "C" DLL_PUBLIC void API_Begin(void) {
	cout << "Test!" << endl;
}