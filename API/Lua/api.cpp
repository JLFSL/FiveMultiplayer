#include "../../Shared/Common.h"

extern "C" {
	#include "inc_lua/lua.h"
	#include "inc_lua/lualib.h"
	#include "inc_lua/lauxlib.h"
}

#include <iostream>
using namespace std;

char scriptName[64] = "gamemodes//test.lua";
lua_State* stateLua;

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

	return true;
}

extern "C" DLL_PUBLIC bool API_Close(void) {
	lua_close(stateLua);
	cout << "API.Lua: Lua state closed." << endl;
	return true;
}

extern "C" DLL_PUBLIC bool API_OnTick(void) {
	// Every server tick this gets called
	//std::cout << "tick" << std::endl;
	return true;
}