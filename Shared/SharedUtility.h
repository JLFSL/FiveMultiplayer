#include <cstddef>

template <typename T, std::size_t N>
inline
std::size_t SizeOfArray(const T(&)[N])
{
	return N;
}

class CString 
{
public:
	static const std::wstring utf8ToUtf16(const std::string& str)
	{
		std::wostringstream wstm;
		wstm.imbue(std::locale("en_US.UTF-8"));
		const std::ctype<wchar_t>& ctfacet =
			std::use_facet< std::ctype<wchar_t> >(wstm.getloc());
		for (size_t i = 0; i<str.size(); ++i)
			wstm << ctfacet.widen(str[i]);
		return wstm.str();
	}

	static const std::string utf16ToUtf8(const std::wstring& wstr)
	{
		std::ostringstream stm;
		stm.imbue(std::locale("en_US"));
		const std::ctype<char>& ctfacet =
			std::use_facet< std::ctype<char> >(stm.getloc());
		for (size_t i = 0; i<wstr.size(); ++i)
			stm << ctfacet.narrow(wstr[i], 0);
		return stm.str();
	}
};