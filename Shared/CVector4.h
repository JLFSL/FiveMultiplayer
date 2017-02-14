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

		float h = y * (6.283185307179586232f * 0.5) / 360;
		float a = z * (6.283185307179586232f * 0.5) / 360;
		float b = x * (6.283185307179586232f * 0.5) / 360;
		float c1 = cos(h);
		float c2 = cos(a);
		float c3 = cos(b);
		float s1 = sin(h);
		float s2 = sin(a);
		float s3 = sin(b);
		quaternion.fW = (c1*c2*c3 - s1*s2*s3) * 100000 / 100000;
		quaternion.fX = (s1*s2*c3 + c1*c2*s3) * 100000 / 100000;
		quaternion.fY = (s1*c2*c3 + c1*s2*s3) * 100000 / 100000;
		quaternion.fZ = (c1*s2*c3 - s1*c2*s3) * 100000 / 100000;

		return quaternion;
	}
};