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

	static CVector3 calculateEuler(float qx, float qy, float qz, float qw)
	{
		CVector3 EulerianAngle;

		float qw2 = qw*qw;
		float qx2 = qx*qx;
		float qy2 = qy*qy;
		float qz2 = qz*qz;
		float test = qx*qy + qz*qw;
		if (test > 0.499)
		{
			EulerianAngle.fY = 360 / (6.283185307179586232f * 0.5) * atan2(qx, qw);
			EulerianAngle.fZ = 90;
			EulerianAngle.fX = 0;
			return EulerianAngle;
		}
		if (test < -0.499)
		{
			EulerianAngle.fY = -360 / (6.283185307179586232f * 0.5) * atan2(qx, qw);
			EulerianAngle.fZ = -90;
			EulerianAngle.fX = 0;
			return EulerianAngle;
		}

		float h = atan2(2 * qy*qw - 2 * qx*qz, 1 - 2 * qy2 - 2 * qz2);
		float a = asin(2 * qx*qy + 2 * qz*qw);
		float b = atan2(2 * qx*qw - 2 * qy*qz, 1 - 2 * qx2 - 2 * qz2);
		EulerianAngle.fY = h * 180 / (6.283185307179586232f * 0.5);
		EulerianAngle.fZ = a * 180 / (6.283185307179586232f * 0.5);
		EulerianAngle.fX = b * 180 / (6.283185307179586232f * 0.5);
		return EulerianAngle;
	}
};