#ifndef __SUDOSTRUCTS_H__
#define __SUDOSTRUCTS_H__

#ifdef __SC_VERSION__
const int ADDRESS_WORLD			= 0x2333980;		//42		/*0x2328EC8*/
const int ADDRESS_WAYPOINT		= 0x1F7F400;		//wtb a (mini)map struct
const int ADDRESS_OBJECTIVE		= 0x1F7F4B0;
const int ADDRESS_AMMO			= 0x0F706C5;		//Ammo dec code; 41 2B D1 E8; 90 90 90 E8
const int ADDRESS_MAGAZINE		= 0x0F70680;		//Magazine dec code; 41 2B C9 3B C8 0F; 90 90 90 3B C8 0F
#endif
#ifdef __STEAM_VERSION__
const int ADDRESS_WORLD			= 0x23378A8;		 // Orig = 0x232BC00
const int ADDRESS_WAYPOINT		= 0x1F82460;
const int ADDRESS_OBJECTIVE		= 0x1F82510;
const int ADDRESS_AMMO			= 0x0F71C38;
const int ADDRESS_MAGAZINE		= 0x0F71C7D;
#endif

//offset from WORLD
const int OFFSET_PLAYER					= 0x08;			//playerbase from world

//entity offsets
const int OFFSET_ENTITY_POSBASE			= 0x30;			//base of a structure that contains entity coords
const int OFFSET_ENTITY_POSBASE_POS		= 0x50;			//vector3
const int OFFSET_ENTITY_POS				= 0x90;			//vector3
const int OFFSET_ENTITY_HEALTH			= 0x280;		//entity health (except for vehicles); float cur, float max
const int OFFSET_ENTITY_HEALTH_MAX		= 0x2A0;		//they moved this away from curHealth in 1.36 :(
const int OFFSET_ENTITY_ATTACKER		= 0x2A8;		//base to a list of the last 3 entities that attacked the current entity
const int OFFSET_ENTITY_GOD				= 0x189;		//godmode; on = 1, off = 0; byte

//player (entity) offsets
const int OFFSET_PLAYER_ARMOR					= 0x14B0;		//armour
const int OFFSET_PLAYER_INFO					= 0x10B8;		//playerInfo struct
const int OFFSET_PLAYER_INFO_WANTED_CAN_CHANGE	= 0x71C;		//fWantedCanChange
const int OFFSET_PLAYER_INFO_WANTED				= 0x798;		//wanted level; DWORD
const int OFFSET_PLAYER_INFO_RUN_SPD			= 0xE8;			//run speed; def 1; float
const int OFFSET_PLAYER_INFO_SWIM_SPD			= 0xE4;			//swim speed; def 1; float
const int OFFSET_PLAYER_INFO_FRAMEFLAGS			= 0x190;		//frame flags; DWORD
const int OFFSET_PLAYER_INFO_STAMINA			= 0xC00;		//fStamina, fStaminaMax
const int OFFSET_PLAYER_VEHICLE					= 0xD28;		//ptr to last used vehicle
const int OFFSET_PLAYER_NAME					= 0x7C;
const int OFFSET_PLAYER_RAGDOLL					= 0x10A8;		//byte; CPed.noRagdoll: 0x20 = off; 0x00/0x01 = on
const int OFFSET_PLAYER_SEATBELT				= 0x13EC;		//byte; CPed.seatBelt: 0xC8 = off; 0xC9 = on
const int OFFSET_PLAYER_INVEHICLE				= 0x146B;

//vehicle offsets
const int OFFSET_VEHICLE_HEALTH							= 0x84C;	//vehicle health; 0.f-1000.f
const int OFFSET_VEHICLE_GRAVITY						= 0xB7C;	//fGravity
const int OFFSET_VEHICLE_BULLETPROOF_TIRES				= 0x883;	//btBulletproofTires;  (btBulletproofTires & 0x20) ? true : false
const int OFFSET_VEHICLE_HANDLING						= 0x878;
const int OFFSET_VEHICLE_HANDLING_ACCELERATION			= 0x4C;
const int OFFSET_VEHICLE_HANDLING_BRAKEFORCE			= 0x6C;
const int OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_MIN	= 0x90;		//fTractionCurveMin
const int OFFSET_VEHICLE_HANDLING_DEFORM_MULTIPLIER		= 0xF8;		//fDeformationDamageMult
const int OFFSET_VEHICLE_HANDLING_UPSHIFT				= 0x58;
const int OFFSET_VEHICLE_HANDLING_SUSPENSION_FORCE		= 0xBC;		//fSuspensionForce 

//weapon offsets
const int OFFSET_WEAPON_MANAGER				= 0x10C8;		//from playerbase
const int OFFSET_WEAPON_CURRENT				= 0x20;			//from weapon manager
const int OFFSET_WEAPON_AMMOINFO			= 0x48;			//from weaponbase
const int OFFSET_WEAPON_AMMOINFO_MAX		= 0x28;			//ammoinfo
const int OFFSET_WEAPON_AMMOINFO_CUR_1		= 0x08;			//ptr lvl 1, ptr 1
const int OFFSET_WEAPON_AMMOINFO_CUR_2		= 0x00;			//ptr tr lvl 2, ptr 1
const int OFFSET_WEAPON_AMMOINFO_CURAMMO	= 0x18;			//offset to cur ammo
const int OFFSET_WEAPON_AMMOINFO_TYPE		= 0x0C;			//offset to projectile type?
const int OFFSET_WEAPON_SPREAD				= 0x5C;			//float set to 0
const int OFFSET_WEAPON_BULLET_DMG			= 0x98;			//float times 10 (so when 0, it will stay 0)
const int OFFSET_WEAPON_RELOAD_MULTIPLIER	= 0x114;		//float times 10
const int OFFSET_WEAPON_RECOIL				= 0x2A4;		//float set to 0
const int OFFSET_WEAPON_MODEL_HASH			= 0x14;
const int OFFSET_WEAPON_NAME_HASH			= 0x10;
const int OFFSET_WEAPON_RELOAD_VEHICLE		= 0x110;
const int OFFSET_WEAPON_RANGE				= 0x25C;
const int OFFSET_WEAPON_SPINUP				= 0x124;
const int OFFSET_WEAPON_SPIN				= 0x128;
const int OFFSET_WEAPON_BULLET_BATCH		= 0x100;		//dwBulletInBatch
const int OFFSET_WEAPON_MUZZLE_VELOCITY		= 0xFC;			//fMuzzleVelocity
const int OFFSET_WEAPON_BATCH_SPREAD		= 0x104;		//fBatchSpread


const int OFFSET_ATTACKER_DISTANCE			= 0x18;			//changed to 0x18, from 0x10


class CReplayInterfacePed
{
private:
	class CPedList
	{
	private:
		/*struct Ped
		{
			CPed* ped;
			char _pad0[0x8];
		};*/

	public:
		Ped peds[256];
	};

public:
	char _pad0[0x100];			// 0000 - 0100
	CPedList* ped_list;			// 0100 - 0108
	int max_peds;				// 0108 - 010C
	char _pad1[0x4];			// 010C - 0110
	int number_of_peds;		// 0110 - 0114
};

class CReplayInterface
{
public:
	void* game_interface;
	void* camera_interface;
	void* vehicle_interface;
	CReplayInterfacePed* ped_interface;
	void* pickup_interface;
	void* object_interface;

	static CReplayInterface* get()
	{
		return *(CReplayInterface**)(Hooking::getReplayPtr);
	}
};

#endif