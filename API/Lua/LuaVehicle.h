#pragma once

#pragma region VehicleObject
struct Vehicle
{
	int entity;

	Vehicle()
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
		if (args == 4 || args == 6)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			std::wstring model = CString::utf8ToUtf16(lua_tostring(L, 2));
			float heading;
			CVector3 poss;
			CVector3 rott;

			if (args == 4)
			{
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
				else if(lua_isnumber(L, 4))
				{
					heading = lua_tonumber(L, 4);
				}
				else if (lua_istable(L, 3))
				{
					lua_getfield(L, 3, "x");
					lua_rawgeti(L, 3, 1);
					rott.fX = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 3, "y");
					lua_rawgeti(L, 3, 1);
					rott.fY = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 3, "z");
					lua_rawgeti(L, 3, 1);
					rott.fZ = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}

			}
			else
			{
				poss.fX = lua_tonumber(L, 3);
				poss.fX = lua_tonumber(L, 4);
				poss.fX = lua_tonumber(L, 5);
				heading = lua_tonumber(L, 6);
			}

			if(lua_isnumber(L, 4))
				veh->entity = API::Vehicle::Create(model, poss, heading);
			else
				veh->entity = API::Vehicle::Create(model, poss, rott);

			veh = nullptr;
		}
		return 0;
	}

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			API::Entity::Destroy(veh->entity);
			veh->entity = -1;
			veh = nullptr;
		}
		return 0;
	}

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			CVector3 poss = API::Entity::GetPosition(veh->entity);
			/*Vec pos(poss.fX, poss.fY, poss.fZ);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, poss.fX);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, poss.fY);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, poss.fZ);
			lua_setfield(L, -2, "z");


			veh = nullptr;
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
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
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

			API::Entity::SetPosition(veh->entity, poss);
			veh = nullptr;
		}
		return 0;
	}

	int GetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			CVector3 rot = API::Entity::GetRotation(veh->entity);
			/*Vec pos(poss.fX, poss.fY, poss.fZ);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, rot.fX);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, rot.fY);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, rot.fZ);
			lua_setfield(L, -2, "z");


			veh = nullptr;
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
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
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

			API::Entity::SetRotation(veh->entity, rott);
			veh = nullptr;
		}
		return 0;
	}

	int GetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			float distance = API::Entity::GetViewDistance(veh->entity);
			lua_newtable(L);

			lua_pushinteger(L, distance);

			veh = nullptr;
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
		if (args == 2 || args == 4)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			if (args == 2)
			{
				float distance = lua_tonumber(L, 2);

				API::Entity::SetViewDistance(veh->entity, distance);
			}
			veh = nullptr;
		}
		return 0;
	}


};
#pragma endregion