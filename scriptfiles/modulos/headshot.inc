hook OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart){
	if(JogadorCongelado[damagedid]) return 1;

	if(bodypart == 9 && !JogadorCongelado[damagedid]){
		GameTextForPlayer(damagedid,"~R~HEADSHOT", 5000, 6);
		GameTextForPlayer(playerid,"~R~HEADSHOT", 5000, 6);//, OPEN_MP_TAGS:...)
		new Float:h;
		GetPlayerHealth(damagedid, h);
		if(h < 26.0){
			SetPlayerHealth(playerid, 0);
		
		}
		else
			SetPlayerHealth(damagedid, h - 25.0);
	
		new Float: x, Float: y, Float: z;
		GetPlayerPos(playerid, x, y, z);
		PlayerPlaySound(playerid, 139,x, y, z);
	}
	return 1;
}
hook OnPlayerDeath(playerid, killerid, reason){
	morto[playerid] = true;

	if(killerid != INVALID_PLAYER_ID){
		if(PlayerInfo[playerid][time] == PlayerInfo[killerid][time]){
			PlayerInfo[killerid][Mortes] ++;
			PlayerInfo[playerid][Mortes] --;
			SendClientMessageToAll(cor, "%s cometeu TK em %s e perdeu k/d.", nome(killerid), nome(playerid));
			PlayerInfo[killerid][Dinheiro] -= 100;
			AdicionarPontos(PlayerInfo[playerid][time], -1);
		}
		else{
			AdicionarPontos(PlayerInfo[killerid][time], 1);

			PlayerInfo[killerid][Kills] ++;
			PlayerInfo[killerid][Dinheiro] += 100;

			CheckSequencia(killerid, AUMENTAR_SEQUENCIA);
		}
	}else{
		new id = random(sizeof nomesfracos);
		SendClientMessageToAll(GetPlayerColor(playerid), "#ARMA O %s %s conseguiu morrer sozinho kkkkkk.", nomesfracos[id], nome(playerid));//, nome(playerid));		
	}

	PlayerInfo[playerid][Mortes] ++;
	SendDeathMessage(killerid, playerid, reason);
	CheckSequencia(playerid, ZERAR_SEQUENCIA);
	return 1;
}