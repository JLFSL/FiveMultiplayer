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
	// do linux api stuff
#endif

	while (1);
	return 1;
}