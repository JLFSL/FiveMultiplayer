#pragma once
extern "C" {
	namespace API
	{
		namespace Entity
		{
			DLL_PUBLIC CVector3 GetPosition(int entity);
			DLL_PUBLIC void SetPosition(int entity, CVector3 position);
		}
	}
}