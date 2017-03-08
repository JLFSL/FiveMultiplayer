#pragma once
extern "C" {
	namespace API
	{
		namespace Object
		{
			DLL_PUBLIC int Create(std::string model, CVector3 position, CVector4 Quaternion, bool dynamic);
			DLL_PUBLIC int CreateWithHash(int hash, CVector3 position, CVector4 Quaternion, bool dynamic);
			DLL_PUBLIC int CreateWithRotation(std::string model, CVector3 position, CVector3 Rotation, bool dynamic);
			DLL_PUBLIC int CreateWithHRotation(int hash, CVector3 position, CVector3 Rotation, bool dynamic);
		}
	}
}