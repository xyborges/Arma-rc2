#include <YSI-Includes\YSI_Coding\y_hooks>
enum{
	NENHUM,
	SOLDADO,
	SNIPER,
	SUPORTE,
	MEDICO,
	CAPITAO,
	MAX_CLASSES
}
GetClassName(class){
	static string[8];
	string[0] = EOS;

	switch(class){
		case SOLDADO: string = "Soldado";
		case SNIPER: string = "Sniper";
		case SUPORTE: string = "Suporte";
		case MEDICO: string = "Medico";
		case CAPITAO: string = "Capitao";
	}
	return string;
}
function ArmarPorClasse(playerid, bool:armar){
	if(!armar){
		ResetPlayerWeapons(playerid);
		SetPlayerArmour(playerid, 50.0);
		switch(PlayerInfo[playerid][Classe]){
			case SOLDADO:{
				GivePlayerWeapon(playerid, WEAPON:24, 60);
				GivePlayerWeapon(playerid, WEAPON:31, 350);
			}
			case SNIPER:{
				GivePlayerWeapon(playerid, WEAPON:WEAPON_TEARGAS, 1);
				GivePlayerWeapon(playerid, WEAPON:24, 80);
				GivePlayerWeapon(playerid, WEAPON:WEAPON_SNIPER, 150);
			}
			case SUPORTE:{
				GivePlayerWeapon(playerid, WEAPON:WEAPON_ROCKETLAUNCHER, 1);
				GivePlayerWeapon(playerid, WEAPON:16, 2);
				GivePlayerWeapon(playerid, WEAPON:WEAPON_M4, 300);
				GivePlayerWeapon(playerid, WEAPON:WEAPON_THERMAL_GOGGLES, 1);
				GivePlayerWeapon(playerid, WEAPON:WEAPON_SHOTGSPA, 40);
			}
			case MEDICO:{
				GivePlayerWeapon(playerid, WEAPON:31, 300);
				GivePlayerWeapon(playerid, WEAPON:24, 50);
				GivePlayerWeapon(playerid, WEAPON:WEAPON_UZI, 140);
			}
			case CAPITAO:{
				GivePlayerWeapon(playerid, WEAPON:WEAPON_THERMAL_GOGGLES, 1);
				SetPlayerArmour(playerid, 100.0);
				GivePlayerWeapon(playerid, WEAPON:WEAPON_M4, 400);
				GivePlayerWeapon(playerid, WEAPON:24, 70);
				GivePlayerWeapon(playerid, WEAPON:WEAPON_MP5, 150);
			}
		}
	}
	else{
		static WEAPON: weap[MAX_WEAPON_SLOTS] = WEAPON:0, ammo[MAX_WEAPON_SLOTS]= 0;
		for(new WEAPON_SLOT:i; i < MAX_WEAPON_SLOTS; i++){

			GetPlayerWeaponData(playerid, i, weap[i], ammo[i]);
			if(weap[i] == WEAPON_TEARGAS || weap[i] == WEAPON_GRENADE || weap[i] == WEAPON_ROCKETLAUNCHER || weap[i] == WEAPON_MOLOTOV)
				GivePlayerWeapon(playerid, weap[i], 1);
			else
				if(weap[i] != WEAPON:0)
					GivePlayerWeapon(playerid, weap[i], 25);	
		}

	}
	return 1;
}