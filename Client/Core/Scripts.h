#pragma once
class Scripts
{
public:
	Scripts() { };
	~Scripts() { };

	void StopAll();

	typedef struct {
		char *name;
	} ScriptInfo;
};

