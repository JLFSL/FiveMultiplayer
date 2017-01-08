#include <math.h>

class CVector3
{
public:
	float fX;
	float fY;
	float fZ;

	CVector3()
	{
		fX = fY = fZ = 0.0f;
	}

	CVector3(float _fX, float _fY, float _fZ)
	{
		fX = _fX; fY = _fY; fZ = _fZ;
	}

	bool IsEmpty() const
	{
		return (fX == 0 && fY == 0 && fZ == 0);
	}

	bool SameAs(CVector3 vec) const
	{
		CVector3 thisVec = { fX, fY, fZ };
		if (thisVec == vec)
			return true;
		return false;
	}

	float Length() const
	{
		return sqrt((fX * fX) + (fY * fY) + (fZ * fZ));
	}

	bool operator== (CVector3 vec) const
	{
		if (fX == vec.fX && fY == vec.fY && fZ == vec.fZ)
			return true;
		return false;
	}

	bool operator!= (CVector3 vec) const
	{
		if (fX != vec.fX && fY != vec.fY && fZ != vec.fZ)
			return true;
		return false;
	}

	CVector3 operator+ (const CVector3& vecRight) const
	{
		return CVector3(fX + vecRight.fX, fY + vecRight.fY, fZ + vecRight.fZ);
	}

	CVector3 operator+ (float fRight) const
	{
		return CVector3(fX + fRight, fY + fRight, fZ + fRight);
	}

	CVector3 operator- (const CVector3& vecRight) const
	{
		return CVector3(fX - vecRight.fX, fY - vecRight.fY, fZ - vecRight.fZ);
	}

	CVector3 operator- (float fRight) const
	{
		return CVector3(fX - fRight, fY - fRight, fZ - fRight);
	}

	CVector3 operator* (const CVector3& vecRight) const
	{
		return CVector3(fX * vecRight.fX, fY * vecRight.fY, fZ * vecRight.fZ);
	}

	CVector3 operator* (float fRight) const
	{
		return CVector3(fX * fRight, fY * fRight, fZ * fRight);
	}

	CVector3 operator/ (const CVector3& vecRight) const
	{
		return CVector3(fX / vecRight.fX, fY / vecRight.fY, fZ / vecRight.fZ);
	}

	CVector3 operator/ (float fRight) const
	{
		return CVector3(fX / fRight, fY / fRight, fZ / fRight);
	}

	CVector3 operator - () const
	{
		return CVector3(-fX, -fY, -fZ);
	}

	void operator += (float fRight)
	{
		fX += fRight;
		fY += fRight;
		fZ += fRight;
	}

	void operator -= (float fRight)
	{
		fX -= fRight;
		fY -= fRight;
		fZ -= fRight;
	}

	void operator *= (float fRight)
	{
		fX *= fRight;
		fY *= fRight;
		fZ *= fRight;
	}

	void operator /= (float fRight)
	{
		fX /= fRight;
		fY /= fRight;
		fZ /= fRight;
	}
};