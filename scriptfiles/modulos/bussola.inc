convertNAME(const Float:rz){

	static retstr[15];
	if(rz >= 348.75 || rz < 11.25) retstr = "Norte";
	else if(rz >= 326.25 && rz < 348.75) retstr = "Nor-Nordeste";
	else if(rz >= 303.75 && rz < 326.25) retstr = "Nordeste";
	else if(rz >= 281.25 && rz < 303.75) retstr = "Leste-Nordeste";
	else if(rz >= 258.75 && rz < 281.25) retstr = "Leste";
	else if(rz >= 236.25 && rz < 258.75) retstr = "Leste-Sudeste";
	else if(rz >= 213.75 && rz < 236.25) retstr = "Sudeste";
	else if(rz >= 191.25 && rz < 213.75) retstr = "Sul-Sudeste";
	else if(rz >= 168.75 && rz < 191.25) retstr = "Sul";
	else if(rz >= 146.25 && rz < 168.75) retstr = "Sul-Sudoeste";
	else if(rz >= 123.25 && rz < 146.25) retstr = "Sudoeste";
	else if(rz >= 101.25 && rz < 123.25) retstr = "Oeste-Sudoeste";
	else if(rz >= 78.75 && rz < 101.25) retstr = "Oeste";
	else if(rz >= 56.25 && rz < 78.75) retstr = "Oeste-Noroeste";
	else if(rz >= 33.75 && rz < 56.25) retstr = "Noroeste";
	else if(rz >= 11.5 && rz < 33.75) retstr = "Nor-Noroeste";
	return retstr;
}
function attbussola(playerid){
	if(IsPlayerSpawned(playerid)){
		PlayerTextDrawSetString(playerid, Bussola[playerid][0], "%s",convertNAME(GetCameraAngle(playerid)));
		PlayerTextDrawShow(playerid, Bussola[playerid][0]);
	}
}