#include <YSI-Includes\YSI_Coding\y_hooks>
new Iterator:Vehicles<MAX_VEHICLES>;
enum enumv{
	Org, CaixasMunicao, Bombas, Misseis, Anti_Aerea
}
new VehInfo[MAX_VEHICLES][enumv];
function VerificarBombas(veh){
	switch(GetVehicleModel(veh)){
		case BARRACKS: VehInfo[veh][CaixasMunicao] = 2;
		case RUSTLER:{
			VehInfo[veh][Bombas] = 5;
			VehInfo[veh][Misseis] = 10;
		}
		case ANTI_AEREA:{
			VehInfo[veh][Misseis] = 5;
		}
		default:{
			VehInfo[veh][Bombas] = 0;
			VehInfo[veh][Misseis] = 0;
			VehInfo[veh][CaixasMunicao] = 0;			
		}
	}
	return 1;
}
function DestruirVeiculo(vehicleid){
	if(IsValidVehicle(vehicleid)){
		DestroyVehicle(vehicleid);
		VehInfo[vehicleid][Org] = 0;
		Iter_Remove(Vehicles, vehicleid);
		return 1;
	}
	return 0;
}
forward CriarVeiculo(orgid, modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2, respawnDelay);
public CriarVeiculo(orgid, modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2, respawnDelay){ 
	new veh = CreateVehicle(modelid, spawnX, spawnY, spawnZ, angle, colour1, colour2, respawnDelay);
	Iter_Add(Vehicles, veh);
	SetVehicleRespawnDelay(veh, -1);
	VerificarBombas(veh);
	VehInfo[veh][Org] = orgid;
	if(modelid == ANTI_AEREA){
		VehInfo[veh][Anti_Aerea] = CreateDynamicObject(3267, 0.0,0.0,0.0,0.0,0.0,0.0);//, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
		AttachDynamicObjectToVehicle(VehInfo[veh][Anti_Aerea], veh, 0.000000,-1.875000,-0.524999,0.000000,0.000000,0.000000);
		
	}
	return veh;
}
hook OnVehicleSpawn(vehicleid){
	VerificarBombas(vehicleid);
	return 1;
}
hook OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate){
	if(newstate == PLAYER_STATE_DRIVER){
		new pveh = GetPlayerVehicleID(playerid);

		if(GetVehicleModel(pveh) == BARRACKS)
			SendClientMessage(playerid, cor, "Total de caixas de municao ainda neste veiculo: %d", VehInfo[pveh][CaixasMunicao]);
		
		if(GetVehicleModel(pveh) == RUSTLER)
			SendClientMessage(playerid, cor, "Total de Misseis e Bombas ainda neste veiculo: %d & %d", VehInfo[pveh][Misseis], VehInfo[pveh][Bombas]);
		
		if(GetVehicleModel(pveh) == ANTI_AEREA)
			SendClientMessage(playerid, cor, "Total de misseis ainda neste veiculo: %d", VehInfo[pveh][Misseis]);
		
	}
}
hook OnVehicleDeath(vehicleid, killerid){
	new playerid = killerid;
	if(killerid == INVALID_PLAYER_ID) return 1;

	if(VehInfo[vehicleid][Org] == PlayerInfo[playerid][time])
		AdicionarPontos(PlayerInfo[playerid][time], -1);
	else{
		AdicionarPontos(PlayerInfo[playerid][time], 1);
		AdicionarPontos(VehInfo[vehicleid][Org], -1);
	}
	return 1;
}