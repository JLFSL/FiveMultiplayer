#pragma once
class CAPI
{
private:
	char *Module;
	HMODULE Instance;

public:
	CAPI();
	~CAPI();

	bool Load(LPCSTR Filename);
	bool Unload();

	bool Initialize();
	bool Close();

	char *ModuleName() { return Module; };
};

