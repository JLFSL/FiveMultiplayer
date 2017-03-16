#pragma once
extern "C" {
	namespace API
	{
		class Object
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static const int Create(std::string model, CVector3 position, CVector4 Quaternion, bool dynamic);
			DLL_PUBLIC static const int CreateWithHash(int hash, CVector3 position, CVector4 Quaternion, bool dynamic);
			DLL_PUBLIC static const int CreateWithRotation(std::string model, CVector3 position, CVector3 Rotation, bool dynamic);
			DLL_PUBLIC static const int CreateWithHRotation(int hash, CVector3 position, CVector3 Rotation, bool dynamic);
		};
	}
}