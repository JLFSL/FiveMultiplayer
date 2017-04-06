#include <iostream>
#include <sstream>

extern "C" {
#include "inc_lua/lualib.h"
#include "inc_lua/lauxlib.h"
#include "inc_lua/lua.h"
}

#include "LuaBridge/LuaBridge.h"
#include "LuaBridge/RefCountedPtr.h"
#include "LuaBridge/RefCountedObject.h"

#include "api.h"

// Math
#include "sdk/CVector3.h"
#include "sdk/CVector4.h"
#include "sdk/util.h"
#include "sdk/Structs.h"

// API Function Imports
#include "sdk/APIServer.h"
#include "sdk/APIWorld.h"
#include "sdk/APIEntity.h"
#include "sdk/APIVehicle.h"
#include "sdk/APIVisual.h"
#include "sdk/APICheckpoint.h"

using namespace luabridge;

typedef RefCountedObjectType <int> RefCountedObject;

#pragma region LuaVector3
struct Vector3
{
	float coord[3];

	Vector3(float x, float y, float z)
	{
		coord[0] = x;
		coord[1] = y;
		coord[2] = z;
	}
};

struct VecHelper
{
	template <unsigned index>
	static float get(Vector3 const* vec)
	{
		return vec->coord[index];
	}

	template <unsigned index>
	static void set(Vector3* vec, float value)
	{
		vec->coord[index] = value;
	}
};
#pragma endregion

// API Lua Functions
#include "LuaServer.h"
#include "LuaEntity.h"
#include "LuaVehicle.h"
#include "LuaCheckpoint.h"

char scriptName[64] = "gamemodes//test.lua";
lua_State* stateLua;

#pragma region CallBacks
extern "C" DLL_PUBLIC bool API_Initialize(void) {
	stateLua = luaL_newstate();
	std::cout << "API.Lua: Lua state created." << std::endl;
	luaL_openlibs(stateLua);
	std::cout << "API.Lua: Previous libraries opened." << std::endl;

	setHideMetatables(false);
	
	getGlobalNamespace(stateLua)
		.beginClass <Vector3>("Vector3")
			.addConstructor <void(*)(float, float, float)>()
			.addProperty("x", &VecHelper::get <0>, &VecHelper::set <0>)
			.addProperty("y", &VecHelper::get <1>, &VecHelper::set <1>)
			.addProperty("z", &VecHelper::get <2>, &VecHelper::set <2>)
		.endClass()
		.beginClass <Vehicle>("Vehicle")
			.addConstructor <void(*)(void)>()
			.addCFunction("Create", &Vehicle::Create)
			.addCFunction("Destroy", &Vehicle::Destroy)
			.addCFunction("SetPosition", &Vehicle::SetPosition)
			.addCFunction("GetPosition", &Vehicle::GetPosition)
			.addCFunction("GetRotation", &Vehicle::GetRotation)
			.addCFunction("SetRotation", &Vehicle::SetRotation)
			.addCFunction("GetViewDistance", &Vehicle::GetViewDistance)
			.addCFunction("SetViewDistance", &Vehicle::SetViewDistance)
		.endClass()
		.beginClass <Checkpoint>("Checkpoint")
			.addConstructor <void(*)(void)>()
			.addCFunction("Create", &Checkpoint::Create)
			.addCFunction("Destroy", &Checkpoint::Destroy)
			.addCFunction("GetPosition", &Checkpoint::GetPosition)
			.addCFunction("SetPosition", &Checkpoint::SetPosition)
			.addCFunction("Show", &Checkpoint::Show)
			.addCFunction("Hide", &Checkpoint::Hide)
			.addCFunction("GetNearHeight", &Checkpoint::GetNearHeight)
			.addCFunction("SetNearHeight", &Checkpoint::SetNearHeight)
			.addCFunction("GetFarHeight", &Checkpoint::GetFarHeight)
			.addCFunction("SetFarHeight", &Checkpoint::SetFarHeight)
			.addCFunction("GetViewDistance", &Checkpoint::GetViewDistance)
			.addCFunction("SetViewDistance", &Checkpoint::SetViewDistance)
		.endClass();

	// Load scripts
	if (luaL_dofile(stateLua, scriptName) != 0) {
		std::cout << "API.Lua: Error occured when loading " << scriptName << std::endl;
		std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
	}
	else {
		std::cout << "API.Lua: Succesfully loaded " << scriptName << std::endl;
	}
	
	lua_register(stateLua, "PrintMessage", ex_PrintMessage);

	std::cout << "OnGameModeInit() was called." << std::endl;
	
	int result;
	int call = lua_getglobal(stateLua, "OnInit");
	if (call != 0)
	{
		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnInit" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		result = lua_tointeger(stateLua, -1);
		lua_pop(stateLua, 1);
	}

	return true;
}

extern "C" DLL_PUBLIC bool API_Close(void) {
	int result;
	int call = lua_getglobal(stateLua, "OnClose");
	if (call != 0)
	{
		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnClose" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		result = lua_tointeger(stateLua, -1);
		lua_pop(stateLua, 1);
	}

	lua_close(stateLua);
	std::cout << "API.Lua: Lua state closed." << std::endl;
	return true;
}

extern "C" DLL_PUBLIC bool API_OnTick(void) {
	// CRASH
	/*int result;
	int call = lua_getglobal(stateLua, "OnTick");
	if (call != 0)
	{
		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnTick" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		result = lua_tointeger(stateLua, -1);
		lua_pop(stateLua, 1);
	}*/
	return true;
}

extern "C" DLL_PUBLIC bool API_OnPlayerConnecting(const char *guid)
{
	int result;

	std::cout << "OnPlayerConnecting() was called." << std::endl;

	int call = lua_getglobal(stateLua, "OnPlayerConnecting");
	if (call != 0)
	{

		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnPlayerConnecting" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		result = (int)lua_tointeger(stateLua, -1);
		lua_pop(stateLua, 1);
	}
	return result;
}

extern "C" DLL_PUBLIC bool API_OnPlayerConnected(void)
{
	int result;

	std::cout << "OnPlayerConnected() was called." << std::endl;

	int call = lua_getglobal(stateLua, "OnPlayerConnected");
	if (call != 0)
	{

		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnPlayerConnected" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		result = (int)lua_tointeger(stateLua, -1);
		lua_pop(stateLua, 1);
	}
	return result;
}

extern "C" DLL_PUBLIC void API_OnEntityEnterCheckpoint(int checkpoint, int entity)
{
	int result;

	std::cout << "OnEntityEnterCheckpoint() was called." << std::endl;

	int call = lua_getglobal(stateLua, "OnEntityEnterCheckpoint");
	if (call != 0)
	{

		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnEntityEnterCheckpoint" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		result = (int)lua_tointeger(stateLua, -1);
		lua_pop(stateLua, 1);
	}
}

extern "C" DLL_PUBLIC void API_OnEntityExitCheckpoint(int checkpoint, int entity)
{
	int result;

	std::cout << "OnEntityExitCheckpoint() was called." << std::endl;

	int call = lua_getglobal(stateLua, "OnEntityExitCheckpoint");
	if (call != 0)
	{

		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnEntityExitCheckpoint" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		result = (int)lua_tointeger(stateLua, -1);
		lua_pop(stateLua, 1);
	}
}
#pragma endregion