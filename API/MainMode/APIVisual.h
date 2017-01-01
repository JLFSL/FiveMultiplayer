#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		namespace Visual
		{
			void _ShowMessageAboveMap(const char *_message)
			{
				DLL_PUBLIC_I void ShowMessageAboveMap(const char *message);
				ShowMessageAboveMap(_message);
			}
		}
	}
#ifdef __cplusplus
}
#endif