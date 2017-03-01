#include "stdafx.h"

namespace API
{
	namespace Player
	{
		const char *ThisNamespace = "API::Player";

		const std::string GetModel(const int entity)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					return g_Players[i].GetModel();
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		void SetModel(const int entity, const std::string model)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					RakNet::BitStream sData;
					sData.Write(RakString(model.c_str()));
					g_Server->GetNetworkManager()->GetRPC().Signal("PlayerModel", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);

					return g_Players[i].SetModel(model);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		PlayerComponent GetPlayerComponent(const int entity, const int componentid)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					PlayerComponent comp;
					comp.drawableid = g_Players[i].GetModelComponent(componentid).drawableid;
					comp.paletteid = g_Players[i].GetModelComponent(componentid).paletteid;
					comp.textureid = g_Players[i].GetModelComponent(componentid).textureid;
					return comp;
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		void SetPlayerComponent(const int entity, const int componentid, PlayerComponent component)
		{
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
					g_Server->GetNetworkManager()->GetRPC().Signal("PlayerComponent", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

					return g_Players[i].SetModelComponent(componentid, component.drawableid, component.textureid, component.paletteid);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		PlayerHeadBlend GetPlayerHeadBlend(const int entity)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					PlayerHeadBlend blend;
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

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		void SetPlayerHeadBlend(const int entity, PlayerHeadBlend headblend)
		{
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
					g_Server->GetNetworkManager()->GetRPC().Signal("PlayerHeadBlend", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

					return g_Players[i].SetModelHeadBlend(headblend.shapeFirst, headblend.shapeMix, headblend.shapeSecond, headblend.shapeThird, headblend.skinFirst, headblend.skinMix, headblend.skinSecond, headblend.skinThird, headblend.thirdMix);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		PlayerHeadOverlay GetPlayerHeadOverlay(const int entity, const int index)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					PlayerHeadOverlay overlay;
					overlay.index = g_Players[i].GetModelHeadOverlay(index).index;
					overlay.colorType = g_Players[i].GetModelHeadOverlay(index).colorType;
					overlay.colorID = g_Players[i].GetModelHeadOverlay(index).colorID;
					overlay.secondColorID = g_Players[i].GetModelHeadOverlay(index).secondColorID;
					overlay.opacity = g_Players[i].GetModelHeadOverlay(index).opacity;
					return overlay;
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		void SetPlayerHeadOverlay(const int entity, const int index, PlayerHeadOverlay overlay)
		{
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
					g_Server->GetNetworkManager()->GetRPC().Signal("PlayerHeadOverlay", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

					return g_Players[i].SetModelHeadOverlay(index, overlay.index, overlay.colorType, overlay.colorID, overlay.secondColorID, overlay.opacity);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		PlayerProp GetPlayerProp(const int entity, const int index)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					PlayerProp prop;
					prop.drawableid = g_Players[i].GetModelProp(index).drawableid;
					prop.textureid = g_Players[i].GetModelProp(index).textureid;
					return prop;
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		void SetPlayerProp(const int entity, const int index, PlayerProp prop)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					RakNet::BitStream sData;
					sData.Write(g_Players[i].GetId());
					sData.Write(index);
					sData.Write(prop.drawableid);
					sData.Write(prop.textureid);
					g_Server->GetNetworkManager()->GetRPC().Signal("PlayerProp", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

					return g_Players[i].SetModelProp(index, prop.drawableid, prop.textureid);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		float GetPlayerFaceFeature(const int entity, const int index)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					return g_Players[i].GetModelFaceFeature(index);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		void SetPlayerFaceFeature(const int entity, const int index, const float scale)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					RakNet::BitStream sData;
					sData.Write(g_Players[i].GetId());
					sData.Write(index);
					sData.Write(scale);
					g_Server->GetNetworkManager()->GetRPC().Signal("PlayerFaceFeature", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

					return g_Players[i].SetModelFaceFeature(index, scale);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}
	}
}