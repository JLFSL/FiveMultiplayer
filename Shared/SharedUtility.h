

template <typename T, size_t N>
inline
size_t SizeOfArray(const T(&)[N])
{
	return N;
}