#include <math.h>

class CVector4
{
public:
	float fX;
	float fY;
	float fZ;
	float fW;

	CVector4()
	{
		fX = fY = fZ = fW = 0.0f;
	}

	CVector4(float _fX, float _fY, float _fZ, float _fW)
	{
		fX = _fX; fY = _fY; fZ = _fZ; fW = _fW;
	}

	bool IsEmpty() const
	{
		return (fX == 0 && fY == 0 && fZ == 0 && fW == 0);
	}

	CVector4 operator+ (const CVector4& vecRight) const
	{
		return CVector4(fX + vecRight.fX, fY + vecRight.fY, fZ + vecRight.fZ, fW + vecRight.fW);
	}
};