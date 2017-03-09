#pragma once
#pragma once
extern "C" {
	namespace API
	{
		class Player
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC struct PlayerComponent
			{
				int drawableid = -1;
				int textureid = -1;
				int paletteid = -1;
			};

			DLL_PUBLIC struct PlayerHeadBlend
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

			DLL_PUBLIC struct PlayerHeadOverlay
			{
				int index = 0;
				float opacity = 0.0f;
				int colorType = 0;
				int colorID = 0;
				int secondColorID = 0;
			};

			DLL_PUBLIC struct PlayerProp
			{
				int drawableid = 0;
				int textureid = 0;
			};

			DLL_PUBLIC struct PlayerFeature
			{
				float scale = 0.0f;
			};


			DLL_PUBLIC static const std::string GetModel(const int entity);
			DLL_PUBLIC static void SetModel(const int entity, const std::string model);

			DLL_PUBLIC static const PlayerComponent GetPlayerComponent(const int entity, const int componentid);
			DLL_PUBLIC static void SetPlayerComponent(const int entity, const int componentid, PlayerComponent component);
			DLL_PUBLIC static const PlayerHeadBlend GetPlayerHeadBlend(const int entity);
			DLL_PUBLIC static void SetPlayerHeadBlend(const int entity, PlayerHeadBlend headblend);
			DLL_PUBLIC static const PlayerHeadOverlay GetPlayerHeadOverlay(const int entity, const int index);
			DLL_PUBLIC static void SetPlayerHeadOverlay(const int entity, const int index, PlayerHeadOverlay overlay);
			DLL_PUBLIC static const PlayerProp GetPlayerProp(const int entity, const int index);
			DLL_PUBLIC static void SetPlayerProp(const int entity, const int index, PlayerProp prop);
			DLL_PUBLIC static const float GetPlayerFaceFeature(const int entity, const int index);
			DLL_PUBLIC static void SetPlayerFaceFeature(const int entity, const int index, float scale);
		};
	}
}