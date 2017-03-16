#pragma once

extern "C" {
	namespace API
	{
		class Visual
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static void ShowMessageAboveMap(const std::string message, const std::string pic, const int icontype, const std::string sender, const std::string subject);
			DLL_PUBLIC static void ShowMessageAboveMapToPlayer(const int entity, const std::string message, const std::string pic, const int icontype, const std::string sender, const std::string subject);
		};
	}
}
