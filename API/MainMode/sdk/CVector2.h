/// <summary>
/// CVector2 class
/// By Ethem Kurt (BigETI)
/// </summary>
class CVector2
{
public:
	/// <summary>
	/// X component
	/// </summary>
	float_t x;

	/// <summary>
	/// Y component
	/// </summary>
	float_t y;

	/// <summary>
	/// Unit vector
	/// </summary>
	static const CVector2 unit;

	/// <summary>
	/// Null vector
	/// </summary>
	static const CVector2 null;

	/// <summary>
	/// Up vector
	/// </summary>
	static const CVector2 up;

	/// <summary>
	/// Down vector
	/// </summary>
	static const CVector2 down;

	/// <summary>
	/// Left vector
	/// </summary>
	static const CVector2 left;

	/// <summary>
	/// Right vector
	/// </summary>
	static const CVector2 right;

	/// <summary>
	/// Default constructor
	/// </summary>
	CVector2();

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="v">Vector to assign from</param>
	CVector2(const CVector2 &v);

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_x">X component</param>
	/// <param name="_y">Y component</param>
	CVector2(float_t _x, float_t _y);

	/// <summary>
	/// Destructor
	/// </summary>
	~CVector2();
	
	/// <summary>
	/// Assign vector
	/// </summary>
	/// <param name="v">Vector to assign from</param>
	/// <returns>Itself</returns>
	CVector2 &operator=(const CVector2 &v);

	/// <summary>
	/// Add Vector
	/// </summary>
	/// <param name="v">Add from vector and assign result</param>
	/// <returns>Itself</returns>
	CVector2 &operator+=(const CVector2 &v);

	/// <summary>
	/// Subtract vector
	/// </summary>
	/// <param name="v">Add from vector and assign result</param>
	/// <returns>Itself</returns>
	CVector2 &operator-=(const CVector2 &v);

	/// <summary>
	/// Multiply vector
	/// </summary>
	/// <param name="s">Scalar to multiply with and assign result</param>
	/// <returns>Itself</returns>
	CVector2 &operator*=(float_t s);

	/// <summary>
	/// Divide vector
	/// </summary>
	/// <param name="s">Scalar to divide with and assign result</param>
	/// <returns>Itself</returns>
	CVector2 &operator/=(float_t s);

	/// <summary>
	/// Add vector
	/// </summary>
	/// <param name="v">Vector to add</param>
	/// <returns>Result vector</returns>
	CVector2 operator+(const CVector2 &v);

	/// <summary>
	/// Subtract vector
	/// </summary>
	/// <param name="v">Vector to subtract</param>
	/// <returns>Result vector</returns>
	CVector2 operator-(const CVector2 &v);

	/// <summary>
	/// Vector dot product
	/// </summary>
	/// <param name="v">Vector for dot product</param>
	/// <returns>Dot product</returns>
	float_t operator*(const CVector2 &v);

	/// <summary>
	/// Add vector
	/// </summary>
	/// <param name="s">Scalar to multiply with</param>
	/// <returns>Result vector</returns>
	CVector2 operator*(float_t s);

	/// <summary>
	/// Divide vector
	/// </summary>
	/// <param name="s">Scalar to divide with</param>
	/// <returns>Result vector</returns>
	CVector2 operator/(float_t s);

	/// <summary>
	/// Is vector null
	/// </summary>
	/// <returns>If null then true, otherwise false</returns>
	bool IsNull();

	/// <summary>
	/// Get magnitude of vector squared (faster than CVector2::Magnitude())
	/// </summary>
	/// <returns>Magnitude squared</returns>
	float_t MagnitudeSquared();

	/// <summary>
	/// Get magnitude of vector (slower than CVector2::MagnitudeSquared())
	/// </summary>
	/// <returns>Magnitude</returns>
	float_t Magnitude();

	/// <summary>
	/// Set magnitude of vector
	/// </summary>
	/// <param name="m">Magnitude</param>
	void SetMagnitude(float_t m);

	/// <summary>
	/// Create vector with magnitude
	/// </summary>
	/// <param name="m">Magnitude</param>
	/// <returns>Vector with set magnitude</returns>
	CVector2 WithMagnitude(float_t m);

	/// <summary>
	/// Is point in range
	/// </summary>
	/// <param name="p">Point to check</param>
	/// <param name="range">Range for check</param>
	/// <returns>If is point in range true, otherwise false</returns>
	bool IsInRange(const CVector2 &p, float_t range);

	/// <summary>
	/// Get square angled vector
	/// </summary>
	/// <returns>Square angeled vector</returns>
	CVector2 SquareAngle();

	/// <summary>
	/// Get angle between two vectors (radians)
	/// </summary>
	/// <param name="v">Vector to get angle between</param>
	/// <returns>Angle between 2 vectors (radians)</returns>
	float_t GetAngle(const CVector2 &v);

	/// <summary>
	/// Get angle between two vectors (degrees)
	/// </summary>
	/// <param name="v">Vector to get angle between</param>
	/// <returns>Angle between 2 vectors (degrees)</returns>
	float_t GetAngleDegrees(const CVector2 &v);

	/// <summary>
	/// Rotate vector (radians)
	/// </summary>
	/// <param name="radians">Radians to rotate</param>
	void Rotate(float_t radians);

	/// <summary>
	/// Create rotated vector (radians)
	/// </summary>
	/// <param name="radians">Radians to rotate</param>
	/// <returns>Rotated vector</returns>
	CVector2 CreateRotated(float_t radians);

	/// <summary>
	/// Rotate vector (degrees)
	/// </summary>
	/// <param name="degrees">Degrees to rotate</param>
	void RotateDegrees(float_t degrees);

	/// <summary>
	/// Create rotated vector (degrees)
	/// </summary>
	/// <param name="degrees">Degrees to rotate</param>
	/// <returns>Rotated vector</returns>
	CVector2 CreateRotatedDegrees(float_t degrees);

	/// <summary>
	/// Negate vector
	/// </summary>
	void Negate();

	/// <summary>
	/// Create negated vector
	/// </summary>
	/// <returns>Negated vector</returns>
	CVector2 CreateNegated();
	
};