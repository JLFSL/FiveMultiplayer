#pragma once

static int ex_Destroy(lua_State* state)
{
	const int args = lua_gettop(state);
	if (args == 1)
	{
		API::Entity::Destroy(lua_tointeger(state, 1));
	}
	else
	{
		std::cerr << "Destroy requires args (entity)." << std::endl;
	}
	lua_pop(state, args);
	return 0;
}

static int ex_GetPosition(lua_State* state)
{
	const int args = lua_gettop(state);
	if (args == 1)
	{
		CVector3 pos = API::Entity::GetPosition(lua_tointeger(state, 1));
		lua_pop(state, args);

		lua_createtable(state, 0, 3);

		lua_pushnumber(state, pos.fX);
		lua_setfield(state, -2, "x");

		lua_pushnumber(state, pos.fY);
		lua_setfield(state, -2, "y");

		lua_pushnumber(state, pos.fZ);
		lua_setfield(state, -2, "z");
		//lua_settable(state, -3);
	}
	else
	{
		std::cerr << "GetPosition requires args (entity)." << std::endl;
		lua_pushnil(state);
	}
	return 1;
}