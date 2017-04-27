#ifndef __APIOBJECT_H__
#define __APIOBJECT_H__
extern "C" {
	namespace API
	{
		class Object
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static const int Create(const std::wstring model, const CVector3 position, const CVector3 Rotation, const bool dynamic);
			DLL_PUBLIC static const int Create(const int hash, const CVector3 position, const CVector3 Rotation, const bool dynamic);
			DLL_PUBLIC static const int GetTextureVariation(const int entity);
			DLL_PUBLIC static void SetTextureVariation(const int entity, const int textureindex);
		};
	}
}
#endif