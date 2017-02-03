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
				if (g_Players[i].GetEntity() == entity)
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
				if (g_Players[i].GetEntity() == entity)
				{
					return g_Players[i].SetModel(model);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		PlayerComponents GetPlayerComponent(const int entity, const int index)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetEntity() == entity)
				{
					PlayerComponents comp;
					comp.drawableid = g_Players[i].GetModelComponent(index).drawableid;
					comp.paletteid = g_Players[i].GetModelComponent(index).paletteid;
					comp.textureid = g_Players[i].GetModelComponent(index).textureid;
					return comp;
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		void SetPlayerComponent(const int entity, const int index, PlayerComponents component)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetEntity() == entity)
				{
					return g_Players[i].SetModelComponent(index, component.drawableid, component.textureid, component.paletteid);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		PlayerHeadBlends GetPlayerHeadBlend(const int entity)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetEntity() == entity)
				{
					PlayerHeadBlends blend;
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

		void SetPlayerHeadBlend(const int entity, PlayerHeadBlends headblend)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetEntity() == entity)
				{
					return g_Players[i].SetModelHeadBlend(headblend.shapeFirst, headblend.shapeMix, headblend.shapeSecond, headblend.shapeThird, headblend.skinFirst, headblend.skinMix, headblend.skinSecond, headblend.skinThird, headblend.thirdMix);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		PlayerHeadOverlays GetPlayerHeadOverlay(const int entity, const int index)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetEntity() == entity)
				{
					PlayerHeadOverlays overlay;
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

		void SetPlayerHeadOverlay(const int entity, const int index, PlayerHeadOverlays overlay)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetEntity() == entity)
				{
					return g_Players[i].SetModelHeadOverlay(index, overlay.index, overlay.colorType, overlay.colorID, overlay.secondColorID, overlay.opacity);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		PlayerProps	GetPlayerProp(const int entity, const int index)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetEntity() == entity)
				{
					PlayerProps prop;
					prop.drawableid = g_Players[i].GetModelProp(index).drawableid;
					prop.textureid = g_Players[i].GetModelProp(index).textureid;
					return prop;
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		void SetPlayerProp(const int entity, const int index, PlayerProps prop)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetEntity() == entity)
				{
					return g_Players[i].SetModelProp(index, prop.drawableid, prop.textureid);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		float GetPlayerFeature(const int entity, const int index)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetEntity() == entity)
				{
					return g_Players[i].GetModelFeature(index);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}

		void SetPlayerFeature(const int entity, const int index, const float scale)
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetEntity() == entity)
				{
					return g_Players[i].SetModelFeature(index, scale);
				}
			}

			std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
		}
	}
}