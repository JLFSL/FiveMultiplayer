#pragma once

class CPlayerEntity {
private:
	struct PlayerInfo {
		int					Entity;
		int					PlayerID;
		RakString			Name;
	} Information;

	struct PlayerStats {
		int					Score;
	} Statistics;

	struct PlayerData {
		struct PlayerModelData {
			std::wstring	Model;
			int				Type;
		} Model;

		struct PlayerWeaponData {
			unsigned long	Weapon;
			bool			Reload;
		} Weapon;

		struct PlayerVehicle
		{
			int			VehicleID;
			int			Seat;
		} Vehicle;

		struct PlayerComponent
		{
			int drawableid	= -1;
			int textureid	= -1;
			int paletteid	= -1;
		} ModelComponents[12];

		struct PlayerHeadBlend
		{
			int shapeFirst	= 0;
			int shapeSecond = 0;
			int shapeThird	= 0;
			int skinFirst	= 0;
			int skinSecond	= 0;
			int skinThird	= 0;
			float shapeMix	= 0;
			float skinMix	= 0;
			float thirdMix	= 0;
		} ModelHeadBlend;

		struct PlayerHeadOverlay
		{
			int index			= 0;
			float opacity		= 0.0f;
			int colorType		= 0;
			int colorID			= 0;
			int secondColorID	= 0;
		} ModelHeadOverlay[13];

		struct PlayerProp
		{
			int drawableid	= 0;
			int textureid	= 0;
		} ModelProp[3];

		struct PlayerFeature
		{
			float scale = 0.0f;
		} ModelFaceFeature[20];

		float				ForwardSpeed;
		int					Task;

		CVector3			Position;
		CVector3			Velocity;
		CVector3			Rotation;
	} Data;

	struct PlayerNetwork {
		std::chrono::time_point<std::chrono::system_clock> LastSyncSent;
		bool				Synchronized;
		RakNetGUID			GUID;
		SystemAddress		Ip;
	} Network;

public:
	static int Amount;

	CPlayerEntity() {};
	~CPlayerEntity() {};

	void Create(std::string Name, RakNetGUID GUID, SystemAddress Ip);
	void Destroy();

	void Pulse();
	void Update(Packet *packet);

	int				GetPlayerID() { return Information.PlayerID; }
	void			SetPlayerID(int playerid) { Information.PlayerID = playerid; }
	int				GetId() { return Information.Entity; }
	std::string		GetUsername() { return Information.Name.C_String(); }
	void			SetUsername(RakString name) { Information.Name = name; }

	int				GetScore() { return Statistics.Score; }

	int				GetVehicle() { return Data.Vehicle.VehicleID; }
	int				GetVehicleSeat() { return Data.Vehicle.Seat; }

	CVector3		GetPosition() { return Data.Position; }
	void			SetPosition(CVector3 position) { Data.Position = position; }

	CVector3		GetRotation() { return Data.Rotation; }
	void			SetRotation(CVector3 rotation) { Data.Rotation = rotation; }

	const std::wstring GetModel() { return Data.Model.Model; }
	void			SetModel(const std::wstring model) { Data.Model.Model = model; }

	PlayerData::PlayerComponent GetModelComponent(const int index) { return Data.ModelComponents[index]; }
	void			SetModelComponent(const int index, const int drawableid, const int textureid, const int paletteid)
	{ 
		Data.ModelComponents[index].drawableid = drawableid;
		Data.ModelComponents[index].textureid = textureid;
		Data.ModelComponents[index].paletteid = paletteid;
	}
	PlayerData::PlayerHeadBlend GetModelHeadBlend() { return Data.ModelHeadBlend; }
	void			SetModelHeadBlend(const int shapeFirst, const float shapeMix, const int shapeSecond, const int shapeThird, const int skinFirst, const float skinMix, const int skinSecond, const int skinThird, const float thirdMix )
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
	PlayerData::PlayerHeadOverlay GetModelHeadOverlay(const int index) { return Data.ModelHeadOverlay[index]; }
	void			SetModelHeadOverlay(const int index, const int type, const int colorType, const int colorID, const int secondColorID, const float opacity )
	{
		Data.ModelHeadOverlay[index].index = type;
		Data.ModelHeadOverlay[index].colorType = colorType;
		Data.ModelHeadOverlay[index].colorID = colorID;
		Data.ModelHeadOverlay[index].secondColorID = secondColorID;
		Data.ModelHeadOverlay[index].opacity = opacity;
	}
	PlayerData::PlayerProp	GetModelProp(const int index) { return Data.ModelProp[index]; }
	void			SetModelProp(const int index, const int drawableid, const int textureid)
	{
		Data.ModelProp[index].drawableid = drawableid;
		Data.ModelProp[index].textureid = textureid;
	}
	float			GetModelFaceFeature(const int index) { return Data.ModelFaceFeature[index].scale; }
	void			SetModelFaceFeature(const int index, const float scale) { Data.ModelFaceFeature[index].scale = scale; }

	bool			GetSynchronized()	{ return Network.Synchronized; }
	RakNetGUID		GetGUID()	{ return Network.GUID; };
	SystemAddress	GetIp()	{ return Network.Ip; }

	void			RequestData(RakNetGUID requester);

	PlayerInfo		SetInfo(PlayerInfo newinfo) { Information = newinfo; }
	PlayerStats		SetStats(PlayerStats newstats) { Statistics = newstats; }
	PlayerData		SetData(PlayerData newdata) { Data = newdata; }

	PlayerInfo		GetInfo() { return Information; }
	PlayerStats		GetStats() { return Statistics; }
	PlayerData		GetData() { return Data; }
};
extern std::vector<CPlayerEntity> g_Players;
