#include "stdafx.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char InstallDir[MAX_PATH];
	char InstallExe[MAX_PATH];

	string CmdLine = lpCmdLine;
	bool customDir = false;

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

	sprintf_s(InstallExe, "%s\\GTAVLauncher.exe", InstallDir);

	if (!Util::Exists(InstallExe))
		return Util::ShowMessageBox("Failed to find " INFO_GAME_EXECUTABLE " in set directory. Cannot launch " INFO_NAME ".", MB_ICONEXCLAMATION);

	if (customDir)
		Util::WriteRegistryString(HKEY_CURRENT_USER, INFO_LOC_REG, INFO_LOC_REG2, InstallDir, strlen(InstallDir));
}