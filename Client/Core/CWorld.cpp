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

	// Force streamout all entities
	CStreamer::ForceStreamOut();

	// Remove all existing entities
	if (!g_Entities.empty())
	{
		for (int i = (g_Entities.size() - 1); i > -1; i--)
		{
			g_Entities.erase(g_Entities.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Entities.shrink_to_fit();
	}

	// Remove all existing vehicles
	if (!g_Vehicles.empty())
	{
		for (int i = (g_Vehicles.size() - 1); i > -1; i--)
		{
			if (g_Vehicles[i].IsCreated())
				g_Vehicles[i].Destroy();
			g_Vehicles.erase(g_Vehicles.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Vehicles.shrink_to_fit();
	}

	// Remove all existing players
	if (!g_Players.empty())
	{
		for (int i = (g_Players.size() - 1); i > -1; i--)
		{
			if (g_Players[i].IsCreated())
				g_Players[i].Destroy();
			g_Players.erase(g_Players.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Players.shrink_to_fit();
	}

	// Remove all existing objects
	if (!g_Objects.empty())
	{
		for (int i = (g_Objects.size() - 1); i > -1; i--)
		{
			if (g_Objects[i].IsCreated())
				g_Objects[i].Destroy();
			g_Objects.erase(g_Objects.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Objects.shrink_to_fit();
	}

	if (!g_Npcs.empty())
	{
		// Remove all existing npcs
		for (int i = (g_Npcs.size() - 1); i > -1; i--)
		{
			if (g_Npcs[i].IsCreated())
				g_Npcs[i].Destroy();
			g_Npcs.erase(g_Npcs.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Npcs.shrink_to_fit();
	}

	// Remove all existing checkpoints
	if (!g_Checkpoints.empty())
	{
		for (int i = (g_Checkpoints.size() - 1); i > -1; i--)
		{
			g_Checkpoints[i].Destroy();
			g_Checkpoints.erase(g_Checkpoints.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Checkpoints.shrink_to_fit();
	}
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

void CWorld::LoadModel(const std::wstring model)
{
	int hash = GAMEPLAY::GET_HASH_KEY((char*)CString::utf16ToUtf8(model).c_str());
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash)) {
		STREAMING::REQUEST_MODEL(hash);
		while (!STREAMING::HAS_MODEL_LOADED(hash))
			WAIT(0);
	}
}

void CWorld::LoadModel(const int model)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model)) {
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model))
			WAIT(200);
	}
}