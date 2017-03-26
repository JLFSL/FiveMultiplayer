#include "stdafx.h"

namespace API
{
	const char *Entity::ThisNamespace = "API::Entity";

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

	const CVector3 Entity::GetRotation(int entity)
	{
		if (!g_Entities.empty())
		{
			for (int i = 0; i < g_Entities.size(); i++)
			{
				if (i == entity)
				{
					return g_Entities[i].GetRotation();
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
					return g_Entities[i].SetRotation(rotation);
				}
			}
		}

		std::cout << "[" << ThisNamespace << "] Entity " << entity << " invalid." << std::endl;
	}

	// NPC & Player
	const Entity::PedComponent Entity::GetPedComponent(const int entity, const int componentid)
	{
		for (int i = 1; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				switch (g_Entities[i].GetType())
				{
				case CServerEntity::Player:
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (g_Players[i].GetId() == entity)
						{
							PedComponent comp;
							comp.drawableid = g_Players[i].GetModelComponent(componentid).drawableid;
							comp.paletteid = g_Players[i].GetModelComponent(componentid).paletteid;
							comp.textureid = g_Players[i].GetModelComponent(componentid).textureid;
							return comp;
						}
					}
					break;
				case CServerEntity::NPC:
					for (int i = 0; i < g_Npcs.size(); i++)
					{
						if (g_Npcs[i].GetId() == entity)
						{
							PedComponent comp;
							comp.drawableid = g_Npcs[i].GetModelComponent(componentid).drawableid;
							comp.paletteid = g_Npcs[i].GetModelComponent(componentid).paletteid;
							comp.textureid = g_Npcs[i].GetModelComponent(componentid).textureid;
							return comp;
						}
					}
					break;
				default:
					std::cout << "[" << ThisNamespace << "::GetPedComponent] Entity " << entity << " is not a player or NPC." << std::endl;
					break;
				}
			}
		}
		std::cout << "[" << ThisNamespace << "::GetPedComponent] Player Entity " << entity << " invalid." << std::endl;
	}

	void Entity::SetPedComponent(const int entity, const int componentid, PedComponent component)
	{
		for (int i = 1; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				switch (g_Entities[i].GetType())
				{
				case CServerEntity::Player:
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (g_Players[i].GetId() == entity)
						{
							RakNet::BitStream sData;
							sData.Write(g_Players[i].GetId());
							sData.Write(componentid);
							sData.Write(component.drawableid);
							sData.Write(component.paletteid);
							sData.Write(component.textureid);
							g_Server->GetNetworkManager()->GetRPC().Signal("PedComponent", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

							return g_Players[i].SetModelComponent(componentid, component.drawableid, component.textureid, component.paletteid);
						}
					}
					break;
				case CServerEntity::NPC:
					for (int i = 0; i < g_Npcs.size(); i++)
					{
						if (g_Npcs[i].GetId() == entity)
						{
							RakNet::BitStream sData;
							sData.Write(g_Npcs[i].GetId());
							sData.Write(componentid);
							sData.Write(component.drawableid);
							sData.Write(component.paletteid);
							sData.Write(component.textureid);
							g_Server->GetNetworkManager()->GetRPC().Signal("PedComponent", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

							return g_Npcs[i].SetModelComponent(componentid, component.drawableid, component.textureid, component.paletteid);
						}
					}
					break;
				default:
					std::cout << "[" << ThisNamespace << "::SetPedComponent] Entity " << entity << " is not a player or NPC." << std::endl;
					break;
				}
			}
		}
		std::cout << "[" << ThisNamespace << "::SetPedComponent] Player Entity " << entity << " invalid." << std::endl;
	}

	const Entity::PedHeadBlend Entity::GetPedHeadBlend(const int entity)
	{
		for (int i = 1; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				switch (g_Entities[i].GetType())
				{
				case CServerEntity::Player:
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (g_Players[i].GetId() == entity)
						{
							PedHeadBlend blend;
							blend.shapeFirst = g_Players[i].GetModelHeadBlend().shapeFirst;
							blend.shapeMix = g_Players[i].GetModelHeadBlend().shapeMix;
							blend.shapeSecond = g_Players[i].GetModelHeadBlend().shapeSecond;
							blend.shapeThird = g_Players[i].GetModelHeadBlend().shapeThird;
							blend.skinFirst = g_Players[i].GetModelHeadBlend().skinFirst;
							blend.skinMix = g_Players[i].GetModelHeadBlend().skinMix;
							blend.skinSecond = g_Players[i].GetModelHeadBlend().skinSecond;
							blend.skinThird = g_Players[i].GetModelHeadBlend().skinThird;
							blend.thirdMix = g_Players[i].GetModelHeadBlend().thirdMix;
							return blend;
						}
					}
					break;
				case CServerEntity::NPC:
					for (int i = 0; i < g_Npcs.size(); i++)
					{
						if (g_Npcs[i].GetId() == entity)
						{
							PedHeadBlend blend;
							blend.shapeFirst = g_Npcs[i].GetModelHeadBlend().shapeFirst;
							blend.shapeMix = g_Npcs[i].GetModelHeadBlend().shapeMix;
							blend.shapeSecond = g_Npcs[i].GetModelHeadBlend().shapeSecond;
							blend.shapeThird = g_Npcs[i].GetModelHeadBlend().shapeThird;
							blend.skinFirst = g_Npcs[i].GetModelHeadBlend().skinFirst;
							blend.skinMix = g_Npcs[i].GetModelHeadBlend().skinMix;
							blend.skinSecond = g_Npcs[i].GetModelHeadBlend().skinSecond;
							blend.skinThird = g_Npcs[i].GetModelHeadBlend().skinThird;
							blend.thirdMix = g_Npcs[i].GetModelHeadBlend().thirdMix;
							return blend;
						}
					}
					break;
				default:
					std::cout << "[" << ThisNamespace << "::GetPedHeadBlend] Entity " << entity << " is not a player or NPC." << std::endl;
					break;
				}
			}
		}
		std::cout << "[" << ThisNamespace << "::GetPedHeadBlend] Player Entity " << entity << " invalid." << std::endl;
	}

	void Entity::SetPedHeadBlend(const int entity, PedHeadBlend headblend)
	{
		for (int i = 1; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				switch (g_Entities[i].GetType())
				{
				case CServerEntity::Player:
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (g_Players[i].GetId() == entity)
						{
							RakNet::BitStream sData;
							sData.Write(g_Players[i].GetId());
							sData.Write(headblend.shapeFirst);
							sData.Write(headblend.shapeMix);
							sData.Write(headblend.shapeSecond);
							sData.Write(headblend.shapeThird);
							sData.Write(headblend.skinFirst);
							sData.Write(headblend.skinMix);
							sData.Write(headblend.skinSecond);
							sData.Write(headblend.skinThird);
							sData.Write(headblend.thirdMix);
							g_Server->GetNetworkManager()->GetRPC().Signal("PedHeadBlend", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

							return g_Players[i].SetModelHeadBlend(headblend.shapeFirst, headblend.shapeMix, headblend.shapeSecond, headblend.shapeThird, headblend.skinFirst, headblend.skinMix, headblend.skinSecond, headblend.skinThird, headblend.thirdMix);
						}
					}
					break;
				case CServerEntity::NPC:
					for (int i = 0; i < g_Npcs.size(); i++)
					{
						if (g_Npcs[i].GetId() == entity)
						{
							RakNet::BitStream sData;
							sData.Write(g_Npcs[i].GetId());
							sData.Write(headblend.shapeFirst);
							sData.Write(headblend.shapeMix);
							sData.Write(headblend.shapeSecond);
							sData.Write(headblend.shapeThird);
							sData.Write(headblend.skinFirst);
							sData.Write(headblend.skinMix);
							sData.Write(headblend.skinSecond);
							sData.Write(headblend.skinThird);
							sData.Write(headblend.thirdMix);
							g_Server->GetNetworkManager()->GetRPC().Signal("PedHeadBlend", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

							return g_Npcs[i].SetModelHeadBlend(headblend.shapeFirst, headblend.shapeMix, headblend.shapeSecond, headblend.shapeThird, headblend.skinFirst, headblend.skinMix, headblend.skinSecond, headblend.skinThird, headblend.thirdMix);
						}
					}
					break;
				default:
					std::cout << "[" << ThisNamespace << "::SetPedHeadBlend] Entity " << entity << " is not a player or NPC." << std::endl;
					break;
				}
			}
		}
		std::cout << "[" << ThisNamespace << "::SetPedHeadBlend] Player Entity " << entity << " invalid." << std::endl;
	}

	const Entity::PedHeadOverlay Entity::GetPedHeadOverlay(const int entity, const int index)
	{
		for (int i = 1; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				switch (g_Entities[i].GetType())
				{
				case CServerEntity::Player:
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (g_Players[i].GetId() == entity)
						{
							PedHeadOverlay overlay;
							overlay.index = g_Players[i].GetModelHeadOverlay(index).index;
							overlay.colorType = g_Players[i].GetModelHeadOverlay(index).colorType;
							overlay.colorID = g_Players[i].GetModelHeadOverlay(index).colorID;
							overlay.secondColorID = g_Players[i].GetModelHeadOverlay(index).secondColorID;
							overlay.opacity = g_Players[i].GetModelHeadOverlay(index).opacity;
							return overlay;
						}
					}
					break;
				case CServerEntity::NPC:
					for (int i = 0; i < g_Npcs.size(); i++)
					{
						if (g_Npcs[i].GetId() == entity)
						{
							PedHeadOverlay overlay;
							overlay.index = g_Npcs[i].GetModelHeadOverlay(index).index;
							overlay.colorType = g_Npcs[i].GetModelHeadOverlay(index).colorType;
							overlay.colorID = g_Npcs[i].GetModelHeadOverlay(index).colorID;
							overlay.secondColorID = g_Npcs[i].GetModelHeadOverlay(index).secondColorID;
							overlay.opacity = g_Npcs[i].GetModelHeadOverlay(index).opacity;
							return overlay;
						}
					}
					break;
				default:
					std::cout << "[" << ThisNamespace << "::GetPedHeadOverlay] Entity " << entity << " is not a player or NPC." << std::endl;
					break;
				}
			}
		}
		std::cout << "[" << ThisNamespace << "::GetPedHeadOverlay] Player Entity " << entity << " invalid." << std::endl;
	}

	void Entity::SetPedHeadOverlay(const int entity, const int index, PedHeadOverlay overlay)
	{
		for (int i = 1; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				switch (g_Entities[i].GetType())
				{
				case CServerEntity::Player:
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (g_Players[i].GetId() == entity)
						{
							RakNet::BitStream sData;
							sData.Write(g_Players[i].GetId());
							sData.Write(index);
							sData.Write(overlay.index);
							sData.Write(overlay.colorType);
							sData.Write(overlay.colorID);
							sData.Write(overlay.secondColorID);
							sData.Write(overlay.opacity);
							g_Server->GetNetworkManager()->GetRPC().Signal("PedHeadOverlay", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

							return g_Players[i].SetModelHeadOverlay(index, overlay.index, overlay.colorType, overlay.colorID, overlay.secondColorID, overlay.opacity);
						}
					}
					break;
				case CServerEntity::NPC:
					for (int i = 0; i < g_Npcs.size(); i++)
					{
						if (g_Npcs[i].GetId() == entity)
						{
							RakNet::BitStream sData;
							sData.Write(g_Npcs[i].GetId());
							sData.Write(index);
							sData.Write(overlay.index);
							sData.Write(overlay.colorType);
							sData.Write(overlay.colorID);
							sData.Write(overlay.secondColorID);
							sData.Write(overlay.opacity);
							g_Server->GetNetworkManager()->GetRPC().Signal("PedHeadOverlay", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

							return g_Npcs[i].SetModelHeadOverlay(index, overlay.index, overlay.colorType, overlay.colorID, overlay.secondColorID, overlay.opacity);
						}
					}
					break;
				default:
					std::cout << "[" << ThisNamespace << "::SetPedHeadOverlay] Entity " << entity << " is not a player or NPC." << std::endl;
					break;
				}
			}
		}
		std::cout << "[" << ThisNamespace << "::SetPedHeadOverlay] Player Entity " << entity << " invalid." << std::endl;
	}

	const Entity::PedProp Entity::GetPedProp(const int entity, const int index)
	{
		for (int i = 1; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				switch (g_Entities[i].GetType())
				{
				case CServerEntity::Player:
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (g_Players[i].GetId() == entity)
						{
							PedProp prop;
							prop.drawableid = g_Players[i].GetModelProp(index).drawableid;
							prop.textureid = g_Players[i].GetModelProp(index).textureid;
							return prop;
						}
					}
					break;
				case CServerEntity::NPC:
					for (int i = 0; i < g_Npcs.size(); i++)
					{
						if (g_Npcs[i].GetId() == entity)
						{
							PedProp prop;
							prop.drawableid = g_Npcs[i].GetModelProp(index).drawableid;
							prop.textureid = g_Npcs[i].GetModelProp(index).textureid;
							return prop;
						}
					}
					break;
				default:
					std::cout << "[" << ThisNamespace << "::GetPedProp] Entity " << entity << " is not a player or NPC." << std::endl;
					break;
				}
			}
		}
		std::cout << "[" << ThisNamespace << "::GetPedProp] Player Entity " << entity << " invalid." << std::endl;
	}

	void Entity::SetPedProp(const int entity, const int index, PedProp prop)
	{
		for (int i = 1; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				switch (g_Entities[i].GetType())
				{
				case CServerEntity::Player:
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (g_Players[i].GetId() == entity)
						{
							RakNet::BitStream sData;
							sData.Write(g_Players[i].GetId());
							sData.Write(index);
							sData.Write(prop.drawableid);
							sData.Write(prop.textureid);
							g_Server->GetNetworkManager()->GetRPC().Signal("PedProp", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

							return g_Players[i].SetModelProp(index, prop.drawableid, prop.textureid);
						}
					}
					break;
				case CServerEntity::NPC:
					for (int i = 0; i < g_Npcs.size(); i++)
					{
						if (g_Npcs[i].GetId() == entity)
						{
							RakNet::BitStream sData;
							sData.Write(g_Npcs[i].GetId());
							sData.Write(index);
							sData.Write(prop.drawableid);
							sData.Write(prop.textureid);
							g_Server->GetNetworkManager()->GetRPC().Signal("PedProp", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

							return g_Npcs[i].SetModelProp(index, prop.drawableid, prop.textureid);
						}
					}
					break;
				default:
					std::cout << "[" << ThisNamespace << "::SetPedProp] Entity " << entity << " is not a player or NPC." << std::endl;
					break;
				}
			}
		}
		std::cout << "[" << ThisNamespace << "::SetPedProp] Player Entity " << entity << " invalid." << std::endl;
	}

	const float Entity::GetPedFaceFeature(const int entity, const int index)
	{
		for (int i = 1; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				switch (g_Entities[i].GetType())
				{
				case CServerEntity::Player:
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (g_Players[i].GetId() == entity)
						{
							return g_Players[i].GetModelFaceFeature(index);
						}
					}
					break;
				case CServerEntity::NPC:
					for (int i = 0; i < g_Npcs.size(); i++)
					{
						if (g_Npcs[i].GetId() == entity)
						{
							return g_Npcs[i].GetModelFaceFeature(index);
						}
					}
					break;
				default:
					std::cout << "[" << ThisNamespace << "::GetPedFaceFeature] Entity " << entity << " is not a player or NPC." << std::endl;
					break;
				}
			}
		}
		std::cout << "[" << ThisNamespace << "::GetPedFaceFeature] Player Entity " << entity << " invalid." << std::endl;
	}

	void Entity::SetPedFaceFeature(const int entity, const int index, const float scale)
	{
		for (int i = 1; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				switch (g_Entities[i].GetType())
				{
				case CServerEntity::Player:
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (g_Players[i].GetId() == entity)
						{
							RakNet::BitStream sData;
							sData.Write(g_Players[i].GetId());
							sData.Write(index);
							sData.Write(scale);
							g_Server->GetNetworkManager()->GetRPC().Signal("PedFaceFeature", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

							return g_Players[i].SetModelFaceFeature(index, scale);
						}
					}
					break;
				case CServerEntity::NPC:
					for (int i = 0; i < g_Npcs.size(); i++)
					{
						if (g_Npcs[i].GetId() == entity)
						{
							RakNet::BitStream sData;
							sData.Write(g_Npcs[i].GetId());
							sData.Write(index);
							sData.Write(scale);
							g_Server->GetNetworkManager()->GetRPC().Signal("PedFaceFeature", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

							return g_Npcs[i].SetModelFaceFeature(index, scale);
						}
					}
					break;
				default:
					std::cout << "[" << ThisNamespace << "::SetPedFaceFeature] Entity " << entity << " is not a player or NPC." << std::endl;
					break;
				}
			}
		}
		std::cout << "[" << ThisNamespace << "::SetPedFaceFeature] Player Entity " << entity << " invalid." << std::endl;
	}
}
