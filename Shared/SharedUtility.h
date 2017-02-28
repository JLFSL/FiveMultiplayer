#include <cstddef>

template <typename T, std::size_t N>
inline
std::size_t SizeOfArray(const T(&)[N])
{
	return N;
}
