/**
File:
	CVector3.cpp

Author:
	Ethem Kurt (BigETI)
*/

#include "../stdafx.h"

const CVector3 CVector3::unit(1.0f, 1.0f, 1.0f);
const CVector3 CVector3::null(0.0f, 0.0f, 0.0f);
const CVector3 CVector3::up(0.0f, 1.0f, 0.0f);
const CVector3 CVector3::down(0.0f, -1.0f, 0.0f);
const CVector3 CVector3::left(-1.0f, 0.0f, 0.0f);
const CVector3 CVector3::right(1.0f, 0.0f, 0.0f);
const CVector3 CVector3::front(0.0f, 0.0f, 1.0f);
const CVector3 CVector3::back(0.0f, 0.0f, -1.0f);

//atan2(crossproduct.length,scalarproduct)

CVector3::CVector3() : x(0.0f), y(0.0f), z(0.0f)
{
	//
}

CVector3::CVector3(const CVector3 & v) : x(v.x), y(v.y), z(v.z)
{
	//
}

CVector3::CVector3(float_t _x, float_t _y, float_t _z) : x(_x), y(_y), z(_z)
{
	//
}

CVector3::~CVector3()
{
	//
}

CVector3 & CVector3::operator=(const CVector3 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return (*this);
}

CVector3 & CVector3::operator+=(const CVector3 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return (*this);
}

CVector3 & CVector3::operator-=(const CVector3 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return (*this);
}

CVector3 & CVector3::operator*=(float_t s)
{
	x *= s;
	y *= s;
	z *= s;
	return (*this);
}

CVector3 & CVector3::operator/=(float_t s)
{
	if (IS_FLOAT_ZERO(s))
		throw std::overflow_error("Division by zero");
	x /= s;
	y /= s;
	z /= s;
	return (*this);
}

CVector3 CVector3::operator+(const CVector3 & v)
{
	return CVector3(*this) += v;
}

CVector3 CVector3::operator-(const CVector3 & v)
{
	return CVector3(*this) -= v;
}

float_t CVector3::operator*(const CVector3 & v)
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

CVector3 CVector3::operator*(float_t s)
{
	return CVector3(*this) *= s;
}

CVector3 CVector3::operator/(float_t s)
{
	return CVector3(*this) *= s;
}

bool CVector3::IsNull()
{
	return (IS_FLOAT_ZERO(x) && IS_FLOAT_ZERO(y) && IS_FLOAT_ZERO(z));
}

float_t CVector3::MagnitudeSquared()
{
	return (x * x) + (y * y) + (z * z);
}

float_t CVector3::Magnitude()
{
	return SQRT(MagnitudeSquared());
}

void CVector3::SetMagnitude(float_t m)
{
	if (IsNull())
		throw std::overflow_error("Vector is null");
	else
	{
		float_t mag(Magnitude());
		x = (x * m) / mag;
		y = (y * m) / mag;
		z = (z * m) / mag;
	}
}

CVector3 CVector3::WithMagnitude(float_t m)
{
	CVector3 ret(*this);
	ret.SetMagnitude(m);
	return ret;
}

bool CVector3::IsInRange(const CVector3 & p, float_t range)
{
	return MagnitudeSquared() <= (range * range);
}

CVector3 CVector3::CrossProduct(const CVector3 & v)
{
	return CVector3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
}

float_t CVector3::GetAngle(const CVector3 & v)
{
	return atan2(CrossProduct(v).Magnitude(), (*this) * v);
}

float_t CVector3::GetAngleDegrees(const CVector3 & v)
{
	return (GetAngle(v) * 180.0f) / PI;
}

void CVector3::RotateAround(const CVector3 & n, float_t radians)
{
	float_t cr(cos(radians));
	CVector3 u(unit);
	(*this) = CVector3(((*this) * cr) + (u.CrossProduct(*this) * sin(radians)) + u * (u * (*this)) * (1 - cr));
}

CVector3 CVector3::CreateRotatedAround(const CVector3 & n, float_t radians)
{
	CVector3 ret(*this);
	ret.RotateAround(n, radians);
	return ret;
}

void CVector3::RotateAroundDegrees(const CVector3 & n, float_t degrees)
{
	RotateAround(n, (degrees * PI) / 180.0f);
}

CVector3 CVector3::CreateRotatedAroundDegrees(const CVector3 & n, float_t degrees)
{
	CVector3 ret(*this);
	ret.RotateAroundDegrees(n, degrees);
	return ret;
}

void CVector3::Negate()
{
	x = -x;
	y = -y;
	z = -z;
}

CVector3 CVector3::CreateNegated()
{
	CVector3 ret(*this);
	ret.Negate();
	return ret;
}
