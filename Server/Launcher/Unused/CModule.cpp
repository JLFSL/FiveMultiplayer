#include "stdafx.h"

CModule::CModule()
{
	m_Module = NULL;

	cout << "CModule Constructed" << endl;
}


CModule::~CModule()
{
	if (m_Module)
		Unload();

	cout << "CModule Deconstructed" << endl;
}

bool CModule::Load(const char * mPath)
{
	if (!m_Module)
	{
#ifdef _WIN32
		m_Module = LoadLibraryA(mPath);
#else
		m_Module = dlopen(mPath, RTLD_LAZY);
#endif
		if (!m_Module)
		{
			cout << "An error has occured while loading " << mPath << endl;
			return false;
		}
		cout << "Successfully loaded " << mPath << endl;
		return true;
	}
	return false;
}

bool CModule::Unload()
{
	if (!m_Module)
	{
		bool Error = false;

#ifdef _WIN32
		if (!FreeLibrary(m_Module)) {
			cout << "An error has occured while unloading CModule." << endl;
			Error = true;
			return false;
		}
#else
		
		if (dlclose(m_Module) != 0) {
			cout << "An error has occured while unloading CModule." << endl;
			Error = true;
			return false;
		}
#endif
		if (!Error) {
			m_Module = NULL;
			cout << "Successfully unloaded CModule" << endl;
			return true;
		}
	}
	return false;
}

void *CModule::GetProcedureAddress(const char *mName)
{
	if (!m_Module)
	{
		cout << "Tried to load " << mName << " while CModule isn't initialized." << endl;
		return nullptr;
	}
	else
	{
		void *pProcedureAddress;
#ifdef WIN32
		pProcedureAddress = (void *)GetProcAddress(m_Module, mName);
		if (!pProcedureAddress)
			cout << "An error has occured while retrieving Procedure Address of " << mName << endl;
#else
		pProcedureAddress = dlsym(m_pLibrary, szProcedureName);
		if (!pProcedureAddress)
			cout << "An error has occured while retrieving Procedure Address of " << mName << endl;
#endif
		return pProcedureAddress;
	}
	return nullptr;
}
