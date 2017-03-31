#pragma once
class CAPI
{
private:
	std::string Module;
	void*		Instance;

	bool		Loaded;

public:
	CAPI();
	~CAPI();

	bool Load();
	bool Unload();

	bool Initialize();
	bool Close();
	bool OnTick();

	void* GetInstance() { return Instance;  }

	std::string ModuleName() { return Module; }
	void SetModuleName(std::string _module) { Module = _module; }

	bool IsLoaded() { return Loaded; }
};
extern std::vector<CAPI> g_ApiModules;