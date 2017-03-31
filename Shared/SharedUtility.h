#include <cstddef>

template <typename T, std::size_t N>
inline
std::size_t SizeOfArray(const T(&)[N])
{
	return N;
}

class FString 
{
public:
	static const std::wstring utf8ToUtf16(const std::string& utf8Str)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
		return conv.from_bytes(utf8Str);
	}

	static const std::string utf16ToUtf8(const std::wstring& utf16Str)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
		return conv.to_bytes(utf16Str);
	}
};