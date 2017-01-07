#include "stdafx.h"

namespace API
{
	namespace Visual
	{
		char *ThisNamespace = "API::Visual";

		void ShowMessageAboveMap(const char *message, const char *pic, int icontype, const char *sender, const char *subject)
		{
			RakNet::RakString rakMessage = RakNet::RakString(message);
			RakNet::RakString rakPic = RakNet::RakString(pic);
			RakNet::RakString rakSender = RakNet::RakString(sender);
			RakNet::RakString rakSubject = RakNet::RakString(subject);

			RakNet::BitStream sData;
			sData.Write(rakMessage);
			sData.Write(rakPic);
			sData.Write(icontype);
			sData.Write(rakSender);
			sData.Write(rakSubject);

			g_Network->GetRPC().Signal("ShowMessageAboveMap", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
		}
	}
}
