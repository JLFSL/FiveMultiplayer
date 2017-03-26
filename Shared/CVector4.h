#include <math.h>

/*class CVector4
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

	CVector4 operator+ (float fRight) const
	{
		return CVector4(fX + fRight, fY + fRight, fZ + fRight, fW + fRight);
	}

	CVector4 operator- (const CVector4& vecRight) const
	{
		return CVector4(fX - vecRight.fX, fY - vecRight.fY, fZ - vecRight.fZ, fW - vecRight.fW);
	}

	CVector4 operator- (float fRight) const
	{
		return CVector4(fX - fRight, fY - fRight, fZ - fRight, fW - fRight);
	}

	CVector4 operator* (const CVector4& vecRight) const
	{
		return CVector4(fX * vecRight.fX, fY * vecRight.fY, fZ * vecRight.fZ, fW * vecRight.fW);
	}

	CVector4 operator* (float fRight) const
	{
		return CVector4(fX * fRight, fY * fRight, fZ * fRight, fW * fRight);
	}

	CVector4 operator/ (const CVector4& vecRight) const
	{
		return CVector4(fX / vecRight.fX, fY / vecRight.fY, fZ / vecRight.fZ, fW / vecRight.fW);
	}

	CVector4 operator/ (float fRight) const
	{
		return CVector4(fX / fRight, fY / fRight, fZ / fRight, fW / fRight);
	}

	CVector4 operator - () const
	{
		return CVector4(-fX, -fY, -fZ, -fW);
	}

	void operator += (float fRight)
	{
		fX += fRight;
		fY += fRight;
		fZ += fRight;
		fW += fRight;
	}

	void operator -= (float fRight)
	{
		fX -= fRight;
		fY -= fRight;
		fZ -= fRight;
		fW -= fRight;
	}

	void operator *= (float fRight)
	{
		fX *= fRight;
		fY *= fRight;
		fZ *= fRight;
		fW *= fRight;
	}

	void operator /= (float fRight)
	{
		fX /= fRight;
		fY /= fRight;
		fZ /= fRight;
		fW /= fRight;
	}

	static CVector4 calculateQuaternion(float x, float y, float z)
	{
		CVector4 quaternion;

		double t0 = std::cos(z * 0.5);
		double t1 = std::sin(z * 0.5);
		double t2 = std::cos(x * 0.5);
		double t3 = std::sin(x * 0.5);
		double t4 = std::cos(y * 0.5);
		double t5 = std::sin(y * 0.5);

		quaternion.fW = t0 * t2 * t4 + t1 * t3 * t5;
		quaternion.fX = t0 * t3 * t4 - t1 * t2 * t5;
		quaternion.fY = t0 * t2 * t5 + t1 * t3 * t4;
		quaternion.fZ = t1 * t2 * t4 - t0 * t3 * t5;

		return quaternion;
	}
};*/