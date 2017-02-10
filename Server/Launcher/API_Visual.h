#pragma once

namespace API
{
	namespace Visual
	{
		extern "C" DLL_PUBLIC void ShowMessageAboveMap(const std::string message, const std::string pic, int icontype, const std::string sender, const std::string subject);
		//extern "C" DLL_PUBLIC void ShowMessageAboveMap(const int entity, const std::string message, const std::string pic, int icontype, const std::string sender, const std::string subject);
	}
}
