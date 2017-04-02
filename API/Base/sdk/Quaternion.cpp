/**
File:
	Quaternion.cpp

Author:
	Ethem Kurt (BigETI)
*/

#include "../stdafx.h"

const Quaternion Quaternion::identity(CVector3::null, 1.0f);

Quaternion::Quaternion() : vp(CVector3::null), w(1.0f)
{
	//
}

Quaternion::Quaternion(const Quaternion & q) : vp(q.vp), w(q.w)
{
	//
}

Quaternion::Quaternion(const CVector3 & _vp, float_t _w) : vp(_vp), w(_w)
{
	//
}

Quaternion::Quaternion(float_t x, float_t y, float_t z, float_t _w) : vp(x, y, z), w(_w)
{
	//
}

Quaternion::~Quaternion()
{
	//
}

Quaternion Quaternion::FromEuler(const CVector3 & euler)
{
	float_t xh = euler.x * 0.5f,
		yh = euler.y * 0.5f,
		zh = euler.z * 0.5f,
		sxh = sin(xh), cxh = cos(xh),
		syh = sin(yh), cyh = cos(yh),
		szh = sin(zh), czh = cos(zh);
	return Quaternion(((czh * syh) * cxh) + ((szh * cyh) * sxh), ((szh * cyh) * cxh) - ((czh * syh) * sxh), ((czh * cyh) * sxh) - ((szh * syh) * cxh), ((czh * cyh) * cxh) + ((szh * syh) * sxh));
}

Quaternion Quaternion::FromEulerDegrees(const CVector3 & euler_degrees)
{
	CVector3 e(euler_degrees);
	e *= PI;
	e /= 180.0f;
	return FromEuler(e);
}

Quaternion & Quaternion::operator=(const Quaternion & q)
{
	vp = q.vp;
	w = q.w;
}

Quaternion & Quaternion::operator*=(const Quaternion & q)
{
	Quaternion t(((vp.x * q.w) + (q.vp.x * w)) + ((vp.y * q.vp.z) - (vp.z * q.vp.y)),
		((vp.y * q.w) + (q.vp.y * w)) + ((vp.z * q.vp.x) - (vp.x * q.vp.z)),
		((vp.z * q.w) + (q.vp.z * w)) + ((vp.x * q.vp.y) - (vp.y * q.vp.x)),
		(w * q.w) - (((vp.x * q.vp.x) + (vp.y * q.vp.y)) + (vp.z * q.vp.z)));
	(*this) = t;
	return (*this);
}

Quaternion & Quaternion::operator/=(const Quaternion & q)
{
	float_t _1_ms = 1.0f / ((((q.vp.x * q.vp.x) + (q.vp.y * q.vp.y)) + (q.vp.z * q.vp.z)) + (q.w * q.w));
	CVector3 _1_ms_nqvp(-q.vp.x * _1_ms, -q.vp.y * _1_ms, -q.vp.z * _1_ms);
	float_t _1_ms_w = q.w * _1_ms;
	Quaternion t(((vp.x * _1_ms_w) + (_1_ms_nqvp.x * w)) + ((vp.y * _1_ms_nqvp.z) - (vp.z * _1_ms_nqvp.y)),
		((vp.y * _1_ms_w) + (_1_ms_nqvp.y * w)) + ((vp.z * _1_ms_nqvp.x) - (vp.x * _1_ms_nqvp.z)),
		((vp.z * _1_ms_w) + (_1_ms_nqvp.z * w)) + ((vp.x * _1_ms_nqvp.y) - (vp.y * _1_ms_nqvp.x)),
		(w * _1_ms_w) - (((vp.x * _1_ms_nqvp.x) + (vp.y * _1_ms_nqvp.y)) + (vp.z * _1_ms_nqvp.z)));
	(*this) = t;
	return (*this);

}

Quaternion & Quaternion::operator*(const Quaternion & q)
{
	return Quaternion(*this) * q;
}

Quaternion & Quaternion::operator/(const Quaternion & q)
{
	return Quaternion(*this) / q;
}

void Quaternion::Conjugate()
{
	vp.Negate();
}

Quaternion Quaternion::CreateConjugated()
{
	Quaternion ret(*this);
	ret.Conjugate();
	return ret;
}

void Quaternion::Negate()
{
	vp.Negate();
	w = -w;
}

Quaternion Quaternion::CreateNegated()
{
	Quaternion ret(*this);
	ret.Negate();
	return ret;
}

void Quaternion::Inverse()
{
	float_t _1_ms = 1.0f / (vp.MagnitudeSquared() + (w * w));
	Quaternion t(-vp.x * _1_ms,
		-vp.y * _1_ms,
		-vp.z * _1_ms,
		w * _1_ms);
	(*this) = t;
}

Quaternion Quaternion::CreateInversed()
{
	Quaternion ret(*this);
	ret.Inverse();
	return ret;
}

CVector3 Quaternion::ToEuler()
{
	float_t ys = vp.y * vp.y,
		ysin = 2.0f * ((w * vp.y) - (vp.z * vp.x));
	ysin = ysin > 1.0f ? 1.0f : (ysin < -1.0f ? -1.0f : ysin);
	return CVector3(atan2(2.0f * ((w * vp.x) + (vp.y * vp.z)), 1.0f - (2.0f * ((vp.x * vp.x) + ys))),
		asin(ysin),
		atan2(2.0f * (w * vp.z + vp.x * vp.y), 1.0f - (2.0f * (ys + vp.z * vp.z))));
}

CVector3 Quaternion::ToEulerDegrees()
{
	return (ToEuler() * 180.0f) / PI;
}
