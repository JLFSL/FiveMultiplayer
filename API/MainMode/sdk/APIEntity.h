#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Entity
		{
		public:
			DLL_PUBLIC_I struct PedComponent
			{
				int drawableid = -1;
				int textureid = -1;
				int paletteid = -1;
			};

			DLL_PUBLIC_I struct PedHeadBlend
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

			DLL_PUBLIC_I struct PedHeadOverlay
			{
				int index = 0;
				float opacity = 0.0f;
				int colorType = 0;
				int colorID = 0;
				int secondColorID = 0;
			};

			DLL_PUBLIC_I struct PedProp
			{
				int drawableid = 0;
				int textureid = 0;
			};

			DLL_PUBLIC_I struct PedFeature
			{
				float scale = 0.0f;
			};

			/// <summary>
			/// Destroys/Removes a entity from the server
			/// </summary>
			/// <param name="entity">The entity you wish to destroy.</param>
			DLL_PUBLIC_I static void Destroy(int entity);

			/// <summary>
			/// Gets the position of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to get the position off.</param>
			/// <returns name="position">The CVector3 position of the entity</returns>
			DLL_PUBLIC_I static const CVector3 GetPosition(int entity);

			/// <summary>
			/// Sets the position of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to set the position off.</param>
			/// <param name="position">The position you wish to set the entity at.</param>
			/// <returns></returns>
			DLL_PUBLIC_I static void SetPosition(int entity, CVector3 position);

			/// <summary>
			/// Gets the rotation of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to get the rotation off.</param>
			/// <returns name="rotation">The CVector3 rotation of the entity</returns>
			DLL_PUBLIC_I CVector3 GetRotation(int entity);

			/// <summary>
			/// Sets the rotation of the entity.
			/// </summary>
			/// <param name="entity">The entity you wish to set the rotation off.</param>
			/// <param name="rotation">The rotation you wish to set they entity at.</param>
			/// <returns></returns>
			DLL_PUBLIC_I void SetRotation(int entity, CVector3 rotation);

			/// <summary>
			/// Gets the Ped Component data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to get their model Components.</param>
			/// <param name="componentid">The componentid of the component you wish to get.</param>
			/// <returns name="PlayerComponents">The PlayerComponents of the desired player/npc and component</returns>
			DLL_PUBLIC_I static const PedComponent GetPedComponent(const int entity, const int componentid);

			/// <summary>
			/// Sets the Ped Component data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to set their model Components.</param>
			/// <param name="componentid">The componentid of the component you wish to set.</param>
			/// <param name="component">The component structure of the component you wish to set.</param>
			DLL_PUBLIC_I static void SetPedComponent(const int entity, const int componentid, PedComponent component);

			/// <summary>
			/// Gets the head blend data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to get their model headblend data.</param>
			/// <returns name="PlayerHeadBlends">The headblend data of the players model</returns>
			DLL_PUBLIC_I static const PedHeadBlend GetPedHeadBlend(const int entity);

			/// <summary>
			/// Sets the head blend data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to set their model headblend.</param>
			/// <param name="headblend">The headblend data.</param>
			DLL_PUBLIC_I static void SetPedHeadBlend(const int entity, PedHeadBlend headblend);

			/// <summary>
			/// Gets the headoverlay data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to get their model headoverlay data.</param>
			/// <param name="overlayid">The overlay id you wish to get the data off.</param>
			/// <returns name="headoverlay">The headoverlay data of the overlay id</returns>
			DLL_PUBLIC_I static const PedHeadOverlay GetPedHeadOverlay(const int entity, const int overlayid);

			/// <summary>
			/// Sets the headoverlay data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to set their model headoverlay data.</param>
			/// <param name="overlayid">The overlay id you wish to set the data off.</param>
			/// <param name="overlay">The overlay data.</param>
			DLL_PUBLIC_I static void SetPedHeadOverlay(const int entity, const int overlayid, PedHeadOverlay overlay);

			/// <summary>
			/// Gets the prop data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to Get their model prop data.</param>
			/// <param name="compotentid">The compotent id you wish to get the data off.</param>
			/// <returns name="prop">The prop data.</returns>
			DLL_PUBLIC_I static const PedProp GetPedProp(const int entity, const int compotentid);

			/// <summary>
			/// Sets the prop data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to set their model prop data.</param>
			/// <param name="compotentid">The compotent id you wish to set the data off.</param>
			/// <param name="compotentid">The prop data.</param>
			DLL_PUBLIC_I static void SetPedProp(const int entity, const int compotentid, PedProp prop);

			/// <summary>
			/// Gets the face feature data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to get their model face feature data.</param>
			/// <param name="index">The index you wish to get the data off (Index can be 0 - 19).</param>
			/// <returns name="feature">The face feature scale. (Scale ranges from -1.0 to 1.0)</returns>
			DLL_PUBLIC_I static const float GetPedFaceFeature(const int entity, const int index);

			/// <summary>
			/// Sets the face feature data of the player or npc entity.
			/// </summary>
			/// <param name="entity">The entity of the player or npc you wish to set their model face feature data.</param>
			/// <param name="index">The index you wish to set the data off (Index can be 0 - 19).</param>
			/// <param name="scale">The face feature scale. (Scale ranges from -1.0 to 1.0)</param>
			DLL_PUBLIC_I static void SetPedFaceFeature(const int entity, const int index, float scale);
		};
	}
#ifdef __cplusplus
}
#endif