#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		namespace Server
		{
			void _PrintMessage(const char *_message)
			{
				DLL_PUBLIC_I void PrintMessage(const char *message);
				PrintMessage(_message);
			}
		}
	}
#ifdef __cplusplus
}
#endif