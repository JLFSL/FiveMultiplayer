#pragma once

static int ex_PrintMessage(lua_State* state)
{
	const int args = lua_gettop(state);
	if (args == 1)
	{
		API::Server::PrintMessage(lua_tostring(state, 1));
	}
	else
	{
		std::cerr << "PrintMessage requires args (string)." << std::endl;
		lua_pushnil(state);
	}
	lua_pop(state, args);
	return 0;
}