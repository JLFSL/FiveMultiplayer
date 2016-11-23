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
}
