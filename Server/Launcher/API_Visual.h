#ifndef __APIVISUAL_H__
#define __APIVISUAL_H__
extern "C" {
	namespace API
	{
		class Visual
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static void ShowMessageAboveMap(const std::wstring message, const std::wstring pic, const int icontype, const std::wstring sender, const std::wstring subject);
			DLL_PUBLIC static void ShowMessageAboveMapToPlayer(const int entity, const std::wstring message, const std::wstring pic, const int icontype, const std::wstring sender, const std::wstring subject);
			
			DLL_PUBLIC static void ShowSubtitle(const std::wstring message, const int duration, const bool shownow);
			DLL_PUBLIC static void ShowSubtitleToPlayer(const int entity, const std::wstring message, const int duration, const bool shownow);

			DLL_PUBLIC static void SendChatMessage(const std::string message);
			DLL_PUBLIC static void SendChatMessageToPlayer(const int entity, const std::string message);

			DLL_PUBLIC static void ShowCursor(const int entity, bool show);
		};
	}
}
#endif