#include "stdafx.h"

namespace Util
{
	bool ReadRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, const char * szDefault, char * szData, DWORD dwSize)
	{
		HKEY hKey = NULL;

		if (RegOpenKeyExA(hKeyLocation, szSubKey, NULL, KEY_READ, &hKey) == ERROR_SUCCESS)
		{
			DWORD dwType = REG_SZ;
			LONG lStatus = RegQueryValueExA(hKey, szKey, NULL, &dwType, (BYTE *)szData, &dwSize);
			RegCloseKey(hKey);
			return (lStatus == ERROR_SUCCESS);
		}

		if (szDefault)
			strncpy(szData, szDefault, dwSize);

		return false;
	}

	bool WriteRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, char * szData, DWORD dwSize)
	{
		HKEY hKey = NULL;
		RegOpenKeyExA(hKeyLocation, szSubKey, NULL, KEY_WRITE, &hKey);

		if (!hKey)
			RegCreateKeyA(hKeyLocation, szSubKey, &hKey);

		if (hKey)
		{
			DWORD dwType = REG_SZ;
			RegSetValueExA(hKey, szKey, NULL, dwType, (BYTE *)szData, dwSize);
			RegCloseKey(hKey);
			return true;
		}

		return false;
	}
	bool Exists(const char * szPath)
	{
		struct stat St;
		return (stat(szPath, &St) == 0);
	}

	int ShowMessageBox(const char * szText, UINT uType)
	{
		return MessageBoxA(NULL, szText, INFO_NAME, uType);
	}

	bool GetProcessIdFromProcessName(char * szProcessName, DWORD * dwProcessId)
	{
		bool bReturn = false;

		// Create a tool help 32 process snapshot
		HANDLE hProcessSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (!hProcessSnapShot)
			return false;

		PROCESSENTRY32 ProcessEntry;
		ProcessEntry.dwSize = sizeof(ProcessEntry);

		if (Process32First(hProcessSnapShot, &ProcessEntry))
		{
			// Enumerate through all processes
			while (Process32Next(hProcessSnapShot, &ProcessEntry))
			{
				// Check the process name to see if it matches szProcessName
				if (!strcmp((char *)ProcessEntry.szExeFile, szProcessName))
				{
					// It matches, set the process id (if required) and return true
					if (dwProcessId)
						*dwProcessId = ProcessEntry.th32ProcessID;

					bReturn = true;
					break;
				}
			}
		}

		// Close the snapshot handle
		CloseHandle(hProcessSnapShot);
		return bReturn;
	}

	bool IsProcessRunning(char * szProcessName)
	{
		// Simply return the value of GetProcessIdFromProcessName
		return GetProcessIdFromProcessName(szProcessName, NULL);
	}

	int InjectLibraryIntoProcess(HANDLE hProcess, const char * szLibraryPath)
	{
		int iReturn = 0;

		// Get the length of the library path
		size_t sLibraryPathLen = (strlen(szLibraryPath) + 1);

		// Allocate the a block of memory in our target process for the library path
		void * pRemoteLibraryPath = VirtualAllocEx(hProcess, NULL, sLibraryPathLen, MEM_COMMIT, PAGE_READWRITE);

		// Write our library path to the allocated block of memory
		SIZE_T sBytesWritten = 0;
		WriteProcessMemory(hProcess, pRemoteLibraryPath, (void *)szLibraryPath, sLibraryPathLen, &sBytesWritten);

		if (sBytesWritten != sLibraryPathLen)
		{
			// Failed to write the library path
			iReturn = 1;
		}
		else
		{
			// Get the handle of Kernel32.dll
			HMODULE hKernel32 = GetModuleHandle("Kernel32");

			// Get the address of the LoadLibraryA function from Kernel32.dll
			FARPROC pfnLoadLibraryA = GetProcAddress(hKernel32, "LoadLibraryA");

			// Create a thread inside the target process to load our library
			HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pfnLoadLibraryA, pRemoteLibraryPath, 0, NULL);

			if (hThread)
			{
				// Wait for the created thread to end
				WaitForSingleObject(hThread, INFINITE);

				// Close our thread handle
				CloseHandle(hThread);
			}
			else
			{
				// Thread creation failed
				iReturn = 2;
			}
		}

		// Free the allocated block of memory inside the target process
		VirtualFreeEx(hProcess, pRemoteLibraryPath, sizeof(pRemoteLibraryPath), MEM_RELEASE);
		return iReturn;
	}

	int InjectLibraryIntoProcess(DWORD dwProcessId, const char * szLibraryPath)
	{
		// Open our target process
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

		if (!hProcess)
		{
			// Failed to open the process
			return 3;
		}

		// Inject the library into the process
		int iReturn = InjectLibraryIntoProcess(hProcess, szLibraryPath);

		// Close the process handle
		CloseHandle(hProcess);
		return iReturn;
	}

	inline bool exists(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}
}
