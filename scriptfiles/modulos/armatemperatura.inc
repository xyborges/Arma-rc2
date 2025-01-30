#include <YSI-Includes\YSI_Coding\y_hooks>

new PlayerBar:barra[MAX_PLAYERS];

static limitetiros[] = {
	
	5, // 22 M9 
	5, // 23 M9 SD
	3, // 24 Desert 

		// Shotgun
	5, // 25 Shotgun
	5, // 26 Sawnoff 
	5, // 27 Spas 12

		// Automatic
	7, // 28 Mac 10
	7, // 29 MP5
	8, // 30 AK-47
	8, // 31 M16
	7, // 32 Tec 9 

		// Rifle
	3, // 33 Rifle
	3, // 34 Sniper

		// Heavy
	2, // 35 RPG
	2, // 36 Heatseeker
	2, // 37 Flamer
	25// 38 Minigun

};	
new PlayerLimite[MAX_PLAYERS][25];
new timerbala[MAX_PLAYERS][25];
forward diminuirtemperatura(playerid, WEAPON:weapon);
public diminuirtemperatura(playerid, WEAPON:weapon){
	if(PlayerLimite[playerid][weapon] == 0) return KillTimer(timerbala[playerid][weapon]);
	PlayerLimite[playerid][weapon] -= 1;
	SetPlayerProgressBarValue(playerid, barra[playerid], PlayerLimite[playerid][weapon]);
	if(weapon+WEAPON:22 == GetPlayerWeapon(playerid))
		ShowProgressTemp(playerid);
	else
		HideProgressTemp(playerid);

	return 1;
}
GetWeaponTemp(playerid, weapon)
	return PlayerLimite[playerid][weapon];
GetWeaponLimit(weapon)
	return limitetiros[weapon];
ShowProgressTemp(playerid)
	return ShowPlayerProgressBar(playerid, barra[playerid]);
HideProgressTemp(playerid)
	return HidePlayerProgressBar(playerid, barra[playerid]);

CriarBarraTemperatura(playerid){
	if(!IsValidPlayerProgressBar(playerid, barra[playerid])){
		barra[playerid] = CreatePlayerProgressBar(playerid, 547.000000, 128.000000, 62.000000, 4.000000, -16776961, 100.000000, 0);
		SetPlayerProgressBarValue(playerid, barra[playerid], 0.0);
	}
}
ResetTemperatura(playerid){
	for(new i; i < 25; i++)
		PlayerLimite[playerid][i] = 0;

	for(new i; i < 25; i++){
		if(IsValidTimer(timerbala[playerid][i]))
			KillTimer(timerbala[playerid][i]);
	}

	SetPlayerProgressBarValue(playerid, barra[playerid], 0.0);
	HideProgressTemp(playerid);
}/*
hook OnPlayerWeaponShot(playerid, weaponid, BULLET_HIT_TYPE:hittype, hitid, Float:fX, Float:fY, Float:fZ){
	if(GetPlayerWeapon(playerid) >= WEAPON:WEAPON_COLT45){ // ter certeza de que estou tratando com uma arma que está na array de temperatura
		new WEAPON:weap = WEAPON:weaponid - WEAPON:22;
		// caso o jogador dispare novamente e o timer ja exista ( no caso de uma arma automática, por exemplo) o timer é destruido e recriado ( como se fosse necesário um 'tempo' para a arma esfriar)
		if(IsValidTimer(timerbala[playerid][weap])) KillTimer(timerbala[playerid][weap]);

		timerbala[playerid][weap] = SetTimerEx("diminuirtemperatura", 1102, true, "ii", playerid, weap);
		
		if(GetWeaponTemp(playerid, weap) >= GetWeaponLimit(weap)){
			if(GetPlayerState(playerid) != PLAYER_STATE_PASSENGER){
				Congelar(playerid, 480);
				PlayerLimite[playerid][weap] = GetWeaponLimit(weap);
				SendClientMessage(playerid, cor, "Sua arma esquentou, Aguarde alguns segundos.");
				SetPlayerProgressBarMaxValue(playerid, barra[playerid], GetWeaponLimit(weap));
				return 0;
			}
		}
		else{
			PlayerLimite[playerid][weap]++;
			SetPlayerProgressBarValue(playerid, barra[playerid], PlayerLimite[playerid][weap]);
		}
	} 
	return 1;
}*/