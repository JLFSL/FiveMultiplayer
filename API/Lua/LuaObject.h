#ifndef __LUAOBJECT_H__
#define __LUAOBJECT_H__

struct Object
{
	int entity;

	Object()
	{
		entity = -1;
	}
	//	void Create(const std::wstring model, const CVector3 position, const CVector3 rotation, const bool dynamic)
	//	void Create(const int hash, const CVector3 position, const CVector3 rotation, const bool dynamic)
	int Create(lua_State* L)
	{
		/*
		Arg 1: The pointer of the Object
		Arg 2+: The arguments entered
		*/
		const int args = lua_gettop(L);
		if (args == 4)
		{
			Object* ent = reinterpret_cast<Object*>(lua_touserdata(L, 1));

			std::wstring model;
			int hash = -1;
			CVector3 poss;
			CVector3 rott;

			if (lua_isstring(L, 2))
				model = CString::utf8ToUtf16(lua_tostring(L, 2));
			else
				hash = lua_tointeger(L, 2);

			if (lua_isuserdata(L, 3))
			{
				Vector3* pos = reinterpret_cast<Vector3*>(lua_touserdata(L, 3));
				poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
				pos = nullptr;
			}
			else if (lua_istable(L, 3))
			{
				lua_getfield(L, 3, "x");
				lua_rawgeti(L, 3, 1);
				poss.fX = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "y");
				lua_rawgeti(L, 3, 1);
				poss.fY = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "z");
				lua_rawgeti(L, 3, 1);
				poss.fZ = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}

			if (lua_isuserdata(L, 4))
			{
				Vector3* rot = reinterpret_cast<Vector3*>(lua_touserdata(L, 3));
				rott = { rot->coord[0], rot->coord[1], rot->coord[2] };
				rot = nullptr;
			}
			else if (lua_istable(L, 4))
			{
				lua_getfield(L, 4, "x");
				lua_rawgeti(L, 4, 1);
				rott.fX = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 4, "y");
				lua_rawgeti(L, 4, 1);
				rott.fY = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 4, "z");
				lua_rawgeti(L, 4, 1);
				rott.fZ = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}

			bool dynamic = lua_toboolean(L, 5);

			if (lua_isinteger(L, 2))
				ent->entity = API::Object::Create(hash, poss, rott, dynamic);
			else
				ent->entity = API::Object::Create(model, poss, rott, dynamic);

			ent = nullptr;
		}
		return 0;
	}

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = reinterpret_cast<Object*>(lua_touserdata(L, 1));
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
			Object* ent = reinterpret_cast<Object*>(lua_touserdata(L, 1));

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
			Object* ent = reinterpret_cast<Object*>(lua_touserdata(L, 1));
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

	int GetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = reinterpret_cast<Object*>(lua_touserdata(L, 1));

			CVector3 rot = API::Entity::GetRotation(ent->entity);
			/*Vec pos(poss.fX, poss.fY, poss.fZ);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, rot.fX);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, rot.fY);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, rot.fZ);
			lua_setfield(L, -2, "z");


			ent = nullptr;
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	int SetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Object* ent = reinterpret_cast<Object*>(lua_touserdata(L, 1));
			CVector3 rott;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vector3* rot = reinterpret_cast<Vector3*>(lua_touserdata(L, 2));
					rott = { rot->coord[0], rot->coord[1], rot->coord[2] };
					rot = nullptr;
				}
				else if (lua_istable(L, 2))
				{
					lua_getfield(L, 2, "x");
					lua_rawgeti(L, 2, 1);
					rott.fX = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "y");
					lua_rawgeti(L, 2, 1);
					rott.fY = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "z");
					lua_rawgeti(L, 2, 1);
					rott.fZ = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				rott.fX = lua_tonumber(L, 2);
				rott.fX = lua_tonumber(L, 3);
				rott.fX = lua_tonumber(L, 4);
			}

			API::Entity::SetRotation(ent->entity, rott);
			ent = nullptr;
		}
		return 0;
	}

	int GetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = reinterpret_cast<Object*>(lua_touserdata(L, 1));

			const float distance = API::Entity::GetViewDistance(ent->entity);

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
			Object* ent = reinterpret_cast<Object*>(lua_touserdata(L, 1));

			const float distance = lua_tonumber(L, 2);

			API::Entity::SetViewDistance(ent->entity, distance);
			ent = nullptr;
		}
		return 0;
	}

	int GetTextureVariation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = reinterpret_cast<Object*>(lua_touserdata(L, 1));

			const int texture = API::Object::GetTextureVariation(ent->entity);

			lua_pushinteger(L, texture);

			ent = nullptr;
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	int SetTextureVariation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Object* ent = reinterpret_cast<Object*>(lua_touserdata(L, 1));

			const int texture = lua_tointeger(L, 2);

			API::Object::SetTextureVariation(ent->entity, texture);
			ent = nullptr;
		}
		return 0;
	}
};
#endif