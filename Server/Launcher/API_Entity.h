#pragma once
extern "C" {
	namespace API
	{
		namespace Entity
		{
			DLL_PUBLIC void Destroy(int entity);
			DLL_PUBLIC CVector3 GetPosition(int entity);
			DLL_PUBLIC void SetPosition(int entity, CVector3 position);
			DLL_PUBLIC CVector4 GetQuaternion(int entity);
			DLL_PUBLIC void SetQuaternion(int entity, CVector4 quaternion);
			DLL_PUBLIC CVector3 GetRotation(int entity);
			DLL_PUBLIC void SetRotation(int entity, CVector3 rotation);
		}
	}
}