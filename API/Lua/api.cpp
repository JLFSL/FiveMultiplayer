#include "..\..\Shared\Common.h"
#include "inc_lua\lua.hpp"

#include <iostream>
using namespace std;

char scriptName[64] = "gamemodes\\test.lua";
lua_State* stateLua;

int OnGameModeInit(lua_State* state);
int OnGameModeExit(lua_State* state);

extern "C" int ex_PrintMessage(lua_State* state) {
	DLL_PUBLIC_I int PrintMessage(const char *message);
	PrintMessage(lua_tostring(stateLua, 1));
	return 1;
}

extern "C" DLL_PUBLIC bool API_Initialize(void) {
	stateLua = luaL_newstate();
	cout << endl << "API.Lua: Lua state created." << endl;
	luaL_openlibs(stateLua);
	cout << "API.Lua: Previous libraries opened." << endl;

	if (luaL_dofile(stateLua, scriptName) != 0) {
		cout << "API.Lua: Error occured when loading " << scriptName << endl;
		cout << "Error: " << lua_tostring(stateLua, -1) << endl;
	}
	else {
		cout << "API.Lua: Succesfully loaded " << scriptName << endl;
	}

	lua_register(stateLua, "PrintMessage", ex_PrintMessage);

	OnGameModeInit(stateLua);

	return true;
}

extern "C" DLL_PUBLIC bool API_Close(void) {
	OnGameModeExit(stateLua);

	lua_close(stateLua);
	cout << "API.Lua: Lua state closed." << endl;

	return true;
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

int OnGameModeExit(lua_State* state)
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