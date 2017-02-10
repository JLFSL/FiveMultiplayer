#pragma once
extern "C" {
	namespace API
	{
		namespace Object
		{
			DLL_PUBLIC int CreateObject(std::string model, CVector3 position, CVector4 Quaternion, bool dynamic);
			DLL_PUBLIC int CreateObjectWithHash(int hash, CVector3 position, CVector4 Quaternion, bool dynamic);
		}
	}
}