#pragma once

void PrintTable(lua_State *L)
{
	lua_pushnil(L);

	while (lua_next(L, -2) != 0)
	{
		if (lua_isstring(L, -1))
			printf("%s = %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
		else if (lua_isnumber(L, -1))
			printf("%s = %d\n", lua_tostring(L, -2), lua_tonumber(L, -1));
		else if (lua_istable(L, -1))
			PrintTable(L);

		lua_pop(L, 1);
	}
}

static int ex_CreateVehicle(lua_State* state)
{
	const int args = lua_gettop(state);
	if (args == 3)
	{
		std::string model = lua_tostring(state, 1);
		float heading = lua_tonumber(state, 3);

		CVector3 pos;
		
		if (lua_istable(state, 2))
		{
			lua_getfield(state, 2, "x");
			lua_rawgeti(state, 2, 1);
			pos.fX = lua_tonumber(state, -2);
			lua_pop(state, 1);

			lua_getfield(state, 2, "y");
			lua_rawgeti(state, 2, 1);
			pos.fY = lua_tonumber(state, -2);
			lua_pop(state, 1);

			lua_getfield(state, 2, "z");
			lua_rawgeti(state, 2, 1);
			pos.fZ = lua_tonumber(state, -2);
			lua_pop(state, 1);
		}

		int entity = API::Vehicle::CreateVehicle(model, pos, heading);

		lua_pushinteger(state, entity);
	}
	else
	{
		std::cerr << "CreateVehicle requires args (string model, table vector3, float heading)." << std::endl;
		lua_pushnil(state);
	}
	return 1;
}