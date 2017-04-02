/**
File:
	Plane.cpp

Author:
	Ethem Kurt (BigETI)
*/

#include "../stdafx.h"

Plane::Plane() : xv(CVector3::up), yv(CVector3::right)
{
	//
}

Plane::Plane(const Plane & p) : xv(p.xv), yv(p.yv)
{
	//
}

Plane::Plane(const CVector3 &_xv, const CVector3 &_yv) : xv(_xv), yv(_yv)
{
	//
}

Plane::Plane(float_t xvx, float_t xvy, float_t xvz, float_t yvx, float_t yvy, float_t yvz) : xv(xvx, xvy, xvz), yv(yvx, yvy, yvz)
{
	//
}

Plane::~Plane()
{
	//
}

Plane & Plane::operator=(const Plane & p)
{
	xv = p.xv;
	yv = p.yv;
}

CVector3 Plane::GetPoint(const CVector2 & p)
{
	return (xv * p.x) + (yv * p.y);
}

CVector3 Plane::GetPoint(float_t x, float_t y)
{
	return GetPoint(CVector2(x, y));
}

CVector3 Plane::GetNormal()
{
	return xv.CrossProduct(yv);
}