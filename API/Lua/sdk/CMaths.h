#define DOUBLE_PI    (M_PI * 2)
#define PI           M_PI
#define HALF_PI      M_PI_2
#define RADS_PER_DEG (PI / 180.0f)
#define DEGS_PER_RAD (180.0f / PI)

#define EULER	M_E
#define EPSILON	std::numeric_limits<float_t>::epsilon()
#define IS_FLOAT_ZERO(_f)	(((_f) <= EPSILON) && ((_f) >= (-EPSILON)))

#ifdef FIVEMP_DOUBLE_PRECISION
#define SQRT(_v) sqrt(_v)
typedef double float_t;
#else
#define SQRT(_v) sqrtf(_v)
typedef float float_t;
#endif

namespace Math
{
	static float WrapAround(float fValue, float fHigh)
	{
		return fValue - (fHigh * floor((float)(fValue / fHigh)));
	}

	static float ConvertRadiansToDegrees(float fRotation)
	{
		return WrapAround((fRotation * 180.0f / PI + 360.0f), 360.0f);
	}

	static CVector3 ConvertRadiansToDegrees(const CVector3 &vecRotation)
	{
		return CVector3(ConvertRadiansToDegrees(vecRotation.x),
			ConvertRadiansToDegrees(vecRotation.y),
			ConvertRadiansToDegrees(vecRotation.z));
	}

	static float ConvertDegreesToRadians(float fRotation)
	{
		return WrapAround((fRotation * PI / 180.0f + 2 * PI), DOUBLE_PI);
	}

	static CVector3 ConvertDegreesToRadians(const CVector3 &vecRotation)
	{
		return CVector3(ConvertDegreesToRadians(vecRotation.x),
			ConvertDegreesToRadians(vecRotation.y),
			ConvertDegreesToRadians(vecRotation.z));
	}

	static float GetOffsetDegrees(float a, float b)
	{
		float c = (b > a) ? b - a : 0.0f - (a - b);

		if (c > 180.0f)
			c = 0.0f - (360.0f - c);
		else if (c <= -180.0f)
			c = (360.0f + c);

		return c;
	}

	static CVector3 GetOffsetDegrees(const CVector3& a, const CVector3& b)
	{
		return CVector3(GetOffsetDegrees(a.x, b.x), GetOffsetDegrees(a.y, b.y), GetOffsetDegrees(a.z, b.z));
	}

template <typename T>
static T Lerp(const T& start, float fAlpha, const T& end)
{
	return (end - start) * fAlpha + start;
}

// Clamps a value between two other values
template<class T>
static T Clamp(const T& min, const T& a, const T& max)
{
	if (a < min)
		return min;

	if (a > max)
		return max;

	return a;
}

// Find the relative position of fPos between fStart and fEnd
static const float Unlerp(const double fStart, const double fPos, const double fEnd)
{
	// Avoid dividing by 0 (results in INF values)
	if (fStart == fEnd) return 1.0f;

	return (float)((fPos - fStart) / (fEnd - fStart));
}

// Find the relative position of fPos between fStart and fEnd
// and clamp it between 0 and 1 avoiding extrapolation
static const float UnlerpClamped(const double fStart, const double fPos, const double fEnd)
{
	return Clamp(0.0f, Unlerp(fStart, fPos, fEnd), 1.0f);
}

// Find the distance between two 2D points
static float GetDistanceBetweenPoints2D(float x, float y, float xx, float yy)
{
	float newx = (xx - x);
	float newy = (yy - y);
	return sqrt(newx * newx + newy * newy);
}

// Find the distance between two 3D points
static float GetDistanceBetweenPoints3D(float x, float y, float z, float xx, float yy, float zz)
{
	float newx = (xx - x);
	float newy = (yy - y);
	float newz = (zz - z);
	return sqrt(newx * newx + newy * newy + newz * newz);
}

// Check if a 2D point is within the specified circle
static bool IsPointInCircle(float circleX, float circleY, float circleDistance, float pointX, float pointY)
{
	float distancebetween = GetDistanceBetweenPoints2D(circleX, circleY, pointX, pointY);

	if (distancebetween < circleDistance)
		return true;

	return false;
}

// Check if a 3D point is within the specified tube
static bool IsPointInTube(float tubeX, float tubeY, float tubeZ, float tubeHeight, float tubeRadius, float pointX, float pointY, float pointZ)
{
	float distancebetween = GetDistanceBetweenPoints2D(tubeX, tubeY, pointX, pointY);

	if (distancebetween < tubeRadius && pointZ < tubeZ + tubeHeight && pointZ >= tubeZ)
		return true;

	return false;
}

// Check if a 3D point is within the specified ball
static bool IsPointInBall(float ballX, float ballY, float ballZ, float ballRadius, float pointX, float pointY, float pointZ)
{
	float distancebetween = GetDistanceBetweenPoints3D(ballX, ballY, ballZ, pointX, pointY, pointZ);

	if (distancebetween < ballRadius)
		return true;

	return false;
}

// Check if a 2D point is within the specified 2D area
static bool IsPointInArea(float areaX, float areaY, float areaX2, float areaY2, float pointX, float pointY)
{
	if (pointX >= areaX && pointX <= areaX2 && pointY >= areaY && pointY <= areaY2)
		return true;

	return false;
}

// Check if a 3D point is within the specified 3D area
static bool IsPointInArea(float fAreaX, float fAreaY, float fAreaZ, float fAreaX2, float fAreaY2, float fAreaZ2, float fPointX, float fPointY, float fPointZ)
{
	if ((fPointX >= fAreaX && fPointX <= fAreaX2) && (fPointY >= fAreaY && fPointY <= fAreaY2) && (fPointZ >= fAreaZ && fPointZ <= fAreaZ2))
		return true;

	return false;
}

// Check if a 3D point is within the specified cuboid
static bool IsPointInCuboid(float areaX, float areaY, float areaZ, float areaX2, float areaY2, float areaZ2, float pointX, float pointY, float pointZ)
{
	if (pointX >= areaX && pointX <= areaX2 && pointY >= areaY && pointY <= areaY2 && pointZ >= areaZ && pointZ <= areaZ2)
		return true;

	return false;
}

// polyX and polyY as arrays
static bool IsPointInPolygon(int nvert, float *polyX, float *polyY, float pointX, float pointY)
{
	bool bValid = false;

	for (int i = 0, j = (nvert - 1); i < nvert; j = i++)
	{
		if (((polyY[i] > pointY) != (polyY[j] > pointY)) && (pointX < (polyX[j] - polyX[i]) * (pointY - polyY[i]) / (polyY[j] - polyY[i]) + polyX[i]))
			bValid = !bValid;
	}

	return bValid;
}
};