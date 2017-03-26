#pragma once
extern "C" {
	namespace API
	{
		class NPC
		{
			static const char *ThisNamespace;
		public:
			DLL_PUBLIC static const int Create(const std::wstring model, const CVector3 position, const CVector3 rotation);
		};
	}
}