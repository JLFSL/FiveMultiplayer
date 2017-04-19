#include "stdafx.h"
#include <tchar.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char InstallDir[MAX_PATH];
	char InstallExe[MAX_PATH];
	char CorePath[MAX_PATH];
	char CurDir[MAX_PATH];

	string CmdLine = lpCmdLine;
	bool customDir = false;
	GetCurrentDirectoryA(sizeof(CurDir), CurDir);

	if (!Util::ReadRegistryString(HKEY_CURRENT_USER, INFO_LOC_REG, INFO_LOC_REG2, NULL, InstallDir, sizeof(InstallDir)) || !Util::Exists(InstallDir)) {
		if (Util::ShowMessageBox("Your " INFO_GAME_NAME " folder has not been set yet, do you wish to set it now?",
			(MB_ICONEXCLAMATION | MB_OKCANCEL)) == IDOK) {

			BROWSEINFOA browseInfo = { 0 };
			browseInfo.lpszTitle = INFO_NAME " - Pick a Directory";
			ITEMIDLIST * pItemIdList = SHBrowseForFolderA(&browseInfo);

			if (pItemIdList != NULL) {
				// Get the name of the selected folder
				if (SHGetPathFromIDListA(pItemIdList, InstallDir))
					customDir = true;

				// Free any memory used
				IMalloc * pIMalloc = 0;
				if (SUCCEEDED(SHGetMalloc(&pIMalloc))) {
					pIMalloc->Free(pItemIdList);
					pIMalloc->Release();
				}
			}
		}

		if (!customDir) {
			Util::ShowMessageBox("Failed to retrieve the install directory from registry or browser window. Cannot launch " INFO_NAME ".", MB_ICONEXCLAMATION);
			return 1;
		}
	}

	sprintf_s(InstallExe, "%s\\" INFO_GAME_EXECUTABLE, InstallDir);
	sprintf_s(CorePath, "%s\\" INFO_CLIENT_CORE, CurDir);

	if (!Util::Exists(InstallExe))
		return Util::ShowMessageBox("Failed to find " INFO_GAME_EXECUTABLE " in set directory. Cannot launch " INFO_NAME ".", MB_ICONEXCLAMATION);

	if (customDir)
		Util::WriteRegistryString(HKEY_CURRENT_USER, INFO_LOC_REG, INFO_LOC_REG2, InstallDir, strlen(InstallDir));

	if (!Util::Exists(CorePath))
		return Util::ShowMessageBox("Failed to find " INFO_CLIENT_CORE " in current directory. Cannot launch " INFO_NAME ".", MB_ICONEXCLAMATION);

	const int result = MessageBox(NULL, "Are you using the Steam version of the game?", "Steam Version", MB_YESNOCANCEL | MB_ICONQUESTION);

	switch (result)
	{
	case IDYES:
		ShellExecute(0, 0, "steam://rungameid/" INFO_GAME_STEAMAPPID, 0, 0, SW_SHOW);
		break;
	case IDNO:
		// Start Executable
		STARTUPINFO siStartupInfo;
		PROCESS_INFORMATION piProcessInfo;
		memset(&siStartupInfo, 0, sizeof(siStartupInfo));
		memset(&piProcessInfo, 0, sizeof(piProcessInfo));
		siStartupInfo.cb = sizeof(siStartupInfo);

		if (!CreateProcess(InstallExe, "", NULL, NULL, true, CREATE_SUSPENDED, NULL, InstallDir, &siStartupInfo, &piProcessInfo)) {
			Util::ShowMessageBox("Failed to start " INFO_GAME_EXECUTABLE ". Cannot launch " INFO_NAME ".");
			return 1;
		}

		ResumeThread(piProcessInfo.hThread);
		break;
	case IDCANCEL:
		return 0;
		break;
	}

	AllocConsole();

	bool Started = false;

	while (!Started) {
		if (Util::IsProcessRunning("GTA5.exe")) {
			DWORD ForePID, GamePID;

			Util::GetProcessIdFromProcessName("GTA5.exe", &GamePID);
			SetForegroundWindow(FindWindow(NULL, "Grand Theft Auto V"));

			HWND GameWindow = GetForegroundWindow();
			GetWindowThreadProcessId(GameWindow, &ForePID);

			if (GamePID == ForePID && IsWindowVisible(GameWindow))
			{
				int iReturn = Util::InjectLibraryIntoProcess(GamePID, CorePath);

				if (iReturn > 0)
				{
					if (iReturn == 1)
						Util::ShowMessageBox("Failed to write library path into remote process. Cannot launch " INFO_NAME ".");
					else if (iReturn == 2)
						Util::ShowMessageBox("Failed to create remote thread in remote process. Cannot launch " INFO_NAME ".");
					else if (iReturn == 3)
						Util::ShowMessageBox("Failed to open the remote process, Cannot launch " INFO_NAME ".");
				}
				else
				{
					Started = true;
				}
			}
		}
		Sleep(500);
	}
	FreeConsole();
}