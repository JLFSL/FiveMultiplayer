#include "stdafx.h"

int main(int argc, char *argv[]) {
	// Provide the modification, version and gamename to the user.
	cout << "Loading " INFO_NAME "(" INFO_VERSION ") for " INFO_GAME_NAME << endl;

	CServer* g_Server = new CServer;

	// Create CServer and check if it worked
	if (!g_Server)
	{
		cout << "CServer is invalid" << endl;
		getc(stdin);
		return 1;
	}

	// Call OnLoad
	if (!g_Server->Load(argc, argv))
	{
		cout << "CServer could not be started" << endl;
		getc(stdin);
		return 1;
	}

	// Main Server Process Loop
	while (g_Server->IsActive())
	{
		g_Server->Process();
	}

	// Call OnUnload
	g_Server->Stop();

	// Destroy CServer
	SAFE_DELETE(g_Server);

	ExitProcess(EXIT_SUCCESS);
	return 1;
}