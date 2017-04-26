#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Player
		{
		public:
			/// <summary>
			/// Gets the model of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to get the model of.</param>
			/// <returns name="model">The player model the player currently has.</returns>
			DLL_PUBLIC_I static const std::wstring GetModel(const int entity);

			/// <summary>
			/// Sets the model of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player you wish to set the model of.</param>
			/// <param name="model">The model you wish to set on the player.</param>
			DLL_PUBLIC_I static void SetModel(const int entity, const std::wstring model);

			/// <summary>
			/// Gets the username of the player entity.
			/// </summary>
			/// <param name="entity">The entity of the player to get the username of.</param>
			DLL_PUBLIC_I static const std::string GetUsername(const int entity);

			/// <summary>
			/// Gets the players controls state.
			/// </summary>
			/// <param name="entity">The entity of the player.</param>
			/// <returns name="disabled">The disabled controls state.</returns>
			DLL_PUBLIC_I static const bool IsControlsDisabled(const int entity);

			/// <summary>
			/// Gets the players controls state.
			/// </summary>
			/// <param name="entity">The entity of the player.</param>
			/// <param name="disable">The state to set the controls disabled state in.</param>
			DLL_PUBLIC_I static void DisableControls(const int entity, bool disable);

		};
	}
#ifdef __cplusplus
}
#endif