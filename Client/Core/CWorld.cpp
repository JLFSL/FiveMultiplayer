#include "stdafx.h"

std::vector<CWorld::IPL> CWorld::g_IPLs;

void CWorld::Initialize()
{

}

void CWorld::Destroy()
{
	// Reset IPLs to their default states
	for (int i = (g_IPLs.size() - 1); i > -1; i--)
	{
		if (g_IPLs[i].defaultState)
		{
			STREAMING::REQUEST_IPL((char*)g_IPLs[i].ipl.c_str());
		}
		else
		{
			STREAMING::REMOVE_IPL((char*)g_IPLs[i].ipl.c_str());
		}

		g_IPLs.erase(g_IPLs.begin() + i);
	}
	// Shrink vector so size is correct.
	g_IPLs.shrink_to_fit();
}

void CWorld::LoadIPL(std::wstring ipl)
{
	bool exists;
	for (int i = 0; i < g_IPLs.size(); i++) 
	{
		if (ipl.compare(g_IPLs[i].ipl) == 0)
		{
			g_IPLs[i].enabled = true;
			exists = true;
		}
	}

	if (!exists)
	{
		IPL newIPL;
		newIPL.ipl = ipl;
		newIPL.enabled = true;
		newIPL.defaultState = STREAMING::IS_IPL_ACTIVE((char*)CString::utf16ToUtf8(ipl).c_str());
	}

	STREAMING::REQUEST_IPL((char*)CString::utf16ToUtf8(ipl).c_str());
}

void CWorld::UnloadIPL(std::wstring ipl)
{
	bool exists;
	for (int i = 0; i < g_IPLs.size(); i++)
	{
		if (ipl.compare(g_IPLs[i].ipl) == 0)
		{
			g_IPLs[i].enabled = true;
			exists = true;
		}
	}

	if (!exists)
	{
		IPL newIPL;
		newIPL.ipl = ipl;
		newIPL.enabled = false;
		newIPL.defaultState = STREAMING::IS_IPL_ACTIVE((char*)CString::utf16ToUtf8(ipl).c_str());
	}

	STREAMING::REMOVE_IPL((char*)CString::utf16ToUtf8(ipl).c_str());
}