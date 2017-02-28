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

	static float Distance(CVector3 p1, CVector3 p2)
	{
		float xSqr = (p1.fX - p2.fX) * (p1.fX - p2.fX);
		float ySqr = (p1.fY - p2.fY) * (p1.fY - p2.fY);
		float zSqr = (p1.fZ - p2.fZ) * (p1.fZ - p2.fZ);

		float mySqr = xSqr + ySqr + zSqr;

		float myDistance = sqrt(mySqr);
		return myDistance;
	}

	static CVector3 calculateEuler(float qx, float qy, float qz, float qw)
	{
		CVector3 EulerianAngle;

		double ysqr = qy * qy;

		// roll (x-axis rotation)
		double t0 = +2.0 * (qw * qx + qy * qz);
		double t1 = +1.0 - 2.0 * (qx * qx + ysqr);
		EulerianAngle.fX = std::atan2(t0, t1);

		// pitch (y-axis rotation)
		double t2 = +2.0 * (qw * qy - qz * qx);
		t2 = t2 > 1.0 ? 1.0 : t2;
		t2 = t2 < -1.0 ? -1.0 : t2;
		EulerianAngle.fY = std::asin(t2);

		// yaw (z-axis rotation)
		double t3 = +2.0 * (qw * qz + qx * qy);
		double t4 = +1.0 - 2.0 * (ysqr + qz * qz);
		EulerianAngle.fZ = std::atan2(t3, t4);

		return EulerianAngle;
	}
};