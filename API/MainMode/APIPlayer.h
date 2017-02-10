#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		namespace Player
		{
			DLL_PUBLIC_I struct PlayerComponent
			{
				int drawableid = -1;
				int textureid = -1;
				int paletteid = -1;
			};
			
			DLL_PUBLIC_I struct PlayerHeadBlend
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

			DLL_PUBLIC_I struct PlayerHeadOverlay
			{
				int index = 0;
				float opacity = 0.0f;
				int colorType = 0;
				int colorID = 0;
				int secondColorID = 0;
			};

			DLL_PUBLIC_I struct PlayerProp
			{
				int drawableid = 0;
				int textureid = 0;
			};

			DLL_PUBLIC_I struct PlayerFeature
			{
				float scale = 0.0f;
			};

			/// <summary>
			/// Gets the model of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to get the model of.</param>
			/// <returns name="model">The player model the player currently has.</returns>
			DLL_PUBLIC_I const std::string GetModel(const int entity);

			/// <summary>
			/// Sets the model of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to set the model of.</param>
			/// <param name="model">The model you wish to set on the player.</param>
			DLL_PUBLIC_I void SetModel(const int entity, const std::string model);

			/// <summary>
			/// Gets the Player Component of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to get their model Components.</param>
			/// <param name="componentid">The componentid of the component you wish to get.</param>
			/// <returns name="PlayerComponents">The PlayerComponents of the desired player and component</returns>
			DLL_PUBLIC_I PlayerComponent GetPlayerComponent(const int entity, const int componentid);
			
			/// <summary>
			/// Sets the Player Component of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to set their model Components.</param>
			/// <param name="componentid">The componentid of the component you wish to set.</param>
			/// <param name="component">The component structure of the component you wish to set.</param>
			DLL_PUBLIC_I void SetPlayerComponent(const int entity, const int componentid, PlayerComponent component);

			/// <summary>
			/// Gets the head blend data of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to get their model headblend data.</param>
			/// <returns name="PlayerHeadBlends">The headblend data of the players model</returns>
			DLL_PUBLIC_I PlayerHeadBlend GetPlayerHeadBlend(const int entity);

			/// <summary>
			/// Sets the head blend data of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to set their model headblend.</param>
			/// <param name="headblend">The headblend data.</param>
			DLL_PUBLIC_I void SetPlayerHeadBlend(const int entity, PlayerHeadBlend headblend);

			/// <summary>
			/// Gets the headoverlay data of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to get their model headoverlay data.</param>
			/// <param name="overlayid">The overlay id you wish to get the data off.</param>
			/// <returns name="headoverlay">The headoverlay data of the overlay id</returns>
			DLL_PUBLIC_I PlayerHeadOverlay GetPlayerHeadOverlay(const int entity, const int overlayid);

			/// <summary>
			/// Sets the headoverlay data of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to set their model headoverlay data.</param>
			/// <param name="overlayid">The overlay id you wish to set the data off.</param>
			/// <param name="overlay">The overlay data.</param>
			DLL_PUBLIC_I void SetPlayerHeadOverlay(const int entity, const int overlayid, PlayerHeadOverlay overlay);

			/// <summary>
			/// Gets the prop data of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to Get their model prop data.</param>
			/// <param name="compotentid">The compotent id you wish to get the data off.</param>
			/// <returns name="prop">The prop data.</returns>
			DLL_PUBLIC_I PlayerProp GetPlayerProp(const int entity, const int compotentid);

			/// <summary>
			/// Sets the prop data of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to set their model prop data.</param>
			/// <param name="compotentid">The compotent id you wish to set the data off.</param>
			/// <param name="compotentid">The prop data.</param>
			DLL_PUBLIC_I void SetPlayerProp(const int entity, const int compotentid, PlayerProp prop);

			/// <summary>
			/// Gets the face feature data of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to get their model face feature data.</param>
			/// <param name="index">The index you wish to get the data off (Index can be 0 - 19).</param>
			/// <returns name="feature">The face feature scale. (Scale ranges from -1.0 to 1.0)</returns>
			DLL_PUBLIC_I float GetPlayerFaceFeature(const int entity, const int index);

			/// <summary>
			/// Sets the face feature data of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to set their model face feature data.</param>
			/// <param name="index">The index you wish to set the data off (Index can be 0 - 19).</param>
			/// <param name="scale">The face feature scale. (Scale ranges from -1.0 to 1.0)</param>
			DLL_PUBLIC_I void SetPlayerFaceFeature(const int entity, const int index, float scale);

		}
	}
#ifdef __cplusplus
}
#endif