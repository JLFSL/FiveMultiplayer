#pragma once
class CAPI
{
private:
	char *Module;
	void* Instance;

public:
	CAPI();
	~CAPI();

	bool Load(char *Filename);
	bool Unload();

	bool Initialize();
	bool Close();

	char *ModuleName() { return Module; };
};

