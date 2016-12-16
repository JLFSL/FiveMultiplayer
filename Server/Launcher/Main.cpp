#include "stdafx.h"

int main(int argc, char *argv[]) {
	// Provide the modification, version and gamename to the user.
	cout << "Loading " INFO_NAME "(" INFO_VERSION ") for " INFO_GAME_NAME << endl;

	// Create CServer
	CServer* g_Server = new CServer;

	Sleep(500);

	// Check if CServer is created
	if (!g_Server)
	{
		cout << "CServer is invalid" << endl;
		getc(stdin);
		return 1;
	}

	Sleep(500);

	// Call OnLoad
	if (!g_Server->Load(argc, argv))
	{
		cout << "CServer could not be started" << endl;
		getc(stdin);
		return 1;
	}

	Sleep(500);

	// Main Server Process Loop
	while (g_Server->IsActive())
	{
		g_Server->Process();
	}

	Sleep(500);

	// Call OnUnload
	g_Server->Stop();

	// Destroy CServer
	SAFE_DELETE(g_Server);

	ExitProcess(EXIT_SUCCESS);
	return 1;
}