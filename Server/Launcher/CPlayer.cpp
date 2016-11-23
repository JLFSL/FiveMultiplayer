#include "stdafx.h"

CPlayerEntity::CPlayerEntity()
{
}

CPlayerEntity::~CPlayerEntity()
{
}

void CPlayerEntity::Pulse()
{
	/*if (m_ulLastSyncSent + (1000 / CServer::GetInstance()->GetSyncRate()) <= SharedUtility::GetTime())
	{
		RakNet::BitStream bitStream;
		bitStream.Write(GetId());
		bitStream.Write(CServer::GetInstance()->GetNetworkModule()->GetPlayerPing(GetId()));

		Serialize(&bitStream, m_eLastSyncPackageType);
		m_ulLastSyncSent = SharedUtility::GetTime();

		if (m_controlState.IsAiming() || m_controlState.IsFiring())
		{
			Serialize(&bitStream, RPC_PACKAGE_TYPE_PLAYER_WEAPON);
		}

		CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_SYNC_PACKAGE), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, -1, true);
	}*/
}
