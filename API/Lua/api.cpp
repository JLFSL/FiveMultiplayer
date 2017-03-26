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

// API Function Imports
#include "sdk/APIServer.h"
#include "sdk/APIWorld.h"
#include "sdk/APIEntity.h"
#include "sdk/APIVehicle.h"
#include "sdk/APIVisual.h"

// API Lua Functions
#include "LuaServer.h"
#include "LuaEntity.h"
#include "LuaVehicle.h"

using namespace luabridge;

typedef RefCountedObjectType <int> RefCountedObject;

#pragma region Objects
struct Vec
{
	float coord[3];

	Vec(float x, float y, float z)
	{
		coord[0] = x;
		coord[1] = y;
		coord[2] = z;
	}
};

struct VecHelper
{
	template <unsigned index>
	static float get(Vec const* vec)
	{
		return vec->coord[index];
	}

	template <unsigned index>
	static void set(Vec* vec, float value)
	{
		vec->coord[index] = value;
	}
};

struct Vehicle
{
	int entity;

	Vehicle()
	{
		entity = -1;
	}

	int Create(lua_State* L)
	{
		/*
			Arg 1: The pointer of the Object
			Arg 2+: The arguments entered
		*/
		const int args = lua_gettop(L);
		if (args == 4 || args == 6)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			std::wstring model = utf8ToUtf16(lua_tostring(L, 2));
			float heading;
			CVector3 poss;
			
			if (args == 4)
			{
				heading = lua_tonumber(L, 4);

				if (lua_isuserdata(L, 3))
				{
					Vec* pos = reinterpret_cast<Vec*>(lua_touserdata(L, 3));
					poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
					pos = nullptr;
				}
				else if (lua_istable(L, 3))
				{
					lua_getfield(L, 3, "x");
					lua_rawgeti(L, 3, 1);
					poss.fX = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 3, "y");
					lua_rawgeti(L, 3, 1);
					poss.fY = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 3, "z");
					lua_rawgeti(L, 3, 1);
					poss.fZ = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				poss.fX = lua_tonumber(L, 3);
				poss.fX = lua_tonumber(L, 4);
				poss.fX = lua_tonumber(L, 5);
				heading = lua_tonumber(L, 6);
			}

			veh->entity = API::Vehicle::Create(model, poss, heading);

			veh = nullptr;
		}
		return 0;
	}

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			API::Entity::Destroy(veh->entity);
			veh->entity = -1;
			veh = nullptr;
		}
		return 0;
	}

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));

			CVector3 poss = API::Entity::GetPosition(veh->entity);
			/*Vec pos(poss.fX, poss.fY, poss.fZ);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, poss.fX);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, poss.fY);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, poss.fZ);
			lua_setfield(L, -2, "z");


			veh = nullptr;
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Vehicle* veh = reinterpret_cast<Vehicle*>(lua_touserdata(L, 1));
			CVector3 poss;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vec* pos = reinterpret_cast<Vec*>(lua_touserdata(L, 2));
					poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
					pos = nullptr;
				}
				else if (lua_istable(L, 2))
				{
					lua_getfield(L, 2, "x");
					lua_rawgeti(L, 2, 1);
					poss.fX = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "y");
					lua_rawgeti(L, 2, 1);
					poss.fY = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "z");
					lua_rawgeti(L, 2, 1);
					poss.fZ = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				poss.fX = lua_tonumber(L, 2);
				poss.fX = lua_tonumber(L, 3);
				poss.fX = lua_tonumber(L, 4);
			}
			
			API::Entity::SetPosition(veh->entity, poss);
			veh = nullptr;
		}
		return 0;
	}
};
#pragma endregion

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
		.beginClass <Vec>("Vector3")
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
	int call = lua_getglobal(stateLua, "OnGameModeInit");
	if (call != 0)
	{
		int error = lua_pcall(stateLua, 0, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnGameModeInit" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		result = lua_tointeger(stateLua, -1);
		lua_pop(stateLua, 1);
	}

	return true;
}

extern "C" DLL_PUBLIC bool API_Close(void) {
	lua_close(stateLua);
	std::cout << "API.Lua: Lua state closed." << std::endl;
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
#pragma endregion