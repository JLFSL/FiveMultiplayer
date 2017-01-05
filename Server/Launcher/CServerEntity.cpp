#include "stdafx.h"

int CServerEntity::Create()
{
	if(g_Entities.empty())
		Data.Id = 0;
	else
		Data.Id = g_Entities.size() + 1;

	return Data.Id;
}

CVector3 CServerEntity::GetPosition()
{
	switch(Data.type)
	{
	case Player:
		if (!g_Players.empty())
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if(g_Players[i].GetId() == Data.Id)
					return g_Players[i].GetPosition();
			}
		}

		cout << endl << "[CServerEntity::GetPosition] Invalid player ID: " << Data.Id << endl;
		break;
	case Vehicle:
		cout << endl << "[CServerEntity::GetPosition] Invalid vehicle ID: " << Data.Id << endl;
		break;
	case Object:
		cout << endl << "[CServerEntity::GetPosition] Invalid object ID: " << Data.Id << endl;
		break;
	default:
		cout << endl << "[CServerEntity::GetPosition] Invalid entity" << endl;
		break;
	}
}

void CServerEntity::SetPosition(CVector3 position)
{
	switch(Data.type)
	{
	case Player:
		if (!g_Players.empty())
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == Data.Id)
				{
					g_Players[i].SetPosition(position);
					return;
				}
			}
		}

		cout << endl << "[CServerEntity::SetPosition] Invalid player ID: " << Data.Id << endl;
		break;
	case Vehicle:
		cout << endl << "[CServerEntity::SetPosition] Invalid vehicle ID: " << Data.Id << endl;
		break;
	case Object:
		cout << endl << "[CServerEntity::SetPosition] Invalid object ID: " << Data.Id << endl;
		break;
	default:
		cout << endl << "[CServerEntity::SetPosition] Invalid entity" << endl;
		break;
	}
}