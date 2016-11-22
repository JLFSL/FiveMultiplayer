#include "stdafx.h"

/*int main(int argc, char *argv[]) {
#ifdef API_WIN
	typedef VOID(CALLBACK* LPFN_DHFDLL)();
	HINSTANCE hInst = ::LoadLibraryA("plugins/API.Lua.dll");
	if (NULL != hInst)
	{
		LPFN_DHFDLL API_Initialize =
			(LPFN_DHFDLL)::GetProcAddress(hInst, "API_Initialize");
		API_Initialize();
		::FreeLibrary(hInst);
	}
#else
	void* handle = dlopen("plugins/API.Lua.so", RTLD_LAZY);

	if (!handle) {
		cerr << "Cannot open library: " << dlerror() << '\n';
		return 1;
	}

	// load the symbol
	cout << "Loading symbol hello...\n";
	typedef void(*API_Initialize_t)();

	// reset errors
	dlerror();
	API_Initialize_t API_Begin = (API_Initialize_t)dlsym(handle, "API_Initialize");
	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		cerr << "Cannot load symbol 'API_Initialize': " << dlsym_error << '\n';
		dlclose(handle);
		return 1;
	}

	// use it to do the calculation
	cout << "Calling API_Initialize...\n";
	API_Begin();

	// close the library
	cout << "Closing library...\n";
	dlclose(handle);
#endif

	while (1);
	return 1;
}

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#define DLL_PUBLIC 
#endif

extern "C" DLL_PUBLIC int SendMessageToPlayer(int playerid, const char *message)
{
	cout << "SendMessageToPlayer was called (" << playerid << "): " << message << endl;
	return 1;
}*/