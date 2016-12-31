#include "stdafx.h"

namespace API
{
	namespace Visual
	{
		char *ThisNamespace = "API::Visual";

		void ShowMessageAboveMap(const char *message)
		{
			RakNet::RakString _message = RakNet::RakString(message);

			RakNet::BitStream sData;
			sData.Write(_message);

			g_Network->GetRPC().Signal("ShowMessageAboveMap", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
		}
	}
}
