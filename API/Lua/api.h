#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport)
#endif
#else
#define DLL_PUBLIC 
#endif

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC_I __attribute__ ((dllimport))
#else
#define DLL_PUBLIC_I __declspec(dllimport)
#endif
#else
#define DLL_PUBLIC_I 
#endif

#pragma region API::Server Functions
//static int ex_PrintMessage(lua_State* state);
#pragma endregion
#pragma region API::Entity Functions
//static int ex_Destroy(lua_State* state);
//static int ex_GetPosition(lua_State* state);
#pragma endregion