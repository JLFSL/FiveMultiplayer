#include "stdafx.h"

namespace API
{
	const char *ThisNamespace = "API::Entity";

	void Entity::Destroy(int entity)
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

	const CVector3 Entity::GetPosition(int entity)
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

	void Entity::SetPosition(int entity, CVector3 position)
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

	const CVector4 Entity::GetQuaternion(int entity)
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

	void Entity::SetQuaternion(int entity, CVector4 quaternion)
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

	const CVector3 Entity::GetRotation(int entity)
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

	void Entity::SetRotation(int entity, CVector3 rotation)
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
