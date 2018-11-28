#pragma once
#include "OffsetHandler.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector.h"

enum WeaponType
{
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SMG,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_HEAVY,
	WEAPONTYPE_SNIPER,
	WEAPONTYPE_OTHER,
};

enum eClientClassId
{
	NextBotCombatCharacter = 0,
	CAK47 = 1,
	CBaseAnimating = 2,
	CBaseAnimatingOverlay = 3,
	CBaseAttributableItem = 4,
	CBaseButton = 5,
	CBaseCombatCharacter = 6,
	CBaseCombatWeapon = 7,
	CBaseCSGrenade = 8,
	CBaseCSGrenadeProjectile = 9,
	CBaseDoor = 10,
	CBaseEntity = 11,
	CBaseFlex = 12,
	CBaseGrenade = 13,
	CBaseParticleEntity = 14,
	CBasePlayer = 15,
	CBasePropDoor = 16,
	CBaseTeamObjectiveResource = 17,
	CBaseTempEntity = 18,
	CBaseToggle = 19,
	CBaseTrigger = 20,
	CBaseViewModel = 21,
	CBaseVPhysicsTrigger = 22,
	CBaseWeaponWorldModel = 23,
	CBeam = 24,
	CBeamSpotlight = 25,
	CBoneFollower = 26,
	CBreakableProp = 27,
	CBreakableSurface = 28,
	CC4 = 29,
	CCascadeLight = 30,
	CChicken = 31,
	CColorCorrection = 32,
	CColorCorrectionVolume = 33,
	CCSGameRulesProxy = 34,
	CCSPlayer = 35,
	CCSPlayerResource = 36,
	CCSRagdoll = 37,
	CCSTeam = 38,
	CDEagle = 39,
	CDecoyGrenade = 40,
	CDecoyProjectile = 41,
	CDynamicLight = 42,
	CDynamicProp = 43,
	CEconEntity = 44,
	CEmbers = 45,
	CEntityDissolve = 46,
	CEntityFlame = 47,
	CEntityFreezing = 48,
	CEntityParticleTrail = 49,
	CEnvAmbientLight = 50,
	CEnvDetailController = 51,
	CEnvDOFController = 52,
	CEnvParticleScript = 53,
	CEnvProjectedTexture = 54,
	CEnvQuadraticBeam = 55,
	CEnvScreenEffect = 56,
	CEnvScreenOverlay = 57,
	CEnvTonemapController = 58,
	CEnvWind = 59,
	CFireCrackerBlast = 60,
	CFireSmoke = 61,
	CFireTrail = 62,
	CFish = 63,
	CFlashbang = 64,
	CFogController = 65,
	CFootstepControl = 66,
	CFunc_Dust = 67,
	CFunc_LOD = 68,
	CFuncAreaPortalWindow = 69,
	CFuncBrush = 70,
	CFuncConveyor = 71,
	CFuncLadder = 72,
	CFuncMonitor = 73,
	CFuncMoveLinear = 74,
	CFuncOccluder = 75,
	CFuncReflectiveGlass = 76,
	CFuncRotating = 77,
	CFuncSmokeVolume = 78,
	CFuncTrackTrain = 79,
	CGameRulesProxy = 80,
	CHandleTest = 81,
	CHEGrenade = 82,
	CHostage = 83,
	CHostageCarriableProp = 84,
	CIncendiaryGrenade = 85,
	CInferno = 86,
	CInfoLadderDismount = 87,
	CInfoOverlayAccessor = 88,
	CKnife = 89,
	CKnifeGG = 90,
	CLightGlow = 91,
	CMaterialModifyControl = 92,
	CMolotovGrenade = 93,
	CMolotovProjectile = 94,
	CMovieDisplay = 95,
	CParticleFire = 96,
	CParticlePerformanceMonitor = 97,
	CParticleSystem = 98,
	CPhysBox = 99,
	CPhysBoxMultiplayer = 100,
	CPhysicsProp = 101,
	CPhysicsPropMultiplayer = 102,
	CPhysMagnet = 103,
	CPlantedC4 = 104,
	CPlasma = 105,
	CPlayerResource = 106,
	CPointCamera = 107,
	CPointCommentaryNode = 108,
	CPoseController = 109,
	CPostProcessController = 110,
	CPrecipitation = 111,
	CPrecipitationBlocker = 112,
	CPredictedViewModel = 113,
	CProp_Hallucination = 114,
	CPropDoorRotating = 115,
	CPropJeep = 116,
	CPropVehicleDriveable = 117,
	CRagdollManager = 118,
	CRagdollProp = 119,
	CRagdollPropAttached = 120,
	CRopeKeyframe = 121,
	CSCAR17 = 122,
	CSceneEntity = 123,
	CShadowControl = 124,
	CSlideshowDisplay = 125,
	CSmokeGrenade = 126,
	CSmokeGrenadeProjectile = 127,
	CSmokeStack = 128,
	CSpatialEntity = 129,
	CSpotlightEnd = 130,
	CSprite = 131,
	CSpriteOriented = 132,
	CSpriteTrail = 133,
	CStatueProp = 134,
	CSteamJet = 135,
	CSun = 136,
	CSunlightShadowControl = 137,
	CTeam = 138,
	CTeamplayRoundBasedRulesProxy = 139,
	CTEArmorRicochet = 140,
	CTEBaseBeam = 141,
	CTEBeamEntPoint = 142,
	CTEBeamEnts = 143,
	CTEBeamFollow = 144,
	CTEBeamLaser = 145,
	CTEBeamPoints = 146,
	CTEBeamRing = 147,
	CTEBeamRingPoint = 148,
	CTEBeamSpline = 149,
	CTEBloodSprite = 150,
	CTEBloodStream = 151,
	CTEBreakModel = 152,
	CTEBSPDecal = 153,
	CTEBubbles = 154,
	CTEBubbleTrail = 155,
	CTEClientProjectile = 156,
	CTEDecal = 157,
	CTEDust = 158,
	CTEDynamicLight = 159,
	CTEEffectDispatch = 160,
	CTEEnergySplash = 161,
	CTEExplosion = 162,
	CTEFireBullets = 163,
	CTEFizz = 164,
	CTEFootprintDecal = 165,
	CTEFoundryHelpers = 166,
	CTEGaussExplosion = 167,
	CTEGlowSprite = 168,
	CTEImpact = 169,
	CTEKillPlayerAttachments = 170,
	CTELargeFunnel = 171,
	CTEMetalSparks = 172,
	CTEMuzzleFlash = 173,
	CTEParticleSystem = 174,
	CTEPhysicsProp = 175,
	CTEPlantBomb = 176,
	CTEPlayerAnimEvent = 177,
	CTEPlayerDecal = 178,
	CTEProjectedDecal = 179,
	CTERadioIcon = 180,
	CTEShatterSurface = 181,
	CTEShowLine = 182,
	CTesla = 183,
	CTESmoke = 184,
	CTESparks = 185,
	CTESprite = 186,
	CTESpriteSpray = 187,
	CTest_ProxyToggle_Networkable = 188,
	CTestTraceline = 189,
	CTEWorldDecal = 190,
	CTriggerPlayerMovement = 191,
	CTriggerSoundOperator = 192,
	CVGuiScreen = 193,
	CVoteController = 194,
	CWaterBullet = 195,
	CWaterLODControl = 196,
	CWeaponAug = 197,
	CWeaponAWP = 198,
	CWeaponBizon = 199,
	CWeaponCSBase = 200,
	CWeaponCSBaseGun = 201,
	CWeaponCycler = 202,
	CWeaponElite = 203,
	CWeaponFamas = 204,
	CWeaponFiveSeven = 205,
	CWeaponG3SG1 = 206,
	CWeaponGalil = 207,
	CWeaponGalilAR = 208,
	CWeaponGlock = 209,
	CWeaponHKP2000 = 210,
	CWeaponM249 = 211,
	CWeaponM3 = 212,
	CWeaponM4A1 = 213,
	CWeaponMAC10 = 214,
	CWeaponMag7 = 215,
	CWeaponMP5Navy = 216,
	CWeaponMP7 = 217,
	CWeaponMP9 = 218,
	CWeaponNegev = 219,
	CWeaponNOVA = 220,
	CWeaponP228 = 221,
	CWeaponP250 = 222,
	CWeaponP90 = 223,
	CWeaponSawedoff = 224,
	CWeaponSCAR20 = 225,
	CWeaponScout = 226,
	CWeaponSG550 = 227,
	CWeaponSG552 = 228,
	CWeaponSG556 = 229,
	CWeaponSSG08 = 230,
	CWeaponTaser = 231,
	CWeaponTec9 = 232,
	CWeaponTMP = 233,
	CWeaponUMP45 = 234,
	CWeaponUSP = 235,
	CWeaponXM1014 = 236,
	CWorld = 237,
	DustTrail = 238,
	MovieExplosion = 239,
	ParticleSmokeGrenade = 240,
	RocketTrail = 241,
	SmokeTrail = 242,
	SporeExplosion = 243,
	SporeTrail = 244,
};

enum WeaponIndex
{
	WEAPON_NONE,
	WEAPON_DEAGLE = 1,
	WEAPON_DUAL = 2,
	WEAPON_FIVE7 = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250_CZ75 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFEGG = 41,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKE = 45,
	WEAPON_T_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_CT_MOLOTOV = 48,
	WEAPON_C4 = 49,
	//WEAPON_REVOLVER = 64,
	WEAPON_MAX
};

enum ItemDefinitionIndex : int {
	DEAGLE = 1,
	ELITE = 2,
	FIVESEVEN = 3,
	GLOCK = 4,
	AK47 = 7,
	AUG = 8,
	AWP = 9,
	FAMAS = 10,
	G3SG1 = 11,
	GALILAR = 13,
	M249 = 14,
	M4A1 = 16,
	MAC10 = 17,
	P90 = 19,
	UMP45 = 24,
	XM1014 = 25,
	BIZON = 26,
	MAG7 = 27,
	NEGEV = 28,
	SAWEDOFF = 29,
	TEC9 = 30,
	TASER = 31,
	HKP2000 = 32,
	MP7 = 33,
	MP9 = 34,
	NOVA = 35,
	P250 = 36,
	SCAR20 = 38,
	SG556 = 39,
	SSG08 = 40,
	KNIFE = 42,
	FLASHBANG = 43,
	HEGRENADE = 44,
	SMOKEGRENADE = 45,
	MOLOTOV = 46,
	DECOY = 47,
	INCGRENADE = 48,
	C4 = 49,
	KNIFE_T = 59,
	M4A1_SILENCER = 60,
	USP_SILENCER = 61,
	CZ75A = 63,
	REVOLVER = 64,
	KNIFE_BAYONET = 500,
	KNIFE_FLIP = 505,
	KNIFE_GUT = 506,
	KNIFE_KARAMBIT = 507,
	KNIFE_M9_BAYONET = 508,
	KNIFE_TACTICAL = 509,
	KNIFE_FALCHION = 512,
	KNIFE_SURVIVAL_BOWIE = 514,
	KNIFE_BUTTERFLY = 515,
	KNIFE_PUSH = 516
};

enum SIGNONSTATE
{
	SIGNONSTATE_NONE,
	SIGNONSTATE_CHALLENGE,
	SIGNONSTATE_CONNECTED,
	SIGNONSTATE_NEW,
	SIGNONSTATE_PRESPAWN,
	SIGNONSTATE_SPAWN,
	SIGNONSTATE_FULL,
	SIGNONSTATE_CHANGELEVEL,
};

typedef struct
{
	float flMatrix[4][4];
}WorldToScreenMatrix_t;

enum HitboxList
{
	HITBOX_PELVIS,
	HITBOX_L_THIGH,
	HITBOX_L_CALF,
	HITBOX_L_FOOT,
	HITBOX_R_THIGH,
	HITBOX_R_CALF,
	HITBOX_R_FOOT,
	HITBOX_SPINE1,
	HITBOX_SPINE2,
	HITBOX_SPINE3,
	HITBOX_NECK,
	HITBOX_HEAD,
	HITBOX_L_UPPERARM,
	HITBOX_L_FOREARM,
	HITBOX_L_HAND,
	HITBOX_R_UPPERARM,
	HITBOX_R_FOREARM,
	HITBOX_R_HAND,
	HITBOX_L_CLAVICLE,
	HITBOX_R_CLAVICLE,
	HITBOX_HELMET,
	HITBOX_SPINE4,
	HITBOX_MAX,
};

enum BoneList
{
	BONE_PELVIS,
	BONE_SPINE0,
	BONE_SPINE1,
	BONE_SPINE2,
	BONE_SPINE3,
	BONE_NECK,
	BONE_HEAD,
	BONE_L_CLAVICLE,
	BONE_L_UPPER_ARM,
	BONE_L_FOREARM,
	BONE_L_HAND,
	FINGER_MIDDLE_META_L,
	FINGER_MIDDLE_0_L,
	FINGER_MIDDLE_1_L,
	FINGER_MIDDLE_2_L,
	FINGER_PINKY_META_L,
	FINGER_PINKY_0_L,
	FINGER_PINKY_1_L,
	FINGER_PINKY_2_L,
	FINGER_INDEX_META_L,
	FINGER_INDEX_0_L,
	FINGER_INDEX_1_L,
	FINGER_INDEX_2_L,
	FINGER_THUMB_0_L,
	FINGER_THUMB_1_L,
	FINGER_THUMB_2_L,
	FINGER_RING_META_L,
	FINGER_RING_0_L,
	FINGER_RING_1_L,
	FINGER_RING_2_L,
	WEAPON_HAND_L,
	ARM_LOWER_L_TWIST,
	ARM_LOWRE_L_TWIST1,
	ARM_UPPER_L_TWIST,
	ARM_UPPER_L_TWIST1,
	CLAVICLE_R,
	ARM_UPPER_R,
	ARM_LOWER_R,
	HAND_R,
	FINGER_MIDDLE_META_R,
	FINGER_MIDDLE_0_R,
	FINGER_MIDDLE_1_R,
	FINGER_MIDDLE_2_R,
	FINGER_PINKY_META_R,
	FINGER_PINKY_0_R,
	FINGER_PINKY_1_R,
	FINGER_PINKY_2_R,
	FINGER_INDEX_META_R,
	FINGER_INDEX_0_R,
	FINGER_INDEX_1_R,
	FINGER_INDEX_2_R,
	FINGER_THUMB_0_R,
	FINGER_THUMB_1_R,
	FINGER_THUMB_2_R,
	FINGER_RING_META_R,
	FINGER_RING_0_R,
	FINGER_RING_1_R,
	FINGER_RING_2_R,
	WEAPON_HAND_R,
	ARM_LOWER_R_TWIST,
	ARM_LOWER_R_TWIST1,
	ARM_UPPER_R_TWIST,
	ARM_UPPER_R_TWIST1,
	LEG_UPPER_L,
	LEG_LOWER_L,
	ANKLE_L,
	BALL_L,
	LEG_UPPER_L_TWIST,
	LEG_UPPER_L_TWIST1,
	LEG_UPPER_R,
	LEG_LOWER_R,
	ANKLE_R,
	BALL_R,
	LEG_UPPER_R_TWIST,
	LEG_UPPER_R_TWIST1,
	WEAPON_BONE,
	LH_IK_DRIVER,
	LEAN_ROOT,
	LFOOT_LOCK,
	RFOOT_LOCK,
	PRIMARY_JIGGLE_JNT,
	PRIMARY_SMG_SIGGLE_JNT,
	BONE_MAX
};

//using namespace Misc
namespace Misc
{
	struct Bone
	{
		float bone_x;
		char pad1[0xC];
		float bone_y;
		char pad2[0xC];
		float bone_z;
		char pad3[0xC];
	};

	struct BoneMatrix
	{
		Bone BONE_PELVIS;
		Bone BONE_SPINE0;
		Bone BONE_SPINE1;
		Bone BONE_SPINE2;
		Bone BONE_SPINE3;
		Bone BONE_NECK;
		Bone BONE_HEAD;
		Bone BONE_L_CLAVICLE;
		Bone BONE_L_UPPER_ARM;
		Bone BONE_L_FOREARM;
		Bone BONE_L_HAND;
		Bone FINGER_MIDDLE_META_L;
		Bone FINGER_MIDDLE_0_L;
		Bone FINGER_MIDDLE_1_L;
		Bone FINGER_MIDDLE_2_L;
		Bone FINGER_PINKY_META_L;
		Bone FINGER_PINKY_0_L;
		Bone FINGER_PINKY_1_L;
		Bone FINGER_PINKY_2_L;
		Bone FINGER_INDEX_META_L;
		Bone FINGER_INDEX_0_L;
		Bone FINGER_INDEX_1_L;
		Bone FINGER_INDEX_2_L;
		Bone FINGER_THUMB_0_L;
		Bone FINGER_THUMB_1_L;
		Bone FINGER_THUMB_2_L;
		Bone FINGER_RING_META_L;
		Bone FINGER_RING_0_L;
		Bone FINGER_RING_1_L;
		Bone FINGER_RING_2_L;
		Bone WEAPON_HAND_L;
		Bone ARM_LOWER_L_TWIST;
		Bone ARM_LOWRE_L_TWIST1;
		Bone ARM_UPPER_L_TWIST;
		Bone ARM_UPPER_L_TWIST1;
		Bone CLAVICLE_R;
		Bone ARM_UPPER_R;
		Bone ARM_LOWER_R;
		Bone HAND_R;
		Bone FINGER_MIDDLE_META_R;
		Bone FINGER_MIDDLE_0_R;
		Bone FINGER_MIDDLE_1_R;
		Bone FINGER_MIDDLE_2_R;
		Bone FINGER_PINKY_META_R;
		Bone FINGER_PINKY_0_R;
		Bone FINGER_PINKY_1_R;
		Bone FINGER_PINKY_2_R;
		Bone FINGER_INDEX_META_R;
		Bone FINGER_INDEX_0_R;
		Bone FINGER_INDEX_1_R;
		Bone FINGER_INDEX_2_R;
		Bone FINGER_THUMB_0_R;
		Bone FINGER_THUMB_1_R;
		Bone FINGER_THUMB_2_R;
		Bone FINGER_RING_META_R;
		Bone FINGER_RING_0_R;
		Bone FINGER_RING_1_R;
		Bone FINGER_RING_2_R;
		Bone WEAPON_HAND_R;
		Bone ARM_LOWER_R_TWIST;
		Bone ARM_LOWER_R_TWIST1;
		Bone ARM_UPPER_R_TWIST;
		Bone ARM_UPPER_R_TWIST1;
		Bone LEG_UPPER_L;
		Bone LEG_LOWER_L;
		Bone ANKLE_L;
		Bone BALL_L;
		Bone LEG_UPPER_L_TWIST;
		Bone LEG_UPPER_L_TWIST1;
		Bone LEG_UPPER_R;
		Bone LEG_LOWER_R;
		Bone ANKLE_R;
		Bone BALL_R;
		Bone LEG_UPPER_R_TWIST;
		Bone LEG_UPPER_R_TWIST1;
		Bone WEAPON_BONE;
		Bone LH_IK_DRIVER;
		Bone LEAN_ROOT;
		Bone LFOOT_LOCK;
		Bone RFOOT_LOCK;
		Bone PRIMARY_JIGGLE_JNT;
		Bone PRIMARY_SMG_SIGGLE_JNT;
		Bone BONE_MAX;
	};

}

struct tPlayerName
{
	wchar_t Text[32];
};

class player_info_t
{
public:
	char unknown0[0x10];
	wchar_t name[32];
	char unknown2[0x200];
};

struct Hitbox_t
{
	int		iBone;
	Vector	vMin;
	Vector	vMax;

	void Setup(int bone, Vector min, Vector max)
	{
		iBone = bone;
		vMin.x = min.x;
		vMin.y = min.y;
		vMin.z = min.z;
		vMax.x = max.x;
		vMax.y = max.y;
		vMax.z = max.z;
	}
};

struct GlowObject { //GlowObject
	DWORD dwBase;
	float red;
	float green;
	float blue;
	float alpha;
	uint8_t unk1[16];
	bool renderoccluded;
	bool rendernonoccluded;
	bool fullbloom;
	uint8_t unk2[14];
};

static const string MatchmakingRanks[] = {
	"UNRANKED",
	"Silver I",
	"Silver II",
	"Silver III",
	"Silver IV",
	"Silver Elite",
	"Silver Elite Master",
	"Gold Nova I",
	"Gold Nova II",
	"Gold Nova III",
	"Gold Nova Master",
	"Master Guardian I",
	"Master Guardian II",
	"Master Guardian Elite",
	"Distinguished Master Guardian",
	"Legendary Eagle",
	"Legendary Eagle Master",
	"Supreme Master First Class",
	"The Global Elite"
};

#pragma region globalVars
OffsetHandler oh;
bool bSend;

// Bitflags
#define FL_ONGROUND			(1<<0)
#define FL_DUCKING			(1<<1)
#define FL_ANIMDUCKING		(1<<2)

double RADPI = 180 / M_PI;

char mapName[64];

const int playerCount = 64;

Hitbox_t Hitbox[21];

//key settings & aimbot settings
int aimkey;
int trigkey;
int targetbone;
int rcsscale;
int fovscale;
int smoothscale;
int stickyenabled;
int vischeck;

//switches
bool antiflash = false;		//if noflash is enabled
bool aimbotting = false;	//if aimbot is currently running
bool aimbotOn = false;		//aimbot enabled/disabled
bool ESPOn = false;			//ESP enabled/disabled
bool triggerbotOn = false;	//triggerbot enabled/disabled
bool bhopOn = false;			//bhop enabled/disabled
bool RecoilControl = false;
bool fakelagOn = false;
int showRanks = 999;


int shotsFired;
int lastShotsFired = 0;
float DeltaTime;
float m_AimTime;
int BaseTime = 0;
float YawDistance;
float AimPercent = 0.f;

bool KILLALL = false;
int DEBUGMODE = -1; //-1 off, 0 verbose, 1 esp, 2 aimbot, 3 triggerbot, 4 offsets, 5 player data, 6 angles

#pragma endregion