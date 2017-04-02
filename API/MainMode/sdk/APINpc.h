#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class NPC
		{
		public:
			/// <summary>
			/// Creates a NPC of a desired model at the position defined
			/// </summary>
			/// <param name="model">The model of the npc you wish to create</param>
			/// <param name="position">The position you wish to create the npc at</param>
			/// <param name="heading">The heading you wish to have the npc facing</param>
			/// <returns name="entity">The npc server entity id</returns>
			DLL_PUBLIC_I static const int Create(const std::wstring model, const CVector3 position, const CVector3 rotation);
		};
	}
#ifdef __cplusplus
}
#endif

class NPC {
private:
	int Entity;
public:
	const int GetEntity() { return Entity; }

	void Create(const std::wstring model, const CVector3 position, const CVector3 rotation)
	{
		Entity = API::NPC::Create(model, position, rotation);
	}

	void Destroy() 
	{
		API::Entity::Destroy(Entity);
		Entity = -1;
	}

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

};