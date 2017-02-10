#include <cstddef>

template <typename T, std::size_t N>
inline
std::size_t SizeOfArray(const T(&)[N])
{
	return N;
}


/*CVector3 ToEluaAngles(CVector4 q)
{
	//if (q.fW > 1) q.normalise(); // if fW>1 acos and sqrt will produce errors, this cant happen if quaternion is normalised
	
	float angle = 2 * std::acos(q.fW);

	double s = std::sqrt(1 - q.fW*q.fW); // assuming quaternion normalised then w is less than 1, so term always positive.
	if (s < 0.001)
	{ // test to avoid divide by zero, s is always positive due to sqrt
	  // if s close to zero then direction of axis not important
		CVector3 elua;
		elua.fX = q.fX; // if it is important that axis is normalised then replace with x=1; y=z=0;
		elua.fY = q.fY;
		elua.fZ = q.fZ;
		return elua;
	}
	else
	{
		CVector3 elua;
		elua.fX = q.fX / s; // normalise axis
		elua.fY = q.fY / s;
		elua.fZ = q.fZ / s;
		return elua;
	}
}*/