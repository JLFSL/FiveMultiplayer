#pragma once

class World
{
	static bool WorldToScreenRel(Vector3 worldCoords, Vector2 screenCoords);
	static Vector3 ScreenRelToWorld(Vector3 camPos, Vector3 camRot, Vector2 coord);
	static Vector3 RotationToDirection(Vector3 rotation);
	static Vector3 DirectionToRotation(Vector3 direction);
};