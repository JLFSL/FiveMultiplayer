#pragma once
extern "C" {
	namespace API
	{
		class Player
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static const std::wstring GetModel(const int entity);
			DLL_PUBLIC static void SetModel(const int entity, const std::wstring model);
		};
	}
}