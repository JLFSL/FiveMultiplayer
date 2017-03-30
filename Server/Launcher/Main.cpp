#include "stdafx.h"

CServer*			g_Server;

#ifndef _WIN32
void Sleep(unsigned int seconds) {
	sleep(seconds);
}
#endif

int main(int argc, char *argv[]) {
	// Provide the modification, version and gamename to the user.
	std::cout << "Loading " INFO_NAME "(" INFO_VERSION ") for " INFO_GAME_NAME << std::endl;

	// Create CServer
	g_Server = new CServer;

	// Check if CServer is created
	if (!g_Server)
	{
		std::cout << "[CServer] Invalid" << std::endl;
		getc(stdin);
		return 1;
	}

	// Call OnLoad
	if (!g_Server->Load(argc, argv))
	{
		std::cout << "[CServer] Could not be started" << std::endl;
		getc(stdin);
		return 1;
	}

	std::atomic<bool> run(true);
	std::thread Input(CServer::Input, std::ref(run));

	// Main Server Process Loop
	while (g_Server->IsActive())
	{
		g_Server->Process();
	}

	// Call OnUnload
	Input.join();
	g_Server->Stop();

	// Destroy CServer
	SAFE_DELETE(g_Server);
	return 1;
}