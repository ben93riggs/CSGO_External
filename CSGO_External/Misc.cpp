#include "Misc.h"

#pragma region globalVars
//ProcMem m;

bool bSend;

// Bitflags
#define FL_ONGROUND			(1<<0)
#define FL_DUCKING			(1<<1)
#define FL_ANIMDUCKING		(1<<2)

double RADPI = 180 / M_PI;

char mapName[64];

Hitbox_t Hitbox[21];

//key settings & aimbot settings
int gamerkey;
int gamer2key;
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



//int lastShotsFired;
//Vector actualPunch;
//Vector lastPunch;
//Vector moveVec;
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