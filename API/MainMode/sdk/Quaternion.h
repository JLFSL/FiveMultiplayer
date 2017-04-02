/// <summary>
/// Quaternion class
/// By Ethem Kurt (BigETI)
/// </summary>
class Quaternion
{
private:
	/// <summary>
	/// Vector part
	/// </summary>
	CVector3 vp;

	/// <summary>
	/// Scalar part
	/// </summary>
	float_t w;

public:

	/// <summary>
	/// Identity quaternion
	/// </summary>
	static const Quaternion identity;

	/// <summary>
	/// Default constructor
	/// </summary>
	Quaternion();

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="q">Quaternion to assign from</param>
	Quaternion(const Quaternion &q);

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_vp">Vector part</param>
	/// <param name="_w">W component</param>
	Quaternion(const CVector3 &_vp, float_t _w);

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="x">Vector part X</param>
	/// <param name="y">Vector part Y</param>
	/// <param name="z">Vector part Z</param>
	/// <param name="_w">W component</param>
	Quaternion(float_t x, float_t y, float_t z, float_t _w);

	/// <summary>
	/// Destructor
	/// </summary>
	~Quaternion();

	/// <summary>
	/// Create quaternion from euler angles (radians)
	/// </summary>
	/// <param name="euler">Euler angles (radians)</param>
	/// <returns>Quaternion</returns>
	static Quaternion FromEuler(const CVector3 &euler);

	/// <summary>
	/// Create quaternion from euler angles (degrees)
	/// </summary>
	/// <param name="euler_degrees">Euler angles (degrees)</param>
	/// <returns>Quaternion</returns>
	static Quaternion FromEulerDegrees(const CVector3 &euler_degrees);

	/// <summary>
	/// Assign quaternion
	/// </summary>
	/// <param name="q">Quaternion to assign from</param>
	/// <returns>Itself</returns>
	Quaternion &operator=(const Quaternion &q);

	/// <summary>
	/// Multiply quaternion (This is used to stack rotations)
	/// </summary>
	/// <param name="q">Quaternion to multiply with and assign</param>
	/// <returns>Itself</returns>
	Quaternion &operator*=(const Quaternion &q);

	/// <summary>
	/// Divide quaternion (This is used to revert rotation stacks)
	/// </summary>
	/// <param name="q">Quaternion to divide with and assign</param>
	/// <returns>Itself</returns>
	Quaternion &operator/=(const Quaternion &q);

	/// <summary>
	/// Multiply quaternion (This is used to stack rotations)
	/// </summary>
	/// <param name="q">Quaternion to multiply with</param>
	/// <returns>Result quaternion</returns>
	Quaternion &operator*(const Quaternion &q);

	/// <summary>
	/// Divide quaternion (This is used to revert rotation stacks)
	/// </summary>
	/// <param name="q">Quaternion to divide with</param>
	/// <returns>Result quaternion</returns>
	Quaternion &operator/(const Quaternion &q);

	/// <summary>
	/// Conjugate quaternion
	/// </summary>
	void Conjugate();

	/// <summary>
	/// Create conjugate quaternion
	/// </summary>
	/// <returns>Conjugated quaternion</returns>
	Quaternion CreateConjugated();

	/// <summary>
	/// Negate quaternion
	/// </summary>
	void Negate();

	/// <summary>
	/// Create negated quaternion
	/// </summary>
	/// <returns>Negated quaternion</returns>
	Quaternion CreateNegated();

	/// <summary>
	/// Inverse quaternion
	/// </summary>
	void Inverse();

	/// <summary>
	/// Create inversed quaternion
	/// </summary>
	/// <returns>Inversed quaternion</returns>
	Quaternion CreateInversed();

	/// <summary>
	/// Get euler angles (radians)
	/// </summary>
	CVector3 ToEuler();

	/// <summary>
	/// Get euler angles (degrees)
	/// </summary>
	CVector3 ToEulerDegrees();
};