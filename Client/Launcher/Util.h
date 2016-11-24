#pragma once

namespace Util
{
	// Read a string from the registry
	bool ReadRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, const char * szDefault, char * szData, DWORD dwSize);

	// Write a string to the registry
	bool WriteRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, char * szData, DWORD dwSize);

	// Check if a path exists
	bool Exists(const char * szPath);

	// Show our custom messagebox
	int ShowMessageBox(const char * szText, UINT uType = (MB_ICONEXCLAMATION | MB_OK));

	// Get PID from processname
	bool GetProcessIdFromProcessName(char * szProcessName, DWORD * dwProcessId);

	// Check if process is running
	bool IsProcessRunning(char * szProcessName);

	// Inject the library into the specified process
	int InjectLibraryIntoProcess_go(HANDLE hProcess, const char * szLibraryPath);

	// Get the process id's handle then inject the library into it
	int InjectLibraryIntoProcess(DWORD dwProcessId, const char * szLibraryPath);
}
