#pragma once

extern "C" {
	namespace API
	{
		class Server
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static void PrintMessage(const std::wstring message);
		};
	}
}
