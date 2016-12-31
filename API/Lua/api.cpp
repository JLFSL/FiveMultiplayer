#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport)
#endif
#else
#define DLL_PUBLIC 
#endif

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

#pragma region CallBacks
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

extern "C" DLL_PUBLIC bool API_OnPlayerConnecting(const char *guid)
{
	int result;

	cout << "OnPlayerConnecting() was called." << endl;

	int call = lua_getglobal(stateLua, "OnPlayerConnecting");
	if (call != 0)
	{

		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			cout << "Error occured when executing OnPlayerConnecting" << endl;
			cout << "Error: " << lua_tostring(stateLua, -1) << endl;
		}

		result = (int)lua_tointeger(stateLua, -1);
		lua_pop(stateLua, 1);
	}
	return result;
}

extern "C" DLL_PUBLIC bool API_OnPlayerConnected(void)
{
	int result;

	cout << "OnPlayerConnected() was called." << endl;

	int call = lua_getglobal(stateLua, "OnPlayerConnected");
	if (call != 0)
	{

		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			cout << "Error occured when executing OnPlayerConnected" << endl;
			cout << "Error: " << lua_tostring(stateLua, -1) << endl;
		}

		result = (int)lua_tointeger(stateLua, -1);
		lua_pop(stateLua, 1);
	}
	return result;
}
#pragma endregion