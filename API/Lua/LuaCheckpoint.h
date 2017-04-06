#ifndef __LUACHECKPOINT_H__
#define __LUACHECKPOINT_H__

struct Checkpoint
{
	int entity;

	Checkpoint()
	{
		entity = -1;
	}
	
	int Create(lua_State* L)
	{
		/*
		Arg 1: The pointer of the Object
		Arg 2+: The arguments entered
		*/
		const int args = lua_gettop(L);
		if (args == 7)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));

			CVector3 poss;
			CVector3 pointt;

			// Position
			if (lua_isuserdata(L, 2))
			{
				Vector3* pos = reinterpret_cast<Vector3*>(lua_touserdata(L, 3));
				poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
				pos = nullptr;
			}
			else if (lua_istable(L, 2))
			{
				lua_getfield(L, 2, "x");
				lua_rawgeti(L, 2, 1);
				poss.fX = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "y");
				lua_rawgeti(L, 2, 1);
				poss.fY = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "z");
				lua_rawgeti(L, 2, 1);
				poss.fZ = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}
			// PointTo
			if (lua_isuserdata(L, 3))
			{
				Vector3* point = reinterpret_cast<Vector3*>(lua_touserdata(L, 3));
				pointt = { point->coord[0], point->coord[1], point->coord[2] };
				point = nullptr;
			}
			else if (lua_istable(L, 3))
			{
				lua_getfield(L, 3, "x");
				lua_rawgeti(L, 3, 1);
				pointt.fX = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "y");
				lua_rawgeti(L, 3, 1);
				pointt.fY = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "z");
				lua_rawgeti(L, 3, 1);
				pointt.fZ = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}
			// Type
			const int type = lua_tonumber(L, 4);
			// Radius
			const float radius = lua_tonumber(L, 5);
			// Color
			Color col;
			if (lua_istable(L, 6))
			{
				lua_getfield(L, 6, "r");
				lua_rawgeti(L, 6, 1);
				col.Red = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 6, "g");
				lua_rawgeti(L, 6, 1);
				col.Green = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 6, "b");
				lua_rawgeti(L, 6, 1);
				col.Blue = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 6, "a");
				lua_rawgeti(L, 6, 1);
				col.Alpha = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}
			// Reserved
			const int reserved = lua_tonumber(L, 7);

			//DLL_PUBLIC_I static const int Create(const CVector3 position, const CVector3 pointto, const int type, const float radius, const Color color, const int reserved);
			ent->entity = API::Checkpoint::Create(poss, pointt, type, radius, col, reserved);

			ent = nullptr;
		}
		return 0;
	}

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));
			API::Entity::Destroy(ent->entity);
			ent->entity = -1;
			ent = nullptr;
		}
		return 0;
	}

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));

			CVector3 poss = API::Entity::GetPosition(ent->entity);
			/*Vec pos(poss.fX, poss.fY, poss.fZ);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, poss.fX);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, poss.fY);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, poss.fZ);
			lua_setfield(L, -2, "z");


			ent = nullptr;
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));
			CVector3 poss;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vector3* pos = reinterpret_cast<Vector3*>(lua_touserdata(L, 2));
					poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
					pos = nullptr;
				}
				else if (lua_istable(L, 2))
				{
					lua_getfield(L, 2, "x");
					lua_rawgeti(L, 2, 1);
					poss.fX = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "y");
					lua_rawgeti(L, 2, 1);
					poss.fY = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "z");
					lua_rawgeti(L, 2, 1);
					poss.fZ = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				poss.fX = lua_tonumber(L, 2);
				poss.fX = lua_tonumber(L, 3);
				poss.fX = lua_tonumber(L, 4);
			}

			API::Entity::SetPosition(ent->entity, poss);
			ent = nullptr;
		}
		return 0;
	}

	int Show(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));

			const int player = lua_tonumber(L, 2);

			API::Checkpoint::Show(ent->entity, player);

			ent = nullptr;
		}
		return 0;
	}

	int Hide(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));

			const int player = lua_tonumber(L, 2);

			API::Checkpoint::Hide(ent->entity, player);

			ent = nullptr;
		}
		return 0;
	}

	int GetNearHeight(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));

			float height = API::Checkpoint::GetNearHeight(ent->entity);
			
			lua_pushnumber(L, height);

			ent = nullptr;
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	int SetNearHeight(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));

			const float height = lua_tonumber(L, 2);

			API::Checkpoint::SetNearHeight(ent->entity, height);

			ent = nullptr;
		}
		return 0;
	}

	int GetFarHeight(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));

			float height = API::Checkpoint::GetFarHeight(ent->entity);

			lua_pushnumber(L, height);

			ent = nullptr;
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	int SetFarHeight(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));

			const float height = lua_tonumber(L, 2);

			API::Checkpoint::SetFarHeight(ent->entity, height);

			ent = nullptr;
		}
		return 0;
	}

	int GetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));

			float distance = API::Entity::GetViewDistance(ent->entity);

			lua_pushnumber(L, distance);

			ent = nullptr;
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	int SetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = reinterpret_cast<Checkpoint*>(lua_touserdata(L, 1));

			float distance = lua_tonumber(L, 2);

			API::Entity::SetViewDistance(ent->entity, distance);
			ent = nullptr;
		}
		return 0;
	}
};

#endif