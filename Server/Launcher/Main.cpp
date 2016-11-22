#include "stdafx.h"

CModule	*g_Module = NULL;
CServer *g_Server = NULL;

int main(int argc, char *argv[]) {
	// Provide the modification, version and gamename to the user.
	cout << "Loading " INFO_NAME "(" INFO_VERSION ") for " INFO_GAME << endl << endl;

	// Load our Module Loader
	g_Module = new CModule();

	// Use our Module Loader to load the Server.Core
	if(!g_Module->Load("Server.Core" LIBRARY_EXTENSION))
		getc(stdin);

	typedef CServer * (*GetServerInterface_t)();
	typedef void(*DestroyServerInterface_t)(CServer * pServer);
	GetServerInterface_t pfnGetServerInterface = (GetServerInterface_t)g_Module->GetProcedureAddress("GetServerInterface");
	DestroyServerInterface_t pfnDestroyServerInterface = (DestroyServerInterface_t)g_Module->GetProcedureAddress("DestroyServerInterface");

	g_Server = pfnGetServerInterface();

	getc(stdin);
	return 1;
}