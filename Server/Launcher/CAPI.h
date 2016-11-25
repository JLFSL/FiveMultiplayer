#pragma once
class CAPI
{
private:
	LPCSTR Module;

	HINSTANCE Instance;
	typedef VOID(CALLBACK* LPFN_DHFDLL)();

public:
	CAPI();
	~CAPI();

	bool Load(LPCSTR Filename);
	bool Unload();

	bool Initialize();
	bool Close();

	LPCSTR ModuleName() { return Module; };
};

