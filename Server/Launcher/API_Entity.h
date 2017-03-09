#pragma once
extern "C" {
	namespace API
	{
		class Entity
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static void Destroy(int entity);
			DLL_PUBLIC static const CVector3 GetPosition(int entity);
			DLL_PUBLIC static void SetPosition(int entity, CVector3 position);
			DLL_PUBLIC static const CVector4 GetQuaternion(int entity);
			DLL_PUBLIC static void SetQuaternion(int entity, CVector4 quaternion);
			DLL_PUBLIC static const CVector3 GetRotation(int entity);
			DLL_PUBLIC static void SetRotation(int entity, CVector3 rotation);
		};
	}
}