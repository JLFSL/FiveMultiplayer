class CVector4
{
public:
	float x;
	float y;
	float z;
	float w;

	CVector4()
	{
		x = y = z = w = 0.0f;
	}

	CVector4(float _x, float _y, float _z, float _w)
	{
		x = _x; y = _y; z = _z; w = _w;
	}

	bool IsEmpty() const
	{
		return (x == 0 && y == 0 && z == 0 && w == 0);
	}

	CVector4 operator+ (const CVector4& vecRight) const
	{
		return CVector4(x + vecRight.x, y + vecRight.y, z + vecRight.z, w + vecRight.w);
	}
};