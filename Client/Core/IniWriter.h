#ifndef INIWRITER_H
#define INIWRITER_H
class INIWriter
{
public:
	explicit INIWriter(const std::string& filename);

	void WriteInteger(char* szSection, char* szKey, int iValue);

	void WriteFloat(char* szSection, char* szKey, float fltValue);

	void WriteBoolean(char* szSection, char* szKey, bool bolValue);

	void WriteString(char* szSection, char* szKey, const std::string& szValue);
private:
	char m_szFileName[255];
};
#endif //INIWRITER_H