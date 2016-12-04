#pragma once

#ifdef __DEBUG
#define DEBUGOUT( X, ... ) Logger::Debug( X, __VA_ARGS__ )
#else
#define DEBUGOUT( X, ... )
#endif

#if _DEBUG
#define DEBUGMSG Logger::Debug
#else
#define DEBUGMSG //
#endif

class Logger
{
public:
	static void Init(HMODULE hModule);
#ifdef _DEBUG
	static void Debug(const char* fmt, ...);
#endif
	static void Msg(const char* fmt, ...);
	static void Error(const char* fmt, ...);
	static void Fatal(const char* fmt, ...);
};