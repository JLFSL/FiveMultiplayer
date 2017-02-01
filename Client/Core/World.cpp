#include "stdafx.h"

bool World::WorldToScreenRel(Vector3 worldCoords, Vector2 screenCoords)
{
	float screenX, screenY;
	if (!GRAPHICS::_WORLD3D_TO_SCREEN2D( worldCoords.x, worldCoords.y, worldCoords.z, &screenX, &screenY))
	{
		screenCoords = Vector2();
		return false;
	}
	screenCoords = Vector2((screenX - 0.5f) * 2, (screenY - 0.5f) * 2 );
	return true;
}

Vector3 World::ScreenRelToWorld(Vector3 camPos, Vector3 camRot, Vector2 coord)
{
	Vector3 camForward = RotationToDirection(camRot);

	Vector3 rotUp = camRot;
	rotUp.x += 10;

	Vector3 rotDown = camRot;
	rotDown.x += -10;

	Vector3 rotLeft = camRot;
	rotLeft.z += -10;

	Vector3 rotRight = camRot;
	rotRight.z += 10;

	Vector3 camRight = RotationToDirection(rotRight);
	camRight.x = RotationToDirection(rotLeft).x;
	camRight.y = RotationToDirection(rotLeft).y;
	camRight.z = RotationToDirection(rotLeft).z;

	Vector3 camUp = RotationToDirection(rotUp);
	camUp.x = RotationToDirection(rotDown).x;
	camUp.y = RotationToDirection(rotDown).y;
	camUp.z = RotationToDirection(rotDown).z;

	double rollRad = -Math::ConvertDegreesToRadians(camRot.y);

	Vector3 camRightRoll;
	camRightRoll.x = camRight.x * (float)cos(rollRad) - camUp.x * (float)sin(rollRad);
	camRightRoll.y = camRight.y * (float)cos(rollRad) - camUp.y * (float)sin(rollRad);
	camRightRoll.z = camRight.z * (float)cos(rollRad) - camUp.z * (float)sin(rollRad);

	Vector3 camUpRoll;
	camUpRoll.x = camRight.x * (float)sin(rollRad) + camUp.x * (float)cos(rollRad);
	camUpRoll.y = camRight.y * (float)sin(rollRad) + camUp.y * (float)cos(rollRad);
	camUpRoll.z = camRight.z * (float)sin(rollRad) + camUp.z * (float)cos(rollRad);

	Vector3 point3D;
	point3D.x = camPos.x + camForward.x * 10.0f + camRightRoll.x + camUpRoll.x;
	point3D.y = camPos.y + camForward.y * 10.0f + camRightRoll.y + camUpRoll.y;
	point3D.z = camPos.z + camForward.z * 10.0f + camRightRoll.z + camUpRoll.z;

	Vector2 point2D;
	if (!WorldToScreenRel(point3D, point2D))
	{
		Vector3 rel;
		rel.x = camPos.x + camForward.x * 10.0f;
		rel.y = camPos.y + camForward.y * 10.0f;
		rel.z = camPos.z + camForward.z * 10.0f;
		return rel;
	}

	Vector3 point3DZero;
	point3DZero.x = camPos.x + camForward.x * 10.0f;
	point3DZero.y = camPos.y + camForward.y * 10.0f;
	point3DZero.z = camPos.z + camForward.z * 10.0f;

	Vector2 point2DZero;
	if (!WorldToScreenRel(point3DZero, point2DZero))
	{
		Vector3 rel;
		rel.x = camPos.x + camForward.x * 10.0f;
		rel.y = camPos.y + camForward.y * 10.0f;
		rel.z = camPos.z + camForward.z * 10.0f;
		return rel;
	}

	const double eps = 0.001;
	if (abs(point2D.fX - point2DZero.fX) < eps || abs(point2D.fY - point2DZero.fY) < eps)
	{
		Vector3 rel;
		rel.x = camPos.x + camForward.x * 10.0f;
		rel.y = camPos.y + camForward.y * 10.0f;
		rel.z = camPos.z + camForward.z * 10.0f;
		return rel;
	}
	float scaleX = (coord.fX - point2DZero.fX) / (point2D.fX - point2DZero.fX);
	float scaleY = (coord.fY - point2DZero.fY) / (point2D.fY - point2DZero.fY);

	Vector3 point3Dret;
	point3Dret.x = camPos.x + camForward.x * 10.0f + camRightRoll.x * scaleX + camUpRoll.x * scaleY;
	point3Dret.y = camPos.y + camForward.y * 10.0f + camRightRoll.y * scaleX + camUpRoll.y * scaleY;
	point3Dret.z = camPos.z + camForward.z * 10.0f + camRightRoll.z * scaleX + camUpRoll.z * scaleY;

	return point3Dret;
}

Vector3 World::RotationToDirection(Vector3 rotation)
{
	float z = Math::ConvertDegreesToRadians(rotation.z);
	float x = Math::ConvertDegreesToRadians(rotation.x);
	float num = abs(cos(x));

	Vector3 Direction;
	Direction.x = (float)(-sin(z) * num);
	Direction.y = (float)(cos(z) * num);
	Direction.z = (float)sin(x);

	return Direction;
}

Vector3 World::DirectionToRotation(Vector3 direction)
{
	float x = atan2(direction.z, direction.y);
	float y = 0;
	float z = -atan2(direction.x, direction.y);

	Vector3 rot;
	rot.x = Math::ConvertRadiansToDegrees(x);
	rot.y = Math::ConvertRadiansToDegrees(y);
	rot.z = Math::ConvertRadiansToDegrees(z);

	return rot;
}
