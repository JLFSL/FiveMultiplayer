#pragma once
class Scripts
{
public:
	Scripts() { };
	~Scripts() { };

	void StopAll();
	void Pulse();

	typedef struct {
		char *name;
	} ScriptInfo;
};

