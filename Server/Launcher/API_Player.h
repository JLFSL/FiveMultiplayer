#pragma once
#pragma once
extern "C" {
	namespace API
	{
		namespace Player
		{
			DLL_PUBLIC struct PlayerComponents
			{
				int drawableid = -1;
				int textureid = -1;
				int paletteid = -1;
			};

			DLL_PUBLIC struct PlayerHeadBlends
			{
				int shapeFirst = 0;
				int shapeSecond = 0;
				int shapeThird = 0;
				int skinFirst = 0;
				int skinSecond = 0;
				int skinThird = 0;
				float shapeMix = 0;
				float skinMix = 0;
				float thirdMix = 0;
			};

			DLL_PUBLIC struct PlayerHeadOverlays
			{
				int index = 0;
				float opacity = 0.0f;
				int colorType = 0;
				int colorID = 0;
				int secondColorID = 0;
			};

			DLL_PUBLIC struct PlayerProps
			{
				int drawableid = 0;
				int textureid = 0;
			};

			DLL_PUBLIC struct PlayerFeatures
			{
				float scale = 0.0f;
			};


			DLL_PUBLIC const std::string GetModel(const int entity);
			DLL_PUBLIC void SetModel(const int entity, const std::string model);

			DLL_PUBLIC PlayerComponents GetModelComponent(const int entity, const int index);
			DLL_PUBLIC void SetModelComponent(const int entity, const int index, PlayerComponents component);
			DLL_PUBLIC PlayerHeadBlends GetModelHeadBlend(const int entity);
			DLL_PUBLIC void SetModelHeadBlend(const int entity, PlayerHeadBlends headblend);
			DLL_PUBLIC PlayerHeadOverlays GetModelHeadOverlay(const int entity, const int index);
			DLL_PUBLIC void SetModelHeadOverlay(const int entity, const int index, PlayerHeadOverlays overlay);
			DLL_PUBLIC PlayerProps	GetModelProp(const int entity, const int index);
			DLL_PUBLIC void SetModelProp(const int entity, const int index, PlayerProps prop);
			DLL_PUBLIC float GetModelFeature(const int entity, const int index);
			DLL_PUBLIC void SetModelFeature(const int entity, const int index, float scale);
		}
	}
}