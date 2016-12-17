#include "stdafx.h"

int CPlayerEntity::Amount = 0;

CPlayerEntity::CPlayerEntity()
{
	
}

CPlayerEntity::~CPlayerEntity()
{
	cout << "[CPlayerEntity] Removing Player: " << Information.Name << " [" << Information.Guid << "]" << endl;

	Information = {};
	Statistics = {};
	Data = {};

	Information.Id = -1;

	Amount--;

	cout << "[CPlayerEntity] Players Online: " << g_Players.size() << endl;
}

void CPlayerEntity::Create(string Name, const char * Guid)
{
	Information.Name = Name;
	Information.Id = Amount;
	Information.Guid = Guid;

	Amount++;

	cout << "[CPlayerEntity] Added Player: " << Information.Name << " [" << Information.Guid << "]" << endl;
	cout << "[CPlayerEntity] Players Online: " << g_Players.size() << endl;
}

void CPlayerEntity::Pulse()
{
}

void CPlayerEntity::Update(Packet packet)
{
}