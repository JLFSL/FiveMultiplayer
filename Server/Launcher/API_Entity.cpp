#include "stdafx.h"

namespace API
{
	namespace Entity
	{
		char *ThisNamespace = "API::Entity";

		CVector3 GetPosition(int entity)
		{
			cout << g_Entities[entity].GetPosition().fX << endl;
			return g_Entities[entity].GetPosition();
		}

		void SetPosition(int entity, CVector3 position)
		{
			g_Entities[entity].SetPosition(position);
		}
	}
}
