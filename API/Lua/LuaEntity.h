#ifndef __LUAENTITY_H__
#define __LUAENTITY_H__

class Entity {
public:
	static int GetEntities(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			std::vector<int> entities = API::Entity::GetEntities(lua_tointeger(L,1));

			lua_newtable(L);

			for (int i = 0; i < entities.size(); i++)
			{
				lua_pushinteger(L, entities[i]);
			}

		}
		else
		{
			std::cerr << "GetEntities requires arg (int type)." << std::endl;
			lua_pushnil(L);
		}
		lua_pop(L, args);
		return 1;
	}
};
#endif