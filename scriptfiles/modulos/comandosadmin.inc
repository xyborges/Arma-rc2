flags:gmx(DONO)
cmd:gmx(playerid){
	SendClientMessageToAll(cor_cinza, "#ARMA Dono %s reiniciou o servidor.", nome(playerid));
	SendRconCommand("gmx");
	return 1;
}

cmd:minhapos(playerid){
	new Float: x, Float: y, Float: z;
	GetPlayerPos(playerid, x, y ,z);
	SendClientMessage(playerid, -1, "%f %f %f", x, y, z);
	return 1;
}
flags:ca(HELPER | ADMIN | DONO)
cmd:ca(playerid, params[]){
	new string[144];
	format(string, sizeof string, "[CA] (%d)%s: {ffffff}%s",playerid, nome(playerid), params);
	SendAdminsMessage(cor_cinza, string);
	return 1;
}
flags:veiculo(HELPER | ADMIN | DONO)
cmd:veiculo(playerid, params[]){
	if(!IsValidVehicle(moto[playerid])){
		CriarMoto(playerid, params);
	}
	else{
		DestruirMoto(playerid);
		SendClientMessage(playerid, cor, "#ARMA Veiculo destruido.");
	}
	
	return 1;
}
flags:spectar(HELPER | ADMIN | DONO)
cmd:spectar(playerid, params[]){
	PlayerSpectatePlayer(playerid, strval(params));
	return 1;
}
flags:daradmin(DONO)
cmd:daradmin(playerid, params[]){
	new id, admin;
	if(sscanf(params, "ii", id, admin)) return SendClientMessage(playerid, cor, "#ARMA /daradmin [ id ] [ 0-3 ]");
	if(0 < admin > 3) return SendClientMessage(playerid, cor, "#ARMA o nivel de admin está acima de 3 ou abaixo de 0.");
	if(!IsPlayerConnected(id) || !IsPlayerSpawned(id)) return SendClientMessage(playerid, cor, "#ARMA O Jogador está offline ou não está spawnado.");
	if(id == playerid) return SendClientMessage(playerid, cor, "#ARMA Você não pode fazer isso.");		

	new string[144];
	if(admin == 0){
		PlayerInfo[id][Admin] = 0;
		PlayerInfo[id][CMDPERM] = 0;
		
		format(string, sizeof string, "#ARMA_ADMINISTRACAO %s removeu o admin de %s!", nome(playerid), nome(id));
		SendAdminsMessage(cor_cinza, string);

		format(string, sizeof string, "#ARMA_ADMINISTRACAO %s removeu você da staff.", nome(playerid));
		SendClientMessage(id, cor_cinza, string);
	}
	else{
		PlayerInfo[id][Admin] = admin;
		PlayerInfo[id][CMDPERM] = 1 << PlayerInfo[id][Admin]-1;	
		format(string, sizeof string, "#ARMA_ADMINISTRACAO %s adicionou o admin %s!", nome(playerid), nome(id));
		SendAdminsMessage(cor_cinza, string);
		SendClientMessage(id, cor_cinza, "#ARMA Seja bem-vindo!");
	}


	SalvarConta(id);
	return 1;
}