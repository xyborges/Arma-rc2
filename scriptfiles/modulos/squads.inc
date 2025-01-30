enum{
	NENHUM_SQUAD,
	ALPHA,
	BRAVO,
	CHARLIE,
	DELTA,
	ECHO,
	MAX_SQUADS
}
enum{
	LABEL_SQUAD_CRIAR = 1,
	LABEL_SQUAD_DELETAR
}
GetSquadName(squad){
	static string[8];
	switch(squad){
		case ALPHA:  string = "Alpha";
		case BRAVO:  string ="Bravo";
		case CHARLIE:  string ="Charlie";
		case DELTA:  string ="Delta";
		case ECHO:  string = "Echo";
		default:  string ="Nenhum";
	}
	return string;
}
GetMembersInSquad(squad, orgd){
	new contar;
	foreach(new i: Player){
		if(PlayerInfo[i][Squad] == squad && PlayerInfo[i][time] == orgd)
			contar++;
	}
	return contar;
}
GetSquadDisponivel(sqd, orgd){
	new contar;
	foreach(new i: Player){
		if(PlayerInfo[i][Squad] == sqd && PlayerInfo[i][time] == orgd)
			contar++;
	}
	if(contar == 5) return true;
	else return false;	
}
HasClassInSquad(class, sqd, orgd){
	new bool: retorno = false;
	foreach(new i: Player){
		if(PlayerInfo[i][Squad] == sqd && PlayerInfo[i][time] == orgd){
			if(PlayerInfo[i][Classe] == class){
				retorno = true;
				break;
			}
		}
	}
	return retorno;
}
SendSquadMessage(squad, orgd, const text[]){
	foreach(new i: Player){
		if(PlayerInfo[i][Squad] == squad && PlayerInfo[i][time] == orgd){
			SendClientMessage(i, cor_cinza, "%s (%s)%s diz: %s", GetSquadName(PlayerInfo[i][Squad]), GetClassName(PlayerInfo[i][Classe]), nome(i), text);
		}
	}
}
MostrarSquads(playerid){
	static string[150] = "Squad\tDisponivel\tMembros\n";
	string[0] = EOS;
	string = "Squad\tDisponivel\tMembros\n";
	for(new i = ALPHA; i < MAX_SQUADS; i++){
		new str[30];
		format(str, sizeof str, "%s\t%s\t%d/5\n", GetSquadName(i), GetSquadDisponivel(i, PlayerInfo[playerid][time]) ? "Nao" : "Sim", GetMembersInSquad(i, PlayerInfo[playerid][time]));
		strcat(string, str);
	}
	ShowPlayerDialog(playerid, DIALOG_SELECT_SQUAD, DIALOG_STYLE:5, "{fff000}Squads", string, "Ok", #);
	return 1;
}
CriarLabelSquad(type, i = -1, const text[] = "", Float:x = 0.0, Float:y = 0.0, Float: z = 0.0){
	static Text3D: label = INVALID_3DTEXT_ID;
	
	if(type == LABEL_SQUAD_CRIAR){
		if(IsValidDynamic3DTextLabel(label)){
			DestroyDynamic3DTextLabel(label);
		}
		//CreateDynamic3DTextLabel(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
		label = CreateDynamic3DTextLabel(text,0xfff000FF,x, y, z, 350.0,  INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1,  -1, i);//, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
	}
	else{
		if(IsValidDynamic3DTextLabel(label)){
			DestroyDynamic3DTextLabel(label);
			label = INVALID_3DTEXT_ID;
		}
	}
	return 1;
}