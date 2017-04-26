#pragma once
extern "C" {
	namespace API
	{
		class CEF
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static void LoadURL(const int entity, std::string url, std::string appcode = "", bool remote = false);
			DLL_PUBLIC static void JavaScriptCall(const int entity, std::string call);
		};
	}
}