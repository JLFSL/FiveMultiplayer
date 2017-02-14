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

		CVector4 GetQuaternion(int entity)
		{
			if (!g_Entities.empty())
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (i == entity)
					{
						return g_Entities[i].GetQuaternion();
					}
				}
			}

			std::cout << "[" << ThisNamespace << "] Entity " << entity << " invalid." << std::endl;
		}

		void SetQuaternion(int entity, CVector4 quaternion)
		{
			if (!g_Entities.empty())
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (i == entity)
					{
						return g_Entities[i].SetQuaternion(quaternion);
					}
				}
			}

			std::cout << "[" << ThisNamespace << "] Entity " << entity << " invalid." << std::endl;
		}

		CVector3 GetRotation(int entity)
		{
			if (!g_Entities.empty())
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (i == entity)
					{
						CVector4 q = g_Entities[i].GetQuaternion();
						CVector3 rotation = CVector3::calculateEuler(q.fX, q.fY, q.fZ, q.fW);
						return rotation;
					}
				}
			}

			std::cout << "[" << ThisNamespace << "] Entity " << entity << " invalid." << std::endl;

		}

		void SetRotation(int entity, CVector3 rotation)
		{
			if (!g_Entities.empty())
			{
				for (int i = 0; i < g_Entities.size(); i++)
				{
					if (i == entity)
					{
						CVector4 q = CVector4::calculateQuaternion(rotation.fX, rotation.fY, rotation.fZ);
						return g_Entities[i].SetQuaternion(q);
					}
				}
			}

			std::cout << "[" << ThisNamespace << "] Entity " << entity << " invalid." << std::endl;
		}
	}
}
