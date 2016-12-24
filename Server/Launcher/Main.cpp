#include "stdafx.h"

CServer*			g_Server;

#ifndef _WIN32
void Sleep(unsigned int seconds) {
	sleep(seconds);
}
#endif

int main(int argc, char *argv[]) {
	// Provide the modification, version and gamename to the user.
	cout << "Loading " INFO_NAME "(" INFO_VERSION ") for " INFO_GAME_NAME << endl;

	// Create CServer
	g_Server = new CServer;

	// Check if CServer is created
	if (!g_Server)
	{
		cout << "[CServer] Invalid" << endl;
		getc(stdin);
		return 1;
	}

	// Call OnLoad
	if (!g_Server->Load(argc, argv))
	{
		cout << "[CServer] Could not be started" << endl;
		getc(stdin);
		return 1;
	}

	// Main Server Process Loop
	while (g_Server->IsActive())
	{
		g_Server->Process();
		Sleep(15);
	}

	// Call OnUnload
	g_Server->Stop();

	// Destroy CServer
	SAFE_DELETE(g_Server);
	return 1;
}