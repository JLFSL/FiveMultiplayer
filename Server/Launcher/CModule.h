#pragma once
class CModule
{
private:
	HMODULE m_Module;

public:
	CModule();
	~CModule();

	bool Load(const char *mPath);
	bool Unload();

	void *GetProcedureAddress(const char * mName);
};

