#include "inc_lua/lua.hpp"

#include <iostream>
using namespace std;

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport)
#endif
#else
#define DLL_PUBLIC 
#endif

char scriptName[64] = "gamemodes//test.lua";
lua_State* stateLua;

int OnGameModeInit(lua_State* state);

extern "C" int ex_SendMessageToPlayer(lua_State* state) {
	__declspec(dllimport) int SendMessageToPlayer(int playerid, const char *message);
	SendMessageToPlayer(lua_tointeger(stateLua, 1), lua_tostring(stateLua, 2));
	return 1;
}

extern "C" DLL_PUBLIC void API_Initialize(void) {
	stateLua = luaL_newstate();
	cout << "API.Lua: Lua state created." << endl;
	luaL_openlibs(stateLua);
	cout << "API.Lua: Previous libraries opened." << endl;

	if (luaL_dofile(stateLua, scriptName) != 0) {
		cout << "API.Lua: Error occured when loading " << scriptName << endl;
		cout << "Error: " << lua_tostring(stateLua, -1) << endl;
	}
	else {
		cout << "API.Lua: Succesfully loaded " << scriptName << endl;
	}

	//__declspec(dllimport) int SendMessageToPlayer(int playerid, const char *message);
	//SendMessageToPlayer(0, "test");
	lua_register(stateLua, "SendMessageToPlayer", ex_SendMessageToPlayer);

	OnGameModeInit(stateLua);
}

extern "C" DLL_PUBLIC void API_Close(void) {
	lua_close(stateLua);
	cout << "API.Lua: Lua state closed." << endl;
}

int OnGameModeInit(lua_State* state)
{
	int result;

	cout << "API.Lua: OnGameModeInit() was called." << endl;

	int call = lua_getglobal(state, "OnGameModeInit");
	if (call != 0) {

		int error = lua_pcall(state, 0, 1, 0);
		if (error != 0) {
			cout << "API.Lua: Error occured when executing OnGameModeInit" << endl;
			cout << "Error: " << lua_tostring(state, -1) << endl;
		}

		result = (int)lua_tointeger(state, -1);
		lua_pop(state, 1);
	}
	return result;
}

/*
__declspec(dllimport) int SendMessageToPlayer(int playerid, char *message);

SendMessageToPlayer(5, "test");
*/