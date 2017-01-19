#pragma once
class CAPI
{
private:
	std::string Module;
	void*		Instance;

public:
	CAPI();
	~CAPI();

	bool Load(const char *Filename);
	bool Unload();

	bool Initialize();
	bool Close();
	bool OnTick();

	void* GetInstance() { return Instance;  };

	std::string ModuleName() { return Module; };
	void SetModuleName(std::string _module) { Module = _module; };
};
extern std::vector<CAPI> g_ApiModules;