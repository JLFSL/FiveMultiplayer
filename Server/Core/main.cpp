#include "stdafx.h"

int main(int argc, char *argv[]) {
#ifdef API_WIN
	typedef VOID(CALLBACK* LPFN_DHFDLL)();
	HINSTANCE hInst = ::LoadLibraryA("plugins/API.Lua.dll");
	if (NULL != hInst)
	{
		LPFN_DHFDLL API_Begin =
			(LPFN_DHFDLL)::GetProcAddress(hInst, "API_Begin");
		API_Begin();
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
	typedef void(*API_Begin_t)();

	// reset errors
	dlerror();
	API_Begin_t API_Begin = (API_Begin_t)dlsym(handle, "API_Begin");
	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		cerr << "Cannot load symbol 'API_Begin': " << dlsym_error << '\n';
		dlclose(handle);
		return 1;
	}

	// use it to do the calculation
	cout << "Calling API_Begin...\n";
	begin();

	// close the library
	cout << "Closing library...\n";
	dlclose(handle);
#endif

	while (1);
	return 1;
}