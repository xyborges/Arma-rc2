new moto[MAX_PLAYERS];

CriarMoto(playerid, const params[]){
	new Float: x, Float: y, Float: z, Float:angle;
	GetPlayerFacingAngle(playerid, angle);
	GetPlayerPos(playerid, x, y, z);

	if(isnull(params))
		moto[playerid] = CriarVeiculo(PlayerInfo[playerid][time], 468, x, y, z, angle, random(20), random(20), -1);//, respawnDelay, bool:addSiren = false)
	else{
		moto[playerid] = CriarVeiculo(PlayerInfo[playerid][time],strval(params), x, y, z, angle, random(20), random(20), -1);
		
	}
	SendClientMessage(playerid, cor, "#ARMA Veículo criado.");
}
DestruirMoto(playerid){
	if(IsValidVehicle(moto[playerid])){
		DestroyVehicle(moto[playerid]);
		moto[playerid] = -1;
		return true;
	}
	return false;
}
PuxarMoto(playerid){
	new Float: x, Float: y, Float: z;
	GetPlayerPos(playerid, x, y, z);
	SetVehiclePos(moto[playerid], x, y, z);
	return 1;
}