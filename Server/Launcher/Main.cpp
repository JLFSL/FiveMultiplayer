#include "stdafx.h"

CModule		* g_Module = NULL;
CInterface	* g_Server = NULL;

int main(int argc, char *argv[]) {
	// Provide the modification, version and gamename to the user.
	cout << "Loading " INFO_NAME "(" INFO_VERSION ") for " INFO_GAME << endl << endl;

	// Load our Module Loader
	g_Module = new CModule();

	// Use our Module Loader to load the Server.Core
	if (!g_Module->Load("Server.Core" LIBRARY_EXTENSION)) {
		getc(stdin);
		return 1;
	}

	// Retrieve exports from Server.Core
	typedef CInterface * (*GetServerInterface_t)();
	typedef void(*DestroyServerInterface_t)(CInterface * pServer);
	GetServerInterface_t fn_GetServerInterface = (GetServerInterface_t)g_Module->GetProcedureAddress("GetServerInterface");
	DestroyServerInterface_t fn_DestroyServerInterface = (DestroyServerInterface_t)g_Module->GetProcedureAddress("DestroyServerInterface");

	// Create CServer and check if it worked
	if (!(g_Server = fn_GetServerInterface()))
	{
		cout << "CServer is invalid" << endl;
		getc(stdin);
		return 1;
	}

	// Call OnLoad
	if (!g_Server->OnLoad(argc, argv))
	{
		cout << "CServer could not be started" << endl;
		getc(stdin);
		return 1;
	}

	// Main Server Process Loop
	while (g_Server->IsActive())
	{
		g_Server->Process();
		Sleep(10);
	}

	// Call OnUnload
	g_Server->OnUnload();

	// Destroy CServer
	fn_DestroyServerInterface(g_Server);

	getc(stdin);
	return 1;
}