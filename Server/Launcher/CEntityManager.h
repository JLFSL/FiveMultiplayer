#pragma once

#ifndef CEntityManager_h
#define CEntityManager_h

template<class T, Entity max>
class CEntityManager
{
private:
	T* g_Entities[max];
public:
	CEntityManager()
	{
		for (Entity id = 0; id < max; ++id)
		{
			g_Entities[id] = nullptr;
		}
	}
	~CEntityManager()
	{
		// Loop through all entities
		for (Entity id = 0; id < max; ++id)
		{
			// Check if ID exists
			if (DoesExists(id))
			{
				// we could call Delete() here, but there's no need to get this done in a clean way as we're about to be deleted
				delete g_Entities[id];
			}
		}
	}
	inline bool		DoesExists(Entity entityId)
	{
		return Exists(entityId);
	}

	inline bool		Exists(Entity entityId)
	{
		return (entityId < max && g_Entities[entityId] != nullptr);
	}

	inline void Pulse()
	{
		// Loop through all entities
		for (Entity id = 0; id < max; ++id)
		{
			// Check if ID exists
			if (DoesExists(id))
			{
				g_Entities[id]->Pulse();
			}
		}
	}
};

#endif