#pragma region includes
#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include "Misc.h"
#include "Entity.h"
#include <sstream>
#include <windows.h>
#include "Ray.h"
#include "Math.h"

using namespace std;

bool initialize()
{
	auto init = 0;
	while (!oh.mem.Process(L"csgo.exe")) {
		init++;
		system("cls");
		cout << "                                            __                                       " << endl
			<< "  _____  _____      ____    ____    ____  _/  |_   ____        ____  ___  ___  ____  " << endl
			<< " /     \\ \\__  \\    / ___\\  /    \\ _/ __ \\ \\   __\\ /  _ \\     _/ __ \\ \\  \\/  /_/ __ \\ " << endl
			<< "|  Y Y  \\ / __ \\_ / /_/  >|   |  \\\\  ___/  |  |  (  <_> )    \\  ___/  >    < \\  ___/ " << endl
			<< "|__|_|  /(____  / \\___  / |___|  / \\___  > |__|   \\____/  /\\  \\___  >/__/\\_ \\ \\___  >" << endl
			<< "      \\/      \\/ /_____/       \\/      \\/                 \\/      \\/       \\/     \\/ " << endl;
		cout << "\n\n\n\n\n\n\n\n\t\t\t\tWaiting for process...\n";
		if (init == 1)
			cout << "\t\t\t\t[\\][|][/][-][\\][|]";
		if (init == 2)
			cout << "\t\t\t\t[|][/][-][\\][|][/]";
		if (init == 3)
			cout << "\t\t\t\t[/][-][\\][|][/][-]";
		if (init == 4) {
			cout << "\t\t\t\t[-][\\][|][/][-][\\]";
			init = 0;
		}

		Sleep(1);
	}
	oh.ClientDLL = oh.mem.Module(L"client.dll");
	oh.EngineDLL = oh.mem.Module(L"engine.dll");
	cout << "\nFound\n\n";

	oh.getOffsets();

	if (DEBUGMODE == 0 || DEBUGMODE == 4)
		oh.printDebug();

	return true;
}

void ConfigSetup()
{

	int LineNumber = 0;

	ifstream Config("C:\\magneto\\settings.cfg");
	if (!Config)
	{
		cout << endl;
		cout << "Creating Directory: C:\\magneto" << endl;
		CreateDirectoryW(L"C:\\magneto", nullptr);
		cout << "Creating config file: settings.cfg" << endl;
		ofstream WriteConfig("C:\\magneto\\settings.cfg");
		WriteConfig << "[magneto CONFIG]\n";
		WriteConfig << "Aim key=" << 1 << "\n";
		WriteConfig << "Aim key 2 (also triggerbot key)=" << 4 << "\n";
		WriteConfig << "RCS Scale (0/1/[2])=" << 2 << "\n";
		WriteConfig << "Smooth=" << 20 << "\n";
		WriteConfig << "Aimbot FOV=" << 1 << "\n";
		WriteConfig << "Stick to target enabled=" << 1 << "\n";
		WriteConfig << "targetbone=" << 6 << "\n";
		WriteConfig << "Visibility check=" << 0 << "\n\n\n";

		aimkey = 1;
		trigkey = 4;
		rcsscale = 2;
		smoothscale = 50;
		fovscale = 1;
		stickyenabled = 1;
		targetbone = 6;
		vischeck = 1;

		cout << "Config written successfully." << endl;
		cout << "Change settings @ 'C:\\magneto\\settings.cfg'" << endl << endl;
	}

	string line;
	while (getline(Config, line))
	{
		istringstream iss(line);
		string s;
		while (getline(iss, s, '='))
		{
			LineNumber++;

			switch (LineNumber)
			{
			case 3:
				aimkey = stoi(s.c_str());
				break;
			case 5:
				trigkey = stoi(s.c_str());
				break;
			case 7:
				rcsscale = stoi(s.c_str());
				break;
			case 9:
				smoothscale = stoi(s.c_str());
				m_AimTime = smoothscale;
				break;
			case 11:
				fovscale = stoi(s.c_str());
				break;
			case 13:
				stickyenabled = stoi(s.c_str());
				break;
			case 15:
				targetbone = stoi(s.c_str());
				break;
			case 17:
				vischeck = stoi(s.c_str());
				break;
			default:
				break;
			}
		}
	}
	Config.close();

	if (DEBUGMODE == -1)
		system("cls");
}

#pragma region functions

void fakelag()
{
	while (!KILLALL)
	{
		if (fakelagOn && !aimbotting && GetAsyncKeyState(0x56) && engine.GetSignOnState() == SIGNONSTATE_FULL)
		{
			oh.mem.Write(oh.EngineDLL + oh.m_bSendPackets, false);
			Sleep(20);
			oh.mem.Write(oh.EngineDLL + oh.m_bSendPackets, true);
			Sleep(2);
		}
		else
		{
			Sleep(12);
		}
	}
	oh.mem.Write(oh.EngineDLL + oh.m_bSendPackets, true);
	ExitThread(0);
}

void arc()
{
	Vector prevPunch;
	int prevShotsFired = 0;
	Vector finalVec;

	while (!KILLALL)
	{
		if (RecoilControl && !aimbotting)
		{
			if (me.GetShotsFired() <= 1)
			{
				prevPunch = 0;
				prevShotsFired = 0;
			}

			else if (me.GetShotsFired() > prevShotsFired)
			{
				finalVec = (me.GetPunch() - prevPunch) * 2.f;
				finalVec = me.currentangle - finalVec;

				SetAngle(finalVec);

				prevPunch = me.GetPunch();
				prevShotsFired = me.GetShotsFired();
			}
		}
		Sleep(12);
	}
}

void noflash()
{
	while (!KILLALL) {

		if (antiflash && engine.GetSignOnState() == SIGNONSTATE_FULL)
		{
			if (me.GetFlashDuration() > 0.f)
				oh.mem.Write<float>(me.dwBase + oh.m_flFlashDuration, 0.f);
		}
		Sleep(100);
	}
	ExitThread(0);
}

void aimbot() {

	int oldtarget = NULL;
	
	while (!KILLALL) {

		if (smoothscale < 1) smoothscale = 1;
		if (vischeck != 0 && vischeck != 1) vischeck = 1;

		
		if (aimbotOn && engine.GetSignOnState() == SIGNONSTATE_FULL) {

			// Resets best angle and best target 
			double bestangle = numeric_limits<double>::infinity();
			int besttarget = NULL;

			// For every entity
			for (int i = 0; i <= playerCount; i++) {
				// If player is alive,  is not on our team and is spotted by us (if smoothscale is not 1) then continue
				if (player[i].GetClassID() == CCSPlayer && !player[i].GetLifeState() && me.GetTeam() != player[i].GetTeam() && !player[i].GetDormant() && player[i].GetSpottedByMe()/* || vischeck == 0*/)//used to be vischeck == 0
				{
					Vector aimspot = player[i].GetBonePosition(targetbone);

					// Calculate angle with our own position and the enemy's bone position
					player[i].aimangle = Math::CalcAngle(me.GetVecOrigin(), aimspot);

					// Find the difference in X and Y vectors for current and aimbot angle
					Vector angledifference = engine.GetViewAngles() - player[i].aimangle;
					
					//clamp angles
					if (angledifference.y > 180) { angledifference.y -= 360; }
					if (angledifference.y < -180) { angledifference.y += 360; }

					// Uses Pythagoras' Theorem to find the total difference
					float pythagAngle = angledifference.getDistance();

					float YawDistance = sinf(Math::ToRadians(pythagAngle)) * Math::Get3dDistance(me.GetVecOrigin(), aimspot);

					// If the difference between current and aimbot angle is better for this entity than the current best then it becomes the current best
					if (YawDistance < bestangle && YawDistance < fovscale) {
						bestangle = YawDistance;
						if (besttarget != i)
						{
							besttarget = i;
						}
					}
				}
			}
			
			if (bestangle > fovscale || besttarget != oldtarget)
			{
				aimbotting = false;
				BaseTime = me.GetTicks();
				oldtarget = besttarget;
			}


			// If a target is found and we are alive when the aimbot key is pressed then aimbot the target
			if (besttarget != NULL && !me.GetLifeState()) 
			{
				WeaponType weptype = me.GetWeaponType();
				if (weptype != WEAPONTYPE_OTHER && weptype != WEAPONTYPE_SNIPER && !player[besttarget].GetLifeState() && player[besttarget].GetClassID() == CCSPlayer) { //if player doesnt have knife/nades/c4/etc out

					if (weptype != WEAPONTYPE_PISTOL) //no pistol RCS
					{
						// Modifies punch of local player by recoil modifiers (most servers require 2)
						rcsscale = 2;
						Vector MyPunch = me.GetPunch() * rcsscale;

						// Changes the aimangles by punch angles to compensate for recoil
						if (shotsFired <= 1)
						{
							lastShotsFired = 0;
						} 

						if (me.GetShotsFired() > lastShotsFired) {
							lastShotsFired = me.GetShotsFired();
							player[besttarget].aimangle -= MyPunch;
						}
					}

					// Move the view angle to the aimangles of target (if aimbot key is pressed)
					if ((GetAsyncKeyState(aimkey) || GetAsyncKeyState(trigkey)) && bestangle <= fovscale)
					{
						aimbotting = true;
						if (smoothscale > 1)
						{
							//Add on the time elapsed
							DeltaTime = me.GetTicks() - BaseTime;
							//Don't want to scale past 1
							if (DeltaTime > m_AimTime)
								DeltaTime = m_AimTime;

							Math::SmoothAngle(engine.GetViewAngles(), player[besttarget].aimangle.NormalizeAngle(), DeltaTime / m_AimTime);
						}
						else
						{
							SetAngle(player[besttarget].aimangle.NormalizeAngle());
						}
					}
					else
					{
						aimbotting = false;
						BaseTime = me.GetTicks();
					}
						
				}
				else
				{
					BaseTime = me.GetTicks();
				}
			}
			
		}
		Sleep(2);
	}
	ExitThread(0);
}

void triggerbot() 
{
	while (!KILLALL) 
	{
		if (triggerbotOn && aimbotting && GetAsyncKeyState(trigkey) && engine.GetSignOnState() == SIGNONSTATE_FULL)
		{
			Entity p;
			p.dwBase = me.GetCrosshairEntity();
			p.eb = oh.mem.Read<EntityBuffer>(p.dwBase);

			if (me.GetTeam() == p.GetTeam() && (p.GetTeam() == 2 || p.GetTeam() == 3) && me.GetWeaponType() != WEAPONTYPE_OTHER && p.GetClassID() == CCSPlayer)
				return;

			Vector bonecenter = p.GetBonePosition(BONE_HEAD); // Get the location of the headbone 
			Vector	bottomHitboxHead(bonecenter.x + -2.140f, bonecenter.y + -3.745f, bonecenter.z + -3.670f),
					topHitboxHead(bonecenter.x + 2.140f, bonecenter.y + 3.745f, bonecenter.z + 3.670f);

			// Get view direction 
			Vector viewDirection = Math::AngleToDirection(engine.GetViewAngles());
			// Start ray 
			Ray viewRay(me.GetVecOrigin(), viewDirection);
			float distance;
			if (viewRay.Trace(bottomHitboxHead, topHitboxHead, distance))
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL); //MOUSE1 DOWN
				Sleep(5);
				mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL); //MOUSE1 UP

				if (me.GetWeaponType() != WEAPONTYPE_PISTOL) {
					Sleep(100);
				}
				else
					Sleep(100);
			}

		}

		
		//If triggerbot is enabled and aimkey is pressed
		if (triggerbotOn && !aimbotting && GetAsyncKeyState(trigkey) && engine.GetSignOnState() == SIGNONSTATE_FULL)
		{
			int EnemyTeam = me.GetCrosshairEntityTeam();
			if (me.GetTeam() != EnemyTeam && (EnemyTeam == 3 || EnemyTeam == 2) && me.GetWeaponType() != WEAPONTYPE_OTHER && GetEntityFromDWORD(me.GetCrosshairEntity()).GetClassID() == CCSPlayer)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL); //MOUSE1 DOWN
				Sleep(5);
				mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL); //MOUSE1 UP

				if (me.GetWeaponType() != WEAPONTYPE_PISTOL) {
					Sleep(100);
				}
				else
					Sleep(100);
			}
		}
		Sleep(12);
	}
	ExitThread(0);
}

void hopper()
{
	while (!KILLALL) {
		if (bhopOn && GetAsyncKeyState(VK_SPACE) && engine.GetSignOnState() == SIGNONSTATE_FULL)
		{
			if (me.GetFlags() & FL_ONGROUND)
			{
				oh.mem.Write<int>(oh.ClientDLL + oh.m_dwForceJump, 5);
				Sleep(20);
				oh.mem.Write<int>(oh.ClientDLL + oh.m_dwForceJump, 4);
				Sleep(20);
			}
		}
		else Sleep(20);
	}
	ExitThread(0);
}

void glow()
{
	while (!KILLALL)
	{
		if (ESPOn && engine.GetSignOnState() == SIGNONSTATE_FULL)
		{

			// Get the glow pointer and glow object count
			DWORD dwGlow = oh.mem.Read<DWORD>(oh.ClientDLL + oh.m_dwGlowObject);
			int GlowObjectCount = oh.mem.Read<int>(oh.ClientDLL + oh.m_dwGlowObject + 0x4);

			// If the glow pointer is valid
			if (dwGlow != NULL) 
			{

				// For every object
				for (int i = 0; i < GlowObjectCount; i++) 
				{

					// Read its glow base and store in a GlowObject
					DWORD glowobject = dwGlow + i * sizeof(GlowObject);
					GlowObject object = oh.mem.Read<GlowObject>(glowobject);

					// Check if it's valid
					if (object.dwBase != NULL) 
					{
						//cout << "object.dwBase != NULL" << endl;

						// For every player
						for (int p = 0; p < playerCount; p++) 
						{

							// If the object is the same as a player they are thus a player
							if (object.dwBase == player[p].dwBase) 
							{

								// If the player is not on our team then set their colour like so depending on their health
								if (player[p].GetTeam() != me.GetTeam() && (player[p].GetClassID() == CCSPlayer || player[p].GetClassID() == CTEPlantBomb))
								{
									object.green = player[p].GetHealth() / 100.f;
									object.red = 1.f - object.green;
									object.blue = 0.f;
									object.alpha = 1.0f;
									object.renderoccluded = !player[p].GetDormant();
									object.rendernonoccluded = false;

									oh.mem.Write<GlowObject>(glowobject, object);
								}
							}
						}
					}
				}
			}
		}
		Sleep(30);
	}
	ExitThread(0);
}

void ranks()
{
	while (!KILLALL)
	{
		if (showRanks <= playerCount) {
			if ((player[showRanks].GetTeam() == 2 || player[showRanks].GetTeam() == 3) && !player[showRanks].GetLifeState()) 
			{
				string name = player[showRanks].GetName();
				cout << "Name: " << name << "\t" << MatchmakingRanks[player[showRanks].GetRank()] << endl;
			}
			showRanks++;
		}
	}
}

#pragma endregion

void KeyLoop()
{
	while (!KILLALL)
	{

		if (GetAsyncKeyState(VK_ESCAPE) < 0 && GetAsyncKeyState(0x56) < 0)
		{
			fakelagOn = !fakelagOn;

			cout << "fakelagOn = " << fakelagOn << endl;

			while (GetAsyncKeyState(VK_ESCAPE) < 0 && GetAsyncKeyState(0x56) < 0)
				Sleep(100);
		}

		if (GetAsyncKeyState(VK_HOME))
		{
			system("cls");
			showRanks = 0;

			while (GetAsyncKeyState(VK_HOME))
				Sleep(100);
		}

		
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F9))
		{
			while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F9))
			{
				Sleep(100);
			}
			KILLALL = true;
		}

		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F5))
		{
			ESPOn = !ESPOn;

			cout << "ESPOn = " << ESPOn << endl;

			while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F5))
				Sleep(100);
		}

		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F7))
		{
			aimbotOn = !aimbotOn;

			cout << "aimbotOn = " << aimbotOn << endl;

			while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F7))
				Sleep(100);
		}

		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F6))
		{
			triggerbotOn = !triggerbotOn;

			cout << "triggerbotOn = " << triggerbotOn << endl;

			while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F6))
				Sleep(100);
		}

		if (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(VK_F8) < 0)
		{
			bhopOn = !bhopOn;

			cout << "bhopOn = " << bhopOn << endl;

			while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_F8))
				Sleep(100);
		}


		if (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(VK_F3) < 0)
		{
			aimkey = 1;
			trigkey = 4;
			rcsscale = 2;
			smoothscale = 1;
			fovscale = 999999999;
			stickyenabled = 0;
			targetbone = 6;
			vischeck = 0;

			antiflash = true;

			cout << "RAGE" << endl;

			while (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(VK_F3) < 0)
				Sleep(100);
		}

		if (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(VK_F2) < 0)
		{
			aimkey = 1;
			trigkey = 4;
			rcsscale = 2;
			smoothscale = 3;
			fovscale = 999999999;
			stickyenabled = 0;
			targetbone = 6;
			vischeck = 1;

			antiflash = true;

			cout << "TEST RAGE" << endl;

			while (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(VK_F2) < 0)
				Sleep(100);
		}

		if (GetAsyncKeyState(VK_F8) < 0 && GetAsyncKeyState(VK_F5) < 0)
		{
			ConfigSetup();
			Sleep(200);
		}
		Sleep(50);
	}
	ExitThread(0);
}

void ReadEntity()
{

	while (!KILLALL)
	{

		me.dwBase = oh.mem.Read<DWORD>(oh.ClientDLL + oh.m_dwLocalPlayer);
		me.eb = oh.mem.Read<EntityBuffer>(me.dwBase);

			for (int i = 0; i < playerCount; i++)
			{
				player[i].dwBase = oh.mem.Read<DWORD>(oh.ClientDLL + oh.m_dwEntityList + i * oh.EntLoopDist);
				player[i].eb = oh.mem.Read<EntityBuffer>(player[i].dwBase);
				
			}

		engine.eb = oh.mem.Read<EngineBuffer>(oh.dwEngine);

		Sleep(5);
	}
	ExitThread(0);
}

int main()
{
	system("COLOR 3F");

	initialize();
	ConfigSetup();


	thread	Second(ReadEntity),
			Third(aimbot), Fourth(glow), Fifth(hopper),
			Sixth(KeyLoop), Seventh(triggerbot), 
			Eighth(noflash), Ninth(arc), Tenth(fakelag), Eleventh(ranks);

	Sleep(100);
	Second.join();
	Sleep(500);
	Third.join();
	Fourth.join();
	Fifth.join();
	Sixth.join();
	Seventh.join();
	Eighth.join();
	Tenth.join();
	Eleventh.join();

	
	return 0;
}