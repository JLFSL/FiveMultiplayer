#pragma once
class CAPI
{
private:
	string Module;
	void* Instance;

public:
	CAPI();
	~CAPI();

	bool Load(const char *Filename);
	bool Unload();

	bool Initialize();
	bool Close();
	bool OnTick();

	string ModuleName() { return Module; };
};

