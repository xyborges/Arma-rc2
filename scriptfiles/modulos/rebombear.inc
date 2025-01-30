#include <YSI-Includes\YSI_Coding\y_hooks>

static const Float:posrebombear[][] = {
	{0.0,0.0,0.0},
	{306.81555, 2029.86719, 16.62395},
	{-1423.39502, 495.93646, 17.22529},
	{-244.31578, 2717.72900, 61.68380} // hms
};
hook OnGameModeInit(){
	for(new i; i < sizeof posrebombear; i++){
		if(posrebombear[i][0] == 0) continue;
		CreateDynamic3DTextLabel("{33ccff}REABASTECER BOMBAS\nN", -1, posrebombear[i][0],posrebombear[i][1],posrebombear[i][2], 60.0);//, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
	}
	return 1;
}
hook OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys){
	if((newkeys == KEY_NO)){
		new pveh = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(pveh) == RUSTLER || GetVehicleModel(pveh) == ANTI_AEREA ){
			for(new i; i < sizeof posrebombear; i++){
				if(IsPlayerInRangeOfPoint(playerid, 5.0, posrebombear[i][0],posrebombear[i][1],posrebombear[i][2])){
					if(VehInfo[pveh][Bombas] < 6 || VehInfo[pveh][Misseis] < 10 ){
						TogglePlayerControllable(playerid, false);
						SendClientMessage(playerid, cor, "Reabastecendo de bombas e misseis...");
						Sleep(4);
						VerificarBombas(pveh);
						TogglePlayerControllable(playerid, true);
						SendClientMessage(playerid, cor, "O Veiculo foi reabastecido com explosivos.");
					}
					else{
						SendClientMessage(playerid, cor, "Voce nao precisa reabastecer de explosivos este veiculo.");
					}
				}
			}
		}
	}
	return 1;
}

hook OnVehicleDeath(vehicleid, killerid){
	VehInfo[vehicleid][Bombas] = 0;
	VehInfo[vehicleid][Misseis] = 0;
	return 1;
}