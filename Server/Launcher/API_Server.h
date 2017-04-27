#ifndef __APISERVER_H__
#define __APISERVER_H__
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
#endif