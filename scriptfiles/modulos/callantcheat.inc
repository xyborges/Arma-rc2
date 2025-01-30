#include <fakekill>
#include <rapidfire>
/*public OnPlayerSpamCars(playerid, number){
	SendClientMessageToAll(cor, "#ARMACHEAT %s foi kickado por suspeita de Spam Car.", nome(playerid));
	Kick(playerid);
	return 1;
}*/
public OnPlayerCarTroll(playerid, vehicleid, trolledid, trolltype){
	SendClientMessageToAll(cor, "#ARMACHEAT %s foi kickado por suspeita de Car Troll.", nome(playerid));
	Kick(playerid);
	return 1;
}
public OnPlayerFakeKill(playerid, spoofedid, spoofedreason, faketype){
	
	SendClientMessageToAll(cor, "#ARMACHEAT %s foi kickado por suspeita de Fake Kill.", nome(playerid));
	Kick(playerid);
	return 1;	
}
public OnPlayerGunCheat(playerid, weaponid, ammo, hacktype){
	if(hacktype == 3 || hacktype == 2){ // mun inf
		SendClientMessageToAll(cor, "#ARMACHEAT %s foi kickado por suspeita de Munição Infinita.", nome(playerid));
		Kick(playerid);
	}
	if(hacktype == 1){ // mun inf
		SendClientMessageToAll(cor, "#ARMACHEAT %s foi kickado por suspeita de Weapon Cheat", nome(playerid));
		Kick(playerid);
	}
	return 1;		
}
public OnPlayerJetpackCheat(playerid){
	SendClientMessageToAll(cor, "#ARMACHEAT %s foi kickado por suspeita de Jetpack Hack.", nome(playerid));
	Kick(playerid);
	return 1;		
}
public OnPlayerAirBreak(playerid){
	if(PlayerInfo[playerid][Admin] == 3) return 1;
	
	SendClientMessageToAll(cor, "#ARMACHEAT %s foi kickado por suspeita de Air Break.", nome(playerid));
	Kick(playerid);
	return 1;	
}
public OnAntiCheatFireRate(playerid, weaponid, interval){
	if(WEAPON:weaponid == WEAPON_DEAGLE && interval < 200){
		SendClientMessageToAll(cor, "#ARMACHEAT %s foi kickado apos 3 avisos de Rapid Fire ou C-BUG.", nome(playerid));
		Kick(playerid);		
	}
	return 1;
}