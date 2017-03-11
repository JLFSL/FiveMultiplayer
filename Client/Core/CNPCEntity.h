#pragma once

class CNPCEntity
{
private:
	struct GameInfo
	{
		Ped			Npc;
		bool		Created;

		Blip		Blip;
	} Game;


	struct NPCData
	{
		int					Id;

		struct ModelData
		{
			RakString		Model;
			int				Type;
		} Model;

		struct WeaponData
		{
			unsigned long	Weapon;
			bool			Reload;
		} Weapon;

		struct Vehicle
		{
			int			VehicleID;
			int			Seat;
		} Vehicle;

		struct Component
		{
			int drawableid = -1;
			int textureid = -1;
			int paletteid = -1;
		} ModelComponents[12];

		struct HeadBlend
		{
			int shapeFirst = 0;
			int shapeSecond = 0;
			int shapeThird = 0;
			int skinFirst = 0;
			int skinSecond = 0;
			int skinThird = 0;
			float shapeMix = 0;
			float skinMix = 0;
			float thirdMix = 0;
		} ModelHeadBlend;

		struct HeadOverlay
		{
			int index = 0;
			float opacity = 0.0f;
			int colorType = 0;
			int colorID = 0;
			int secondColorID = 0;
		} ModelHeadOverlay[13];

		struct Prop
		{
			int drawableid = 0;
			int textureid = 0;
		} ModelProp[3];

		struct Feature
		{
			float scale = 0.0f;
		} ModelFaceFeature[20];

		float				ForwardSpeed;

		CVector3			Position;
		CVector3			Velocity;
		CVector4			Quaternion;
	} Data;

	struct Network
	{
		std::chrono::time_point<std::chrono::system_clock> LastSyncSent;
		bool				Synchronized;
	} Network;

public:
	static int Amount;

	CNPCEntity();
	~CNPCEntity() {}

	bool Create(const int entity, const RakString model, const CVector3 position, const CVector4 quaternion);
	bool CreateNpc();
	void Destroy();
	void Delete();

	void Pulse();
	void Update(Packet *packet);

	int				GetId() { return Data.Id; }
	void			SetId(const int playerid) { Data.Id = playerid; }

	bool			IsCreated() { return Game.Created; }

	int				GetVehicle() { return Data.Vehicle.VehicleID; }
	int				GetVehicleSeat() { return Data.Vehicle.Seat; }

	CVector3		GetPosition() { return Data.Position; }
	void			SetPosition(const CVector3 position) { Data.Position = position; }

	CVector4		GetQuaternion() { return Data.Quaternion; }
	void			SetQuaternion(const CVector4 quaternion) { Data.Quaternion = quaternion; }

	const std::string GetModel() { return Data.Model.Model.C_String(); }
	void			SetModel(const std::string model) { Data.Model.Model = RakString(model.c_str()); }

	NPCData::Component GetModelComponent(const int index) { return Data.ModelComponents[index]; }
	void			SetModelComponent(const int index, const int drawableid, const int textureid, const int paletteid)
	{
		Data.ModelComponents[index].drawableid = drawableid;
		Data.ModelComponents[index].textureid = textureid;
		Data.ModelComponents[index].paletteid = paletteid;
	}
	NPCData::HeadBlend GetModelHeadBlend() { return Data.ModelHeadBlend; }
	void			SetModelHeadBlend(const int shapeFirst, const float shapeMix, const int shapeSecond, const int shapeThird, const int skinFirst, const float skinMix, const int skinSecond, const int skinThird, const float thirdMix)
	{
		Data.ModelHeadBlend.shapeFirst = shapeFirst;
		Data.ModelHeadBlend.shapeMix = shapeMix;
		Data.ModelHeadBlend.shapeSecond = shapeSecond;
		Data.ModelHeadBlend.shapeThird = shapeThird;
		Data.ModelHeadBlend.skinFirst = skinFirst;
		Data.ModelHeadBlend.skinMix = skinMix;
		Data.ModelHeadBlend.skinSecond = skinSecond;
		Data.ModelHeadBlend.skinThird = skinThird;
		Data.ModelHeadBlend.thirdMix = thirdMix;
	}
	NPCData::HeadOverlay GetModelHeadOverlay(const int index) { return Data.ModelHeadOverlay[index]; }
	void			SetModelHeadOverlay(const int index, const int type, const int colorType, const int colorID, const int secondColorID, const float opacity)
	{
		Data.ModelHeadOverlay[index].index = type;
		Data.ModelHeadOverlay[index].colorType = colorType;
		Data.ModelHeadOverlay[index].colorID = colorID;
		Data.ModelHeadOverlay[index].secondColorID = secondColorID;
		Data.ModelHeadOverlay[index].opacity = opacity;
	}
	NPCData::Prop		GetModelProp(const int index) { return Data.ModelProp[index]; }
	void			SetModelProp(const int index, const int drawableid, const int textureid)
	{
		Data.ModelProp[index].drawableid = drawableid;
		Data.ModelProp[index].textureid = textureid;
	}
	float			GetModelFaceFeature(const int index) { return Data.ModelFaceFeature[index].scale; }
	void			SetModelFaceFeature(const int index, const float scale) { Data.ModelFaceFeature[index].scale = scale; }

	bool			GetSynchronized() { return Network.Synchronized; }

	void			RequestData(RakNetGUID requester);

	NPCData		SetData(NPCData newdata) { Data = newdata; }

	NPCData		GetData() { return Data; }
};
extern std::vector<CNPCEntity> g_Npcs;
