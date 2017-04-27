#ifndef __APICEF_H__
#define __APICEF_H__
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
#endif