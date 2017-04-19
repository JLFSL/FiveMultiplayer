#include "stdafx.h" 

INIWriter::INIWriter(const std::string& filename)
{
	 memset(m_szFileName, 0x00, 255);
	 memcpy(m_szFileName, filename.c_str(), strlen(filename.c_str()));
}

void INIWriter::WriteInteger(char* szSection, char* szKey, int iValue)
{
	 char szValue[255];
	 sprintf(szValue, "%d", iValue);
	 WritePrivateProfileStringA(szSection,  szKey, szValue, m_szFileName); 
}

void INIWriter::WriteFloat(char* szSection, char* szKey, float fltValue)
{
	 char szValue[255];
	 sprintf(szValue, "%f", fltValue);
	 WritePrivateProfileStringA(szSection,  szKey, szValue, m_szFileName);
}

void INIWriter::WriteBoolean(char* szSection, char* szKey, bool bolValue)
{
	 char szValue[255];
	 sprintf(szValue, "%s", bolValue ? "True" : "False");
	 WritePrivateProfileStringA(szSection,  szKey, szValue, m_szFileName);
}

void INIWriter::WriteString(char* szSection, char* szKey, const std::string& szValue)
{
	WritePrivateProfileStringA(szSection,  szKey, szValue.c_str(), m_szFileName);
}