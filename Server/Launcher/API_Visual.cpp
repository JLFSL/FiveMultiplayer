#include "stdafx.h"

namespace API
{
	namespace Visual
	{
		char *ThisNamespace = "API::Visual";

		void ShowMessageAboveMap(const char *message, const char *pic, int icontype, const char *sender, const char *subject)
		{
			RakNet::RakString _message = RakNet::RakString(message);
			RakNet::RakString _pic = RakNet::RakString(pic);
			RakNet::RakString _sender = RakNet::RakString(sender);
			RakNet::RakString _subject = RakNet::RakString(subject);

			RakNet::BitStream sData;
			sData.Write(_message);
			sData.Write(_pic);
			sData.Write(icontype);
			sData.Write(_sender);
			sData.Write(_subject);

			g_Network->GetRPC().Signal("ShowMessageAboveMap", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
		}
	}
}
