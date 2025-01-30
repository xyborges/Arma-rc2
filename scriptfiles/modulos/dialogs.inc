enum {
	COMANDO_UM,SEM_COMANDO
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	switch(dialogid){
		case DIALOG_SELECT_SQUAD:{
			if(response){
				if(listitem >= 0){
					new squad = listitem+1, ddorg = PlayerInfo[playerid][time];
					if(GetSquadDisponivel(squad, ddorg) != 5){

						PlayerInfo[playerid][Squad] = squad;
						SendClientMessage(playerid,cor, "Voce entrou no squad %s", GetSquadName(squad));
					}
					else{
						SendClientMessage(playerid, 0xff0000ff, "O Squad lotou antes de voce entrar!");
						MostrarSquads(playerid);
					}
				}
			}
			else 
				MostrarSquads(playerid);
		}
		case DIALOG_REGISTRO:{
 			if(response){
 				if(isnull(inputtext))
 					return SendClientMessage(playerid, cor, "Por favor, escreva algo no campo da senha.");

 				bcrypt_hash(playerid,"OnPassswordHash",inputtext,BCRYPT_COST);
 			}
 			else
 				Kick(playerid);
		}
		case DIALOG_LOGIN:{
			if(response){
				new DBResult:R;
				
				R = DB_ExecuteQuery(Data, "SELECT * FROM `Contas` WHERE `user` = '%d'", GetPlayerUser(playerid));
				
				if(DB_GetRowCount(R)){ 
					new string[BCRYPT_HASH_LENGTH];
					DB_GetFieldStringByName(R, "Senha", string, sizeof string);
					
					bcrypt_verify(playerid,"OnPassswordVerify",inputtext,string);
				}
				DB_FreeResultSet(R);
			}
			else
				Kick(playerid);
		}
		case DIALOG_SELECT_EXE:{
			if(response){
				switch(listitem){
				}
			}
			else
				Kick(playerid);
		}

		case DIALOG_ESCOLHEREXE:{
			if(response){
				SendClientMessage(playerid, cor, "#ARMA Você definiu seu Exercito.");
				switch(listitem){
					case 0:{
						PlayerInfo[playerid][Classe] = NENHUM;
						PlayerInfo[playerid][Squad] = NENHUM_SQUAD;
						PlayerInfo[playerid][time] = HAMAS;
						AbrirSpawns(playerid, HAMAS);
					}
					case 1:{
						PlayerInfo[playerid][Classe] = NENHUM;
						PlayerInfo[playerid][Squad] = NENHUM_SQUAD;
						PlayerInfo[playerid][time] = EXERCITO_DE_ISRAEL;
						AbrirSpawns(playerid, EXERCITO_DE_ISRAEL);
					}
				}
			}
			else{
				AbrirKick(playerid, SEM_COMANDO);
			}
		}
	}
	return 1;
}
Toggle(playerid){
	TogglePlayerSpectating(playerid, true);
	TogglePlayerSpectating(playerid, false);
}
forward OnPassswordVerify(playerid,bool:success);
public OnPassswordVerify(playerid,bool:success){
	
	if(success){
		AbrirSelecao(playerid);
		CarregarConta(playerid);
		PlayerInfo[playerid][logado] = true;
	}
	else{
		SendClientMessage(playerid, cor, "Você não digitou corretamente sua senha.");
		IniciarLogin(playerid);
	}
	return 1;
}
forward OnPassswordHash(playerid,hashid);
public OnPassswordHash(playerid,hashid){
	new dest[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(dest);

	DB_ExecuteQuery(Data, "INSERT INTO `Contas` (`Nome`, `Senha`) VALUES ('%q', '%q')", nome(playerid), dest);
	SendClientMessage(playerid, cor, "A Sua conta foi registrada.");

	PlayerInfo[playerid][logado] = true;
	CarregarConta(playerid);

	AbrirSelecao(playerid);
}
AbrirSelecao(playerid){
	ShowPlayerDialog(playerid, DIALOG_ESCOLHEREXE, DIALOG_STYLE_LIST, "{33ccff}Escolha seu time", "{ff0000}Hamas\n{005EB8}Exercito de Israel", "Selecionar", #);
}
AbrirKick(playerid, type = 0){

	static cmd;

	switch(cmd){
		case COMANDO_UM:{
			cmd = type;	
		}
		case SEM_COMANDO:{
			cmd = type;	
			ShowPlayerDialog(playerid, DIALOG_QUEROKICK, DIALOG_STYLE_MSGBOX, "{ff0000}Importante", "{fff000}Você deseja ser Kickado?", "Sim", "Nao");
		}
	}
	return 0;
}