#ifndef __APIPLAYER_H__
#define __APIPLAYER_H__

extern "C" {
	namespace API
	{
		class Player
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static const std::wstring GetModel(const int entity);
			DLL_PUBLIC static void SetModel(const int entity, const std::wstring model);

			DLL_PUBLIC static const std::string GetUsername(const int entity);

			DLL_PUBLIC static const bool IsControlable(const int entity);
			DLL_PUBLIC static void SetControlable(const int entity, bool disablecontrols, bool frozen = true);
		};
	}
}

#endif