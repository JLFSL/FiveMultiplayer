#include "stdafx.h"

extern "C" {
#include "inc_lua/lualib.h"
#include "inc_lua/lauxlib.h"
#include "inc_lua/lua.h"
}

#include "LuaBridge/LuaBridge.h"
#include "LuaBridge/RefCountedPtr.h"
#include "LuaBridge/RefCountedObject.h"

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
#include "LuaObject.h"
#include "LuaNpc.h"
#include "LuaPlayer.h"
#include "LuaVisual.h"
#include "LuaWorld.h"

char scriptName[64] = "resources//lua//main.lua";
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
			.addCFunction("GetUID", &Vehicle::GetUID)
			.addCFunction("Create", &Vehicle::Create)
			.addCFunction("Destroy", &Vehicle::Destroy)
			.addCFunction("SetPosition", &Vehicle::SetPosition)
			.addCFunction("GetPosition", &Vehicle::GetPosition)
			.addCFunction("GetRotation", &Vehicle::GetRotation)
			.addCFunction("SetRotation", &Vehicle::SetRotation)
			.addCFunction("GetViewDistance", &Vehicle::GetViewDistance)
			.addCFunction("SetViewDistance", &Vehicle::SetViewDistance)
			.addCFunction("SetStandardColor", &Vehicle::SetStandardColor)
			.addCFunction("SetCustomColor", &Vehicle::SetCustomColor)
			.addCFunction("GetNumberPlate", &Vehicle::GetNumberPlate)
			.addCFunction("SetNumberPlate", &Vehicle::SetNumberPlate)
			.addCFunction("GetMod", &Vehicle::GetMod)
			.addCFunction("SetMod", &Vehicle::SetMod)
			.addCFunction("GetEngineState", &Vehicle::GetEngineState)
			.addCFunction("SetEngineState", &Vehicle::SetEngineState)
			.addCFunction("GetDoorsLockState", &Vehicle::GetDoorsLockState)
			.addCFunction("SetDoorsLockState", &Vehicle::SetDoorsLockState)
			.addCFunction("SetDoorsLockStateForPlayer", &Vehicle::SetDoorsLockStateForPlayer)
			.addCFunction("GetModel", &Vehicle::GetModel)
			.addCFunction("GetNumberPlateStyle", &Vehicle::GetNumberPlateStyle)
			.addCFunction("SetNumberPlateStyle", &Vehicle::SetNumberPlateStyle)
			.addCFunction("GetExtra", &Vehicle::GetExtra)
			.addCFunction("SetExtra", &Vehicle::SetExtra)
			.addCFunction("GetEngineHealth", &Vehicle::GetEngineHealth)
			.addCFunction("SetEngineHealth", &Vehicle::SetEngineHealth)
			.addCFunction("GetFuelTankHealth", &Vehicle::GetFuelTankHealth)
			.addCFunction("SetFuelTankHealth", &Vehicle::SetFuelTankHealth)
			.addCFunction("FixDeformation", &Vehicle::FixDeformation)
		.endClass()
		.beginClass <Checkpoint>("Checkpoint")
			.addConstructor <void(*)(void)>()
			.addCFunction("GetUID", &Checkpoint::GetUID)
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
		.endClass()
		.beginClass <Object>("Object")
			.addConstructor <void(*)(void)>()
			.addCFunction("GetUID", &Object::GetUID)
			.addCFunction("Create", &Object::Create)
			.addCFunction("Destroy", &Object::Destroy)
			.addCFunction("SetPosition", &Object::SetPosition)
			.addCFunction("GetPosition", &Object::GetPosition)
			.addCFunction("GetRotation", &Object::GetRotation)
			.addCFunction("SetRotation", &Object::SetRotation)
			.addCFunction("GetViewDistance", &Object::GetViewDistance)
			.addCFunction("SetViewDistance", &Object::SetViewDistance)
			.addCFunction("GetTextureVariation", &Object::GetTextureVariation)
			.addCFunction("SetTextureVariation", &Object::SetTextureVariation)
		.endClass()
		.beginClass <NPC>("NPC")
			.addConstructor <void(*)(void)>()
			.addCFunction("GetUID", &NPC::GetUID)
			.addCFunction("Create", &NPC::Create)
			.addCFunction("Destroy", &NPC::Destroy)
			.addCFunction("SetPosition", &NPC::SetPosition)
			.addCFunction("GetPosition", &NPC::GetPosition)
			.addCFunction("GetRotation", &NPC::GetRotation)
			.addCFunction("SetRotation", &NPC::SetRotation)
			.addCFunction("GetViewDistance", &NPC::GetViewDistance)
			.addCFunction("SetViewDistance", &NPC::SetViewDistance)
			.addCFunction("GetPedComponent", &NPC::GetPedComponent)
			.addCFunction("SetPedComponent", &NPC::SetPedComponent)
			.addCFunction("GetPedHeadBlend", &NPC::GetPedHeadBlend)
			.addCFunction("SetPedHeadBlend", &NPC::SetPedHeadBlend)
			.addCFunction("GetPedHeadOverlay", &NPC::GetPedHeadOverlay)
			.addCFunction("SetPedHeadOverlay", &NPC::SetPedHeadOverlay)
			.addCFunction("GetPedProp", &NPC::GetPedProp)
			.addCFunction("SetPedProp", &NPC::SetPedProp)
			.addCFunction("GetPedFaceFeature", &NPC::GetPedFaceFeature)
			.addCFunction("SetPedFaceFeature", &NPC::SetPedFaceFeature)
		.endClass()
		.beginClass <Player>("Player")
		.addConstructor <void(*)(void)>()
			.addCFunction("GetUID", &Player::GetUID)
			.addCFunction("SetUID", &Player::SetUID)
			.addCFunction("SetPosition", &Player::SetPosition)
			.addCFunction("GetPosition", &Player::GetPosition)
			.addCFunction("GetRotation", &Player::GetRotation)
			.addCFunction("SetRotation", &Player::SetRotation)
			.addCFunction("GetViewDistance", &Player::GetViewDistance)
			.addCFunction("SetViewDistance", &Player::SetViewDistance)
			.addCFunction("GetPedComponent", &Player::GetPedComponent)
			.addCFunction("SetPedComponent", &Player::SetPedComponent)
			.addCFunction("GetPedHeadBlend", &Player::GetPedHeadBlend)
			.addCFunction("SetPedHeadBlend", &Player::SetPedHeadBlend)
			.addCFunction("GetPedHeadOverlay", &Player::GetPedHeadOverlay)
			.addCFunction("SetPedHeadOverlay", &Player::SetPedHeadOverlay)
			.addCFunction("GetPedProp", &Player::GetPedProp)
			.addCFunction("SetPedProp", &Player::SetPedProp)
			.addCFunction("GetPedFaceFeature", &Player::GetPedFaceFeature)
			.addCFunction("SetPedFaceFeature", &Player::SetPedFaceFeature)
			.addCFunction("GetModel", &Player::GetModel)
			.addCFunction("SetModel", &Player::SetModel)
			.addCFunction("ShowMessageAboveMap", &Player::ShowMessageAboveMap)
			.addCFunction("LoadIPL", &Player::LoadIPL)
			.addCFunction("UnloadIPL", &Player::UnloadIPL)
			.addCFunction("SendChatMessage", &Player::SendChatMessage)
			.addCFunction("GetUsername", &Player::GetUsername)
			.addCFunction("ShowCursor", &Player::ShowCursor)
			.addCFunction("LoadURL", &Player::LoadURL)
			.addCFunction("JavaScriptCall", &Player::JavaScriptCall)
			.addCFunction("IsControllable", &Player::IsControllable)
			.addCFunction("SetControllable", &Player::SetControllable)
		.endClass()
		.beginNamespace("visual")
			.addCFunction("ShowMessageAboveMap", Visual::ShowMessageAboveMap)
			.addCFunction("SendChatMessage", Visual::SendChatMessage)
		.endNamespace()
		.beginNamespace("server")
			.addCFunction("PrintMessage", Server::PrintMessage)
		.endNamespace()
		.beginNamespace("world")
			.addCFunction("GetTime", World::GetTime)
			.addCFunction("SetTime", World::SetTime)
			.addCFunction("GetWeather", World::GetWeather)
			.addCFunction("SetWeather", World::SetWeather)
			.addCFunction("LoadIPL", World::LoadIPL)
			.addCFunction("UnloadIPL", World::UnloadIPL)
		.endNamespace();

	// Load scripts
	if (luaL_dofile(stateLua, scriptName) != 0) {
		std::cout << "API.Lua: Error occured when loading " << scriptName << std::endl;
		std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
	}
	else {
		std::cout << "API.Lua: Succesfully loaded " << scriptName << std::endl;
	}

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

extern "C" DLL_PUBLIC bool API_OnPlayerConnecting(const std::string guid, const std::string playername)
{
	int result = 1;

	std::cout << "OnPlayerConnecting() was called." << std::endl;

	int call = lua_getglobal(stateLua, "OnPlayerConnecting");
	if (call != 0)
	{
		lua_pushstring(stateLua, guid.c_str());
		lua_pushstring(stateLua, playername.c_str());

		int error = lua_pcall(stateLua, 2, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnPlayerConnecting" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		result = (int)luaL_optinteger(stateLua, -1, 1);
		lua_pop(stateLua, 1);
	}
	return result;
}

extern "C" DLL_PUBLIC bool API_OnPlayerConnected(int entity)
{
	int result = 1;

	std::cout << "OnPlayerConnected() was called." << std::endl;

	int call = lua_getglobal(stateLua, "OnPlayerConnected");
	if (call != 0)
	{
		lua_pushinteger(stateLua, entity);

		int error = lua_pcall(stateLua, 1, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnPlayerConnected" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		result = (int)luaL_optinteger(stateLua, -1, 1);
		lua_pop(stateLua, 1);
	}
	return result;
}

extern "C" DLL_PUBLIC void API_OnEntityEnterCheckpoint(int checkpoint, int entity)
{
	std::cout << "OnEntityEnterCheckpoint() was called." << std::endl;

	int call = lua_getglobal(stateLua, "OnEntityEnterCheckpoint");
	if (call != 0)
	{
		lua_pushinteger(stateLua, checkpoint);
		lua_pushinteger(stateLua, entity);

		int error = lua_pcall(stateLua, 2, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnEntityEnterCheckpoint" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		lua_pop(stateLua, 1);
	}
}

extern "C" DLL_PUBLIC void API_OnEntityExitCheckpoint(int checkpoint, int entity)
{
	std::cout << "OnEntityExitCheckpoint() was called." << std::endl;

	int call = lua_getglobal(stateLua, "OnEntityExitCheckpoint");
	if (call != 0)
	{
		lua_pushinteger(stateLua, checkpoint);
		lua_pushinteger(stateLua, entity);

		int error = lua_pcall(stateLua, 2, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnEntityExitCheckpoint" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		lua_pop(stateLua, 1);
	}
}

extern "C" DLL_PUBLIC void API_OnPlayerCommand(const int entity, const std::string message)
{
	std::cout << "OnPlayerCommand() was called." << std::endl;

	int call = lua_getglobal(stateLua, "OnPlayerCommand");
	if (call != 0)
	{
		lua_pushinteger(stateLua, entity);
		lua_pushstring(stateLua, message.c_str());

		int error = lua_pcall(stateLua, 2, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnPlayerCommand" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		lua_pop(stateLua, 1);
	}
}

extern "C" DLL_PUBLIC void API_OnPlayerMessage(const int entity, const std::string message)
{
	std::cout << "OnPlayerMessage() was called." << std::endl;

	int call = lua_getglobal(stateLua, "OnPlayerMessage");
	if (call != 0)
	{
		lua_pushinteger(stateLua, entity);
		lua_pushstring(stateLua, message.c_str());

		int error = lua_pcall(stateLua, 2, 1, 0);
		if (error != 0)
		{
			std::cout << "Error occured when executing OnPlayerMessage" << std::endl;
			std::cout << "Error: " << lua_tostring(stateLua, -1) << std::endl;
		}

		lua_pop(stateLua, 1);
	}
}
#pragma endregion