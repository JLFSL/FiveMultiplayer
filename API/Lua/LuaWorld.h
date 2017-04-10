#ifndef __LUAWORLD_H__
#define __LUAWORLD_H__

class World {
public:
	static int GetTime(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 0)
		{
			int hour, minute, second;
			API::World::GetTime(&hour, &minute, &second);

			lua_pushinteger(L, hour);
			lua_pushinteger(L, minute);
			lua_pushinteger(L, second);
		}
		else
		{
			std::cerr << "GetTime requires args ()." << std::endl;
			lua_pushnil(L);
			lua_pushnil(L);
			lua_pushnil(L);
		}
		lua_pop(L, args);
		return 3;
	}

	static int SetTime(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			API::World::SetTime(lua_tointeger(L, 1), lua_tointeger(L, 2), lua_tointeger(L, 3));
		}
		else
		{
			std::cerr << "SetTime requires args (int hour, int minute, int second)." << std::endl;
		}
		lua_pop(L, args);
		return 0;
	}

	static int GetWeather(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 0)
		{
			lua_pushstring(L, CString::utf16ToUtf8(API::World::GetWeather()).c_str());	
		}
		else
		{
			std::cerr << "GetWeather requires args ()." << std::endl;
			lua_pushnil(L);
		}
		lua_pop(L, args);
		return 1;
	}

	static int SetWeather(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			API::World::SetWeather(CString::utf8ToUtf16(lua_tostring(L, 1)));
		}
		else
		{
			std::cerr << "SetWeather requires args (string weather)." << std::endl;
		}
		lua_pop(L, args);
		return 0;
	}

	static int LoadIPL(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			API::World::LoadIPL(CString::utf8ToUtf16(lua_tostring(L, 1)));
		}
		else
		{
			std::cerr << "LoadIPL requires args (string ipl)." << std::endl;
		}
		lua_pop(L, args);
		return 0;
	}

	static int UnloadIPL(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			API::World::UnloadIPL(CString::utf8ToUtf16(lua_tostring(L, 1)));
		}
		else
		{
			std::cerr << "UnloadIPL requires args (string ipl)." << std::endl;
		}
		lua_pop(L, args);
		return 0;
	}

};
#endif