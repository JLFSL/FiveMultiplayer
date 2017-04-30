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

		};
	}
#ifdef __cplusplus
}
#endif

class Player {
private:
	int Entity = -1;
public:
	const int GetEntity() { return Entity; }
	void SetEntity(const int entity) { Entity = entity; }

	const CVector3 GetPosition()
	{
		return API::Entity::GetPosition(Entity);
	}

	void SetPosition(const CVector3 position)
	{
		API::Entity::SetPosition(Entity, position);
	}

	const CVector3 GetRotation()
	{
		return API::Entity::GetRotation(Entity);
	}

	void SetRotation(const CVector3 position)
	{
		API::Entity::SetRotation(Entity, position);
	}

	const PedComponent GetPedComponent(const int componentid)
	{
		return API::Entity::GetPedComponent(Entity, componentid);
	}

	void SetPedComponent(const int componentid, const PedComponent component)
	{
		API::Entity::SetPedComponent(Entity, componentid, component);
	}

	const PedHeadBlend GetPedHeadBlend()
	{
		return API::Entity::GetPedHeadBlend(Entity);
	}

	void SetPedHeadBlend(const PedHeadBlend headblend)
	{
		API::Entity::SetPedHeadBlend(Entity, headblend);
	}

	const PedHeadOverlay GetPedHeadOverlay(const int overlayid)
	{
		return API::Entity::GetPedHeadOverlay(Entity, overlayid);
	}

	void SetPedHeadOverlay(const int overlayid, const PedHeadOverlay overlay)
	{
		API::Entity::SetPedHeadOverlay(Entity, overlayid, overlay);
	}

	const PedProp GetPedProp(const int compotentid)
	{
		return API::Entity::GetPedProp(Entity, compotentid);
	}

	void SetPedProp(const int compotentid, const PedProp prop)
	{
		API::Entity::SetPedProp(Entity, compotentid, prop);
	}

	const float GetPedFaceFeature(const int index)
	{
		return API::Entity::GetPedFaceFeature(Entity, index);
	}

	void SetPedFaceFeature(const int index, const float scale)
	{
		API::Entity::SetPedFaceFeature(Entity, index, scale);
	}

	const float GetViewDistance()
	{
		return API::Entity::GetViewDistance(Entity);
	}

	void SetViewDistance(const float distance)
	{
		API::Entity::SetViewDistance(Entity, distance);
	}

	const std::wstring GetModel()
	{
		return API::Player::GetModel(Entity);
	}

	void SetModel(const std::wstring model)
	{
		API::Player::SetModel(Entity, model);
	}

	// Sends a Message above the map for this player.
	void ShowMessageAboveMap(const std::wstring message, const std::wstring pic, const int icontype, const std::wstring sender, const std::wstring subject)
	{
		API::Visual::ShowMessageAboveMapToPlayer(Entity, message, pic, icontype, sender, subject);
	}

	void SendChatMessage(const std::string message)
	{
		API::Visual::SendChatMessageToPlayer(Entity, message);
	}

	const std::string GetUsername()
	{
		API::Player::GetUsername(Entity);
	}

	void ShowCursor(const bool show)
	{
		API::Visual::ShowCursor(Entity, show);
	}

	void LoadURL(const std::string url, const std::string appcode = "", const bool remote = false)
	{
		API::CEF::LoadURL(Entity, url, appcode, remote);
	}

	void JavaScriptCall(std::string call)
	{
		API::CEF::JavaScriptCall(Entity, call);
	}

	const bool IsControllable()
	{
		return API::Player::IsControllable(Entity);
	}

	void SetControllable(bool disablecontrols, bool frozen = true)
	{
		API::Player::SetControllable(Entity, disablecontrols, frozen);
	}
};