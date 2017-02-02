#include "stdafx.h"

namespace API
{
	namespace Entity
	{
		const char *ThisNamespace = "API::Entity";

		void Destroy(int entity)
		{
			if (!g_Entities.empty())
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (i == entity)
					{
						return g_Entities[i].Destroy();
					}
				}
			}

			std::cout << "[" << ThisNamespace << "] Entity " << entity << " invalid." << std::endl;
		}

		CVector3 GetPosition(int entity)
		{
			if (!g_Entities.empty())
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (i == entity)
					{
						return g_Entities[i].GetPosition();
					}
				}
			}

			std::cout << "[" << ThisNamespace << "] Entity " << entity << " invalid." << std::endl;
		}

		void SetPosition(int entity, CVector3 position)
		{
			if (!g_Entities.empty())
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (i == entity)
					{
						return g_Entities[i].SetPosition(position);
					}
				}
			}

			std::cout << "[" << ThisNamespace << "] Entity " << entity << " invalid." << std::endl;
		}
	}
}
