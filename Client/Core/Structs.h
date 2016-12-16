#pragma once
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