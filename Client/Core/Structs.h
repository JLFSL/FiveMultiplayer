#pragma once

#ifdef __SC_VERSION__
#define ADDRESS_WORLD					0x2328EC8		//42
#define ADDRESS_WAYPOINT				0x1F7F400		//wtb a (mini)map struct
#define ADDRESS_OBJECTIVE				0x1F7F4B0
#define ADDRESS_AMMO					0x0F706C5		//Ammo dec code; 41 2B D1 E8; 90 90 90 E8
#define ADDRESS_MAGAZINE				0x0F70680		//Magazine dec code; 41 2B C9 3B C8 0F; 90 90 90 3B C8 0F
#endif
#ifdef __STEAM_VERSION__
#define ADDRESS_WORLD					0x232BC00
#define ADDRESS_WAYPOINT				0x1F82460
#define ADDRESS_OBJECTIVE				0x1F82510
#define ADDRESS_AMMO					0x0F71C38
#define ADDRESS_MAGAZINE				0x0F71C7D
#endif

//offset from WORLD
#define OFFSET_PLAYER					0x08			//playerbase

//entity offsets
#define OFFSET_ENTITY_POSBASE			0x30			//base of a structure that contains entity coords
#define OFFSET_ENTITY_POSBASE_POS		0x50			//vector3
#define OFFSET_ENTITY_POS				0x90			//vector3
#define OFFSET_ENTITY_HEALTH			0x280			//entity health (except for vehicles); float cur, float max
#define OFFSET_ENTITY_HEALTH_MAX		0x2A0			//they moved this away from curHealth in 1.36 :(
#define OFFSET_ENTITY_ATTACKER			0x2A8			//base to a list of the last 3 entities that attacked the current entity
#define OFFSET_ENTITY_GOD				0x189			//godmode; on = 1, off = 0; byte

//player (entity) offsets
#define OFFSET_PLAYER_ARMOR						0x14B0			//armour
#define OFFSET_PLAYER_INFO						0x10B8			//playerInfo struct
#define OFFSET_PLAYER_INFO_WANTED_CAN_CHANGE	0x71C			//fWantedCanChange
#define OFFSET_PLAYER_INFO_WANTED				0x798			//wanted level; DWORD
#define	OFFSET_PLAYER_INFO_RUN_SPD				0xE8			//run speed; def 1; float
#define OFFSET_PLAYER_INFO_SWIM_SPD				0xE4			//swim speed; def 1; float
#define OFFSET_PLAYER_INFO_FRAMEFLAGS			0x190			//frame flags; DWORD
#define OFFSET_PLAYER_INFO_STAMINA				0xC00			//fStamina, fStaminaMax
#define OFFSET_PLAYER_VEHICLE					0xD28			//ptr to last used vehicle
#define OFFSET_PLAYER_NAME						0x7C
#define OFFSET_PLAYER_RAGDOLL					0x10A8			//byte; CPed.noRagdoll: 0x20 = off; 0x00/0x01 = on
#define OFFSET_PLAYER_SEATBELT					0x13EC			//byte; CPed.seatBelt: 0xC8 = off; 0xC9 = on
#define OFFSET_PLAYER_INVEHICLE					0x146B

//vehicle offsets
#define OFFSET_VEHICLE_HEALTH						0x84C			//vehicle health; 0.f-1000.f
#define OFFSET_VEHICLE_GRAVITY						0xB7C			//fGravity
#define OFFSET_VEHICLE_BULLETPROOF_TIRES			0x883			//btBulletproofTires;  (btBulletproofTires & 0x20) ? true : false
#define OFFSET_VEHICLE_HANDLING						0x878
#define OFFSET_VEHICLE_HANDLING_ACCELERATION		0x4C
#define OFFSET_VEHICLE_HANDLING_BRAKEFORCE			0x6C
#define OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_MIN	0x90			//fTractionCurveMin
#define OFFSET_VEHICLE_HANDLING_DEFORM_MULTIPLIER	0xF8			//fDeformationDamageMult
#define OFFSET_VEHICLE_HANDLING_UPSHIFT				0x58
#define OFFSET_VEHICLE_HANDLING_SUSPENSION_FORCE	0xBC			//fSuspensionForce 

//weapon offsets
#define OFFSET_WEAPON_MANAGER			0x10C8			//from playerbase
#define OFFSET_WEAPON_CURRENT			0x20			//from weapon manager
#define OFFSET_WEAPON_AMMOINFO			0x48			//from weaponbase
#define OFFSET_WEAPON_AMMOINFO_MAX		0x28			//ammoinfo
#define OFFSET_WEAPON_AMMOINFO_CUR_1	0x08			//ptr lvl 1, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CUR_2	0x00			//ptr tr lvl 2, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CURAMMO	0x18			//offset to cur ammo
#define OFFSET_WEAPON_AMMOINFO_TYPE		0x0C			//offset to projectile type?
#define OFFSET_WEAPON_SPREAD			0x5C			//float set to 0
#define OFFSET_WEAPON_BULLET_DMG		0x98			//float times 10 (so when 0, it will stay 0)
#define OFFSET_WEAPON_RELOAD_MULTIPLIER	0x114			//float times 10
#define OFFSET_WEAPON_RECOIL			0x2A4			//float set to 0
#define OFFSET_WEAPON_MODEL_HASH		0x14
#define OFFSET_WEAPON_NAME_HASH			0x10
#define OFFSET_WEAPON_RELOAD_VEHICLE	0x110
#define OFFSET_WEAPON_RANGE				0x25C
#define OFFSET_WEAPON_SPINUP			0x124
#define OFFSET_WEAPON_SPIN				0x128
#define OFFSET_WEAPON_BULLET_BATCH		0x100			//dwBulletInBatch
#define OFFSET_WEAPON_MUZZLE_VELOCITY	0xFC			//fMuzzleVelocity
#define OFFSET_WEAPON_BATCH_SPREAD		0x104			//fBatchSpread


#define OFFSET_ATTACKER_DISTANCE		0x18			//changed to 0x18, from 0x10

class CPed;
class CNavigation;
class CAttacker;
class CVehicle;
class CPlayerInfo;
class CWeaponManager;
class CWeapon;
class CAmmoInfo;
class CVehicleColors;
class CVehicleColorOptions;
class CVehicleHandling;
class CWantedData;

class CPed
{
public:
	char pad_0x0000[0x2C]; //0x0000
	BYTE btInvisibleSP; //0x002C
	char pad_0x002D[0x1]; //0x002D
	BYTE btFreezeMomentum; //0x002E
	char pad_0x002F[0x1]; //0x002F
	CNavigation* CNavigation; //0x0030
	char pad_0x0038[0x58]; //0x0038
	Vector3 v3VisualPos; //0x0090
	char pad_0x009C[0xED]; //0x009C
	BYTE btGodMode; //0x0189
	char pad_0x018A[0xF6]; //0x018A
	float fHealth; //0x0280
	char pad_0x0284[0x1C]; //0x0284
	float fHealthMax; //0x02A0
	char pad_0x02A4[0x4]; //0x02A4
	CAttacker* CAttacker; //0x02A8
	char pad_0x02B0[0x70]; //0x02B0
	Vector3 v3Velocity; //0x0320
	char pad_0x032C[0x9FC]; //0x032C
	CVehicle* CVehicleLast; //0x0D28
	char pad_0x0D30[0x378]; //0x0D30
	BYTE btNoRagdoll; //0x10A8
	char pad_0x10A9[0xF]; //0x10A9
	CPlayerInfo* CPlayerInfo; //0x10B8
	char pad_0x10C0[0x8]; //0x10C0
	CWeaponManager* CWeaponManager; //0x10C8
	char pad_0x10D0[0x31C]; //0x10D0
	BYTE btSeatBelt; //0x13EC
	char pad_0x13ED[0xB]; //0x13ED
	BYTE btSeatbeltWindshield; //0x13F8
	char pad_0x13F9[0x72]; //0x13F9
	BYTE btIsInVehicle; //0x146B
	char pad_0x146C[0x44]; //0x146C
	float fArmor; //0x14B0
	char pad_0x14B4[0x3C]; //0x14B4
	CVehicle* CVehicleLast2; //0x14F0

}; //Size=0x14F8

class CNavigation
{
public:
	char pad_0x0000[0x50]; //0x0000
	Vector3 v3Pos; //0x0050

}; //Size=0x005C

class CAttacker
{
public:
	CPed* CPed0; //0x0000
	char pad_0x0008[0x10]; //0x0008
	CPed* CPed1; //0x0018
	char pad_0x0020[0x10]; //0x0020
	CPed* CPed2; //0x0030

}; //Size=0x0038

class CVehicle
{
public:
	char pad_0x0000[0x30]; //0x0000
	CNavigation* CNavigation; //0x0030
	char pad_0x0038[0x10]; //0x0038
	CVehicleColorOptions* CVehicleColorOptions; //0x0048
	char pad_0x0050[0x40]; //0x0050
	Vector3 v3VisualPos; //0x0090
	char pad_0x009C[0xED]; //0x009C
	BYTE btGodMode; //0x0189
	char pad_0x018A[0xF6]; //0x018A
	float fHealth; //0x0280
	char pad_0x0284[0x1C]; //0x0284
	float fHealthMax; //0x02A0
	char pad_0x02A4[0x4]; //0x02A4
	CAttacker* CAttacker; //0x02A8
	char pad_0x02B0[0x59C]; //0x02B0
	float fHealth2; //0x084C
	char pad_0x0850[0x28]; //0x0850
	CVehicleHandling* CVehicleHandling; //0x0878
	char pad_0x0880[0x3]; //0x0880
	BYTE btBulletproofTires; //0x0883
	char pad_0x0884[0x2F8]; //0x0884
	float fGravity; //0x0B7C

}; //Size=0x0B80

class CWantedData
{
public:
	char pad_0x0000[0x2C]; //0x0000
	float fWantedCanChange; //0x002C
	char pad_0x0030[0x10]; //0x0030
	Vector3 v3WantedCenterPos; //0x0040
	char pad_0x004C[0x4]; //0x004C
	Vector3 v3WantedCenterPos2; //0x0050
	char pad_0x005C[0x38]; //0x005C
	BYTE btFlag0; //0x0094
	BYTE btFlag1; //0x0095
	BYTE btFlag2; //0x0096
	BYTE btFlag3; //0x0097
	char pad_0x0098[0xC]; //0x0098
	DWORD dwWantedLevelFake; //0x00A4
	DWORD dwWantedLevel; //0x00A8

}; //Size=0x00AC

class CPlayerInfo
{
public:
	char pad_0x0000[0x7C]; //0x0000
	char sName[10]; //0x007C
	char pad_0x0086[0x5E]; //0x0086
	float fSwimSpeed; //0x00E4
	float fRunSpeed; //0x00E8
	char pad_0x00EC[0xA5]; //0x00EC
	BYTE btFrameFlags; //0x0191
	char pad_0x0192[0x55E]; //0x0192
	CWantedData CWantedData; //0x06F0
	char pad_0x079C[0x464]; //0x079C
	float fStamina; //0x0C00
	float fStaminaMax; //0x0C04

}; //Size=0x0C08

class CWeaponManager
{
public:
	char pad_0x0000[0x20]; //0x0000
	CWeapon* CWeaponCur; //0x0020

}; //Size=0x0028

class CWeapon
{
public:
	char pad_0x0000[0x10]; //0x0000
	DWORD dwNameHash; //0x0010
	DWORD dwModelHash; //0x0014
	char pad_0x0018[0x24]; //0x0018
	DWORD dwAmmoType; //0x003C
	DWORD dwWeaponWheelSlot; //0x0040
	char pad_0x0044[0x4]; //0x0044
	CAmmoInfo* CAmmoInfo; //0x0048
	char pad_0x0050[0xC]; //0x0050
	float fSpread; //0x005C
	char pad_0x0060[0x38]; //0x0060
	float fBulletDamage; //0x0098
	char pad_0x009C[0x1C]; //0x009C
	float fForce; //0x00B8
	float fForcePed; //0x00BC
	float fForceVehicle; //0x00C0
	float fForceFlying; //0x00C4
	char pad_0x00C8[0x34]; //0x00C8
	float fMuzzleVelocity; //0x00FC
	DWORD dwBulletInBatch; //0x0100
	float fBatchSpread; //0x0104
	char pad_0x0108[0x8]; //0x0108
	float fVehicleReloadTime; //0x0110
	float fAnimReloadRate; //0x0114
	char pad_0x0118[0xC]; //0x0118
	float fSpinUpTime; //0x0124
	float fSpinTime; //0x0128
	char pad_0x012C[0x12C]; //0x012C
	float fLockOnRange; //0x0258
	float fWeaponRange; //0x025C
	char pad_0x0260[0x44]; //0x0260
	float fRecoil; //0x02A4

}; //Size=0x02A8

class CAmmoInfo
{
public:
	char pad_0x0000[0x28]; //0x0000
	DWORD dwMaxAmmo; //0x0028
	char pad_0x002C[0x14]; //0x002C

}; //Size=0x0040

class CVehicleColors
{
public:
	char pad_0x0000[0xA4]; //0x0000
	BYTE btPrimaryBlue; //0x00A4
	BYTE btPrimaryGreen; //0x00A5
	BYTE btPrimaryRed; //0x00A6
	BYTE btPrimaryAlpha; //0x00A7
	BYTE btSecondaryBlue; //0x00A8
	BYTE btSecondaryGreen; //0x00A9
	BYTE btSecondaryRed; //0x00AA
	BYTE btSecondaryAlpha; //0x00AB

}; //Size=0x00AC

class CVehicleColorOptions
{
public:
	char pad_0x0000[0x20]; //0x0000
	CVehicleColors* CVehicleColor; //0x0020

}; //Size=0x0028

class CVehicleHandling
{
public:
	char pad_0x0000[0xC]; //0x0000
	float fMass; //0x000C
	char pad_0x0010[0x10]; //0x0010
	Vector3 v3CentreOfMassOffset; //0x0020
	char pad_0x002C[0x4]; //0x002C
	Vector3 v3InertiaMult; //0x0030
	char pad_0x003C[0x4]; //0x003C
	float fPercentSubmerged; //0x0040
	char pad_0x0044[0x8]; //0x0044
	float fAcceleration; //0x004C
	BYTE btInitialDriveGears; //0x0050
	char pad_0x0051[0x3]; //0x0051
	float fDriveInertia; //0x0054
	float fClutchChangeRateScaleUpShift; //0x0058
	float fClutchChangeRateScaleDownShift; //0x005C
	float fInitialDriveForce; //0x0060
	char pad_0x0064[0x8]; //0x0064
	float fBrakeForce; //0x006C
	char pad_0x0070[0x4]; //0x0070
	float fBrakeBiasFront; //0x0074
	char pad_0x0078[0x4]; //0x0078
	float fHandBrakeForce; //0x007C
	char pad_0x0080[0x8]; //0x0080
	float fTractionCurveMax; //0x0088
	char pad_0x008C[0x4]; //0x008C
	float fTractionCurveMin; //0x0090
	char pad_0x0094[0xC]; //0x0094
	float fTractionSpringDeltaMax; //0x00A0
	char pad_0x00A4[0x4]; //0x00A4
	float fLowSpeedTractionLossMult; //0x00A8
	float fCamberStiffnesss; //0x00AC
	float fTractionBiasFront; //0x00B0
	float fTwoMinus_fTractionBiasFront; //0x00B4
	float fTractionLossMult; //0x00B8
	float fSuspensionForce; //0x00BC
	float fSuspensionCompDamp; //0x00C0
	float fSuspensionReboundDamp; //0x00C4
	float fSuspensionUpperLimit; //0x00C8
	float fSuspensionLowerLimit; //0x00CC
	char pad_0x00D0[0xC]; //0x00D0
	float fAntiRollBarForce; //0x00DC
	char pad_0x00E0[0x8]; //0x00E0
	float fRollCentreHeightFront; //0x00E8
	float fRollCentreHeightRear; //0x00EC
	float fCollisionDamageMult; //0x00F0
	float fWeaponDamageMult; //0x00F4
	float fDeformationDamageMult; //0x00F8
	float fEngineDamageMult; //0x00FC
	float fPetrolTankVolume; //0x0100
	float fOilVolume; //0x0104

}; //Size=0x0108