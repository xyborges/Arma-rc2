#include <YSI-Includes\YSI_Coding\y_hooks>

forward OnPlayerChangeWeapon(playerid, WEAPON:are, WEAPON:was);
static
	WEAPON:armapassada[MAX_PLAYERS];

CheckChangeWeapon(playerid){
	if( (GetPlayerWeapon(playerid) == WEAPON:0 && GetPlayerWeapon(playerid) != armapassada[playerid]) || GetPlayerWeapon(playerid) != WEAPON:armapassada[playerid]){ 
		CallRemoteFunction("OnPlayerChangeWeapon", "iii", playerid, GetPlayerWeapon(playerid), armapassada[playerid]);
		
	}
	else
		armapassada[playerid] = GetPlayerWeapon(playerid);
}
hook OnPlayerChangeWeapon(playerid, WEAPON:are, WEAPON:was){
	/*HideProgressTemp(playerid);
	if(GetPlayerWeapon(playerid) >= WEAPON:22){
		SetPlayerProgressBarMaxValue(playerid, barra[playerid], GetWeaponLimit(are-WEAPON:22));
		ShowProgressTemp(playerid);
		SetPlayerProgressBarValue(playerid, barra[playerid], PlayerLimite[playerid][are - WEAPON:22]);

	}*/

	return 1;
}