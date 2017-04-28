/// <summary>
/// Plane class
/// By Ethem Kurt (BigETI)
/// </summary>
class Plane
{
public:

	/// <summary>
	/// X axis vector component
	/// </summary>
	CVector3 xv;

	/// <summary>
	/// Y axis vector component
	/// </summary>
	CVector3 yv;

	/// <summary>
	/// Constructor
	/// </summary>
	Plane();

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="p">Plane to assign from</param>
	Plane(const Plane &p);

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_vx">X axis vector component</param>
	/// <param name="_vy">Y axis vector component</param>
	Plane(const CVector3 &_xv, const CVector3 &_yv);

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="xvx">X axis vector X component</param>
	/// <param name="xvy">X axis vector Y component</param>
	/// <param name="xvz">X axis vector Z component</param>
	/// <param name="yvx">Y axis vector X component</param>
	/// <param name="yvy">Y axis vector Y component</param>
	/// <param name="yvz">Y axis vector Z component</param>
	Plane(float_t xvx, float_t xvy, float_t xvz, float_t yvx, float_t yvy, float_t yvz);

	/// <summary>
	/// Destructor
	/// </summary>
	~Plane();

	/// <summary>
	/// Assign plane
	/// </summary>
	/// <param name="p">Plane to assign from</param>
	/// <returns>Itself</returns>
	Plane &operator=(const Plane &p);

	/// <summary>
	/// Get point in space from plane X and Y coordinate
	/// This function is not designed for projecting vectors
	/// </summary>
	/// <param name="p">Point on plane</param>
	/// <returns>Point in 3D space</returns>
	CVector3 GetPoint(const CVector2 &p);

	/// <summary>
	/// Get point in space from plane X and Y coordinate
	/// This function is not designed for projecting vectors
	/// </summary>
	/// <param name="x">X axis</param>
	/// <param name="y">Y axis</param>
	/// <returns>Point in 3D space</returns>
	CVector3 GetPoint(float_t x, float_t y);

	/// <summary>
	/// Get plane normal vector
	/// </summary>
	/// <returns>Plane normal vector</returns>
	CVector3 GetNormal();
};