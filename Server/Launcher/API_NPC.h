#ifndef __APINPC_H__
#define __APINPC_H__
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
#endif