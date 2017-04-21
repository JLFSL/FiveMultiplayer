#include "stdafx.h"

void CRPCNetwork::FinishedSync(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	CNetworkManager::g_ConnectionState = CONSTATE_COND;
	std::cout << "CRPCNetwork::FinishedSync" << std::endl;
}