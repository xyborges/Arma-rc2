
cmd:dominar(playerid){
	if(dominador[playerid] != -1) return SendClientMessage(playerid, cor, "Voce nao pode dominar outro territorio.");
	for(new i; i <178; i ++){
		if(IsPlayerInGangZone(playerid, GzDom[i][gz])){
			if(GzDom[i][donogz] == PlayerInfo[playerid][time]) return SendClientMessage(playerid, cor, "Este gangzone ja e do seu time.");
			if(IsGangZoneFlashingForPlayer(playerid, GzDom[i][gz])) return SendClientMessage(playerid, cor, "Ja estao dominando este territorio.");
			GzDom[i][dominando] = PlayerInfo[playerid][time];
			GangZoneFlashForAll(GzDom[i][gz], CorGangZone(PlayerInfo[playerid][time]));
			SendClientMessageToAll(CorGangZone(PlayerInfo[playerid][time]), "%s esta tomando um territorio.", nome(playerid));
			SetTimerEx("dominargz", 30000, false, "siii", nome(playerid), PlayerInfo[playerid][time], playerid, i);
			AdicionarPontos(GzDom[i][donogz], -1);
			SendClientMessage(playerid, cor, "Fique no gangzone ate o final.");
			dominador[playerid] = i;
			break;
		}
	}
	return 1;
}
cmd:skin(playerid, params[]){
	
}
cmd:meuid(playerid){
	SendClientMessage(playerid, cor, "%d id", GetIDByName(nome(playerid)));
	return 1;
}
cmd:squads(playerid) return MostrarSquads(playerid);
cmd:irla(playerid) return SetPlayerPos(playerid, 34.71440, 2390.11548, 9165.39551);
cmd:ajuda(playerid){
	ShowPlayerDialog(playerid, DIALOG_AJUDA, DIALOG_STYLE_MSGBOX, "{fff000}Dialog de Ajuda", "{fff000}Os seguintes comandos existem:\n\
		{33ccff}/ajuda\
		\n/trocartime\
		\n/arma\
		\n/info", "Ok", #);
	return 1;
}
cmd:pxveiculo(playerid){
	if(IsValidVehicle(moto[playerid])){
		if(IsVehicleOccupied(moto[playerid])) return SendClientMessage(playerid, cor, "#ARMA Seu veiculo esta sendo usado, não pode ser puxado.");	
		PuxarMoto(playerid);
	}	
	else
		SendClientMessage(playerid, cor, "#ARMA Seu veiculo não foi criado.");
	return 1;
}
cmd:info(playerid, params[]){
	new id;
	if(sscanf(params, "i", id)) return SendClientMessage(playerid, cor, "#ARMA /info [ id ]");
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, cor, "#ARMA Jogador offline.");
	SendClientMessage(playerid, cor, "#ARMA %s possui %d kills, %d mortes e um kd de %0.1f!", nome(id), PlayerInfo[id][Kills], PlayerInfo[id][Mortes], float(PlayerInfo[id][Kills]) / float(PlayerInfo[id][Mortes]));
	return 1;
}
cmd:trocartime(playerid){
	static tempfo;
	if(tempfo < gettime()){ 
		tempfo = gettime() +  60 * 5;
		AbrirSelecao(playerid);
	}
	else
		SendClientMessage(playerid, cor, "Aguarde %d segundos para trocar novamente.", (tempfo - gettime()));

	return 1;
}
public OnPlayerCommandReceived(playerid, cmd[], params[], flags){
	if(flags != 0 && !(flags & PlayerInfo[playerid][CMDPERM])){
		SendClientMessage(playerid, cor, "#ARMA Você não possui permissão para utilizar o comando.");
		return 0;
	}
	return 1;
}
public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if(!IsPlayerSpawned(playerid)) return 1;

	if(result == -1){
		SendClientMessage(playerid, cor, "Você digitou um comando que não existe.");
	}
	return 1;
}