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
			DLL_PUBLIC_I static const bool IsControllable(const int entity);

			/// <summary>
			/// Sets the players controls state.
			/// </summary>
			/// <param name="entity">The entity of the player.</param>
			/// <param name="disablecontrols">The state to set the controls disabled state in.</param>
			/// <param name="frozen">Wether the player should be frozen in place.</param>
			DLL_PUBLIC_I static void SetControllable(const int entity, bool disablecontrols, bool frozen = true);

			/// <summary>
			/// Gets the players ip
			/// </summary>
			/// <param name="entity">The entity of the player.</param>
			/// <returns name="ip">The ip of the user in string form.</returns>
			DLL_PUBLIC_I static const std::string GetIP(const int entity);
		};
	}
#ifdef __cplusplus
}
#endif