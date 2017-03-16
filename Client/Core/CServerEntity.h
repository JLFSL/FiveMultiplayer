#pragma once
/*
* The global server entity ids
*/
class CServerEntity
{
public:
	enum Type
	{
		Unknown = -1,
		Player = 0,
		Vehicle = 1,
		Object = 2,
		NPC = 3
	};
private:
	struct Entity
	{
		int Id;
		Type type;
	} Data;

public:
	CServerEntity();
	~CServerEntity() {}

	void Create(const int entity, const Type type);
	void Destroy();

	const int	GetId()			{ return Data.Id; }
	void SetId(const int id)	{ Data.Id = id; }

	const Type GetType()		{ return Data.type; }
	void SetType(Type type);

	const CVector3	GetPosition();
	void	SetPosition(const CVector3 position);

	void	SetQuaternion(const CVector4 quaternion);

	void	SetAssignement(const RakNetGUID guid);

	static const bool	IsValid(const int entity);
	static const		RakNetGUID	GetAssignee(const int entity);
	static void			SetAssignee(const int entity, const RakNetGUID assignee);

	static void			SetPedComponentVariation(const int entity, const int componentid, const int drawableid, const int textureid, const int paletteid);
	static void			SetPedHeadBlend(const int entity, const int shapeFirst, const int shapeSecond, const int shapeThird, const int skinFirst, const int skinSecond, const int skinThird, const float shapeMix, const float skinMix, const float thirdMix);
	static void			SetPedHeadOverlayColor(const int entity, const int overlayid, const int index, const int colorType, const int colorid, const int secondColorid, const float opacity);
	static void			SetPedProp(const int entity, const int componentid, const int drawableid, const int textureid);
	static void			SetPedFaceFeature(const int entity, const int index, const float scale);
};
extern std::vector<CServerEntity> g_Entities;