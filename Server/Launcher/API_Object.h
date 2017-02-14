#pragma once
extern "C" {
	namespace API
	{
		namespace Object
		{
			DLL_PUBLIC int CreateObject(std::string model, CVector3 position, CVector4 Quaternion, bool dynamic);
			DLL_PUBLIC int CreateObjectWithHash(int hash, CVector3 position, CVector4 Quaternion, bool dynamic);
			DLL_PUBLIC int CreateObjectWithRotation(std::string model, CVector3 position, CVector3 Rotation, bool dynamic);
			DLL_PUBLIC int CreateObjectWithHRotation(int hash, CVector3 position, CVector3 Rotation, bool dynamic);
		}
	}
}