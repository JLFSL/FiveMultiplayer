#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class Vehicle
		{
		public:
			/// <summary>
			/// Creates a vehicle of a desired model at the position defined
			/// </summary>
			/// <param name="model">The model of the vehicle you wish to create</param>
			/// <param name="position">The position you wish to create the vehicle at</param>
			/// <param name="heading">The direction you wish the vehicle to be facing</param>
			/// <returns name="entity">The vehicles server entity id</returns>
			DLL_PUBLIC_I static const int Create(const std::wstring model, const CVector3 position, const float heading);

			/// <summary>
			/// Creates a vehicle of a desired model at the position defined
			/// </summary>
			/// <param name="model">The model of the vehicle you wish to create</param>
			/// <param name="position">The position you wish to create the vehicle at</param>
			/// <param name="heading">The rotation you wish to set the vehicle at</param>
			/// <returns name="entity">The vehicles server entity id</returns>
			DLL_PUBLIC_I static const int Create(const std::wstring model, const CVector3 position, const CVector3 rotation);
		};
	}
#ifdef __cplusplus
}
#endif

class Vehicle {
private:
	int Entity;
public:
	const int GetEntity() { return Entity; }

	void Create(const std::wstring model, const CVector3 position, const float heading)
	{
		Entity = API::Vehicle::Create(model, position, heading);
	}

	void Create(const std::wstring model, const CVector3 position, const CVector3 rotation)
	{
		Entity = API::Vehicle::Create(model, position, rotation);
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

	const float GetViewDistance()
	{
		return API::Entity::GetViewDistance(Entity);
	}

	void SetViewDistance(const float distance)
	{
		API::Entity::SetViewDistance(Entity, distance);
	}



};