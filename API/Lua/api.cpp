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
	Vec()
	{
		coord[0] = 0;
		coord[1] = 0;
		coord[2] = 0;
	}

	float coord[3];
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

	//int Create(lua_State* L)
	//{
	//	// Arg 1 is the userdata of the object
	//	// Arg 2 onwards is the input arguments
	//	const int args = lua_gettop(L);
	//	if (args == 4)
	//	{
	//		std::string model = lua_tostring(L, 2);
	//		float heading = lua_tonumber(L, 4);
	//		CVector3 poss;

	//		if (lua_isuserdata(L, 3))
	//		{
	//			Vec* pos = reinterpret_cast<Vec*>(lua_touserdata(L, 3));
	//			poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
	//		}
	//		else if (lua_istable(L, 3))
	//		{
	//			lua_getfield(L, 3, "x");
	//			lua_rawgeti(L, 3, 1);
	//			poss.fX = lua_tonumber(L, -2);
	//			lua_pop(L, 1);

	//			lua_getfield(L, 3, "y");
	//			lua_rawgeti(L, 3, 1);
	//			poss.fY = lua_tonumber(L, -2);
	//			lua_pop(L, 1);

	//			lua_getfield(L, 3, "z");
	//			lua_rawgeti(L, 3, 1);
	//			poss.fZ = lua_tonumber(L, -2);
	//			lua_pop(L, 1);
	//		}

	//		this->entity = API::Vehicle::CreateVehicle(model, poss, heading);
	//	}
	//	return 0;
	//}

	//int GetPosition(lua_State* L)
	//{
	//	CVector3 poss = API::Entity::GetPosition(entity);
	//	//Vec pos = { poss.fX, poss.fY, poss.fZ };
	//	//lua_pushlightuserdata(L, &pos);
	//	return 1;
	//}

	//int SetPosition(lua_State* L)
	//{
	//	if (lua_isuserdata(L, 1))
	//	{
	//		Vec* pos = reinterpret_cast<Vec*>(lua_touserdata(L, 1));

	//		std::cout << pos->coord[0] << ":" << pos->coord[1] << ":" << pos->coord[2] << std::endl;
	//		CVector3 poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
	//		API::Entity::SetPosition(entity, poss);
	//		//delete pos;
	//	}
	//	return 0;
	//}
};

struct VehicleHelper
{
//	virtual void create(const char* string/*Vehicle* veh, const char* model, Vec position, float heading*/)
//	{
		//std::cout << string << std::endl;
		//CVector3 pos = { position.coord[0], position.coord[1], position.coord[2] };
		//veh->entity = API::Vehicle::CreateVehicle(model, pos, heading);
	//}

	static void create(const std::string& text)
	{
		std::cout << ": " << text << std::endl;
	}

	int creates(lua_State* L)
	{
		// Arg 1 is the userdata of the object
		// Arg 2 onwards is the input arguments
		const int args = lua_gettop(L);
		if (args == 4)
		{
			std::string model = lua_tostring(L, 2);
			float heading = lua_tonumber(L, 4);
			CVector3 poss;

			if (lua_isuserdata(L, 3))
			{
				Vec* pos = reinterpret_cast<Vec*>(lua_touserdata(L, 3));
				poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
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

			//this->entity = API::Vehicle::CreateVehicle(model, poss, heading);
		}
		return 0;
	}

	template <unsigned index>
	static void set(Vec* vec, float value)
	{
		vec->coord[index] = value;
	}
};

struct C
{
	C() {}

	Vec v;
	Vec& get()
	{
		return v;
	}
	void set(Vec const& v_)
	{
		v = v_;
	}

	static int static_cfunc(lua_State*)
	{
		return 0;
	}

	int cfunc(lua_State*)
	{
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
		.addConstructor <void(*)(void)>()
		.addProperty("x", &VecHelper::get <0>, &VecHelper::set <0>)
		.addProperty("y", &VecHelper::get <1>, &VecHelper::set <1>)
		.addProperty("z", &VecHelper::get <2>, &VecHelper::set <2>)
		.endClass()
		.beginClass <Vehicle>("Vehicle")
		.addConstructor <void(*)(void)>()
		.addFunction("Create", &VehicleHelper::create)
		//.addCFunction("Creates", &VehicleHelper::creates)
		.endClass();
		/*.beginClass <Vehicle>("Vehicle")
			.addConstructor <void(*)(void)>()
			.addCFunction("Create", &Vehicle::Create)
			.addCFunction("SetPosition", &Vehicle::SetPosition)
			.addCFunction("GetPosition", &Vehicle::GetPosition)
		.endClass();*/

	// Load scripts
	if (luaL_dofile(stateLua, scriptName) != 0) {
		std::cout << "API.Lua: Error occured when loading " << scriptName << std::endl;
		std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
	}
	else {
		std::cout << "API.Lua: Succesfully loaded " << scriptName << std::endl;
	}
	
	lua_register(stateLua, "PrintMessage", ex_PrintMessage);

	lua_register(stateLua, "CreateVehicle", ex_CreateVehicle);

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