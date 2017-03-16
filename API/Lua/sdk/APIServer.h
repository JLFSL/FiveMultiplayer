#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Server
		{
		public:
			DLL_PUBLIC_I static void PrintMessage(const std::string  message);
		};
	}
#ifdef __cplusplus
}
#endif