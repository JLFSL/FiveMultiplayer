#pragma once
class Scripts
{
public:
	static void StopAll();
	static void Pulse();

	typedef struct {
		char *name;
	} ScriptInfo;
};

