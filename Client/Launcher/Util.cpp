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
}
