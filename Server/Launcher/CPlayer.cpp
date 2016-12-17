#include "stdafx.h"

int CPlayerEntity::Amount = 0;

void CPlayerEntity::Create(string Name, const char *Guid, const char *Ip)
{
	Information.Name = Name;
	Information.Id = Amount;
	Information.Guid = Guid;
	Information.Ip = Ip;

	Amount++;

	cout << "[CPlayerEntity] Added Player: " << Information.Name << " [" << Information.Ip << "]" << endl;
	cout << "[CPlayerEntity] Players Online: " << Amount << endl;
}

void CPlayerEntity::Destroy()
{
	cout << "[CPlayerEntity] Removing Player: " << Information.Name << " [" << Information.Ip << "]" << endl;

	Information = {};
	Statistics = {};
	Data = {};

	Information.Id = -1;

	Amount--;

	cout << "[CPlayerEntity] Players Online: " << Amount << endl;
}

void CPlayerEntity::Pulse()
{
}

void CPlayerEntity::Update(Packet packet)
{
}