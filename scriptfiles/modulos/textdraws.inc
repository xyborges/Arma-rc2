#include <YSI-Includes\YSI_Coding\y_hooks>
new PlayerText:Bussola[MAX_PLAYERS][1];
new PlayerText:barrainfo[MAX_PLAYERS][8];
static timer[MAX_PLAYERS];
CriarBussola(playerid){													//434
	Bussola[playerid][0] = CreatePlayerTextDraw(playerid, 322.000000, 10.000000, "120");
	PlayerTextDrawFont(playerid, Bussola[playerid][0], TEXT_DRAW_FONT:1);
	PlayerTextDrawLetterSize(playerid, Bussola[playerid][0], 0.324999, 1.249999);
	PlayerTextDrawTextSize(playerid, Bussola[playerid][0], 343.500000, 11.000000);
	PlayerTextDrawSetOutline(playerid, Bussola[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, Bussola[playerid][0], 1);
	PlayerTextDrawAlignment(playerid, Bussola[playerid][0], TEXT_DRAW_ALIGN:2);
	PlayerTextDrawColour(playerid, Bussola[playerid][0], -1);
	PlayerTextDrawBackgroundColour(playerid, Bussola[playerid][0], 255);
	PlayerTextDrawBoxColour(playerid, Bussola[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, Bussola[playerid][0], false);
	PlayerTextDrawSetProportional(playerid, Bussola[playerid][0], true);
	PlayerTextDrawSetSelectable(playerid, Bussola[playerid][0], false);
	timer[playerid] = SetTimerEx("attbussola",1000, true, "i", playerid);
	return 1;
}

DestruirBussola(playerid){
	KillTimer(timer[playerid]);
	PlayerTextDrawDestroy(playerid, Bussola[playerid][0]);
	return 1;
}
CriarBarraInfo(playerid){
	barrainfo[playerid][0] = CreatePlayerTextDraw(playerid, 321.000000, 122.000000, "_");
	PlayerTextDrawFont(playerid, barrainfo[playerid][0], TEXT_DRAW_FONT:1);
	PlayerTextDrawLetterSize(playerid, barrainfo[playerid][0], 0.558333, 3.300003);
	PlayerTextDrawTextSize(playerid, barrainfo[playerid][0], 298.500000, 235.000000);
	PlayerTextDrawSetOutline(playerid, barrainfo[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, barrainfo[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, barrainfo[playerid][0], TEXT_DRAW_ALIGN:2);
	PlayerTextDrawColour(playerid, barrainfo[playerid][0], -1);
	PlayerTextDrawBackgroundColour(playerid, barrainfo[playerid][0], 255);
	PlayerTextDrawBoxColour(playerid, barrainfo[playerid][0], 135);
	PlayerTextDrawUseBox(playerid, barrainfo[playerid][0], true);
	PlayerTextDrawSetProportional(playerid, barrainfo[playerid][0], true);
	PlayerTextDrawSetSelectable(playerid, barrainfo[playerid][0], false);

	barrainfo[playerid][1] = CreatePlayerTextDraw(playerid, 221.000000, 121.000000, "!");
	PlayerTextDrawFont(playerid, barrainfo[playerid][1], TEXT_DRAW_FONT:0);
	PlayerTextDrawLetterSize(playerid, barrainfo[playerid][1], 0.600000, 2.999999);
	PlayerTextDrawTextSize(playerid, barrainfo[playerid][1], 230.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, barrainfo[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, barrainfo[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, barrainfo[playerid][1], TEXT_DRAW_ALIGN:1);
	PlayerTextDrawColour(playerid, barrainfo[playerid][1], -16776961);
	PlayerTextDrawBackgroundColour(playerid, barrainfo[playerid][1], 255);
	PlayerTextDrawBoxColour(playerid, barrainfo[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, barrainfo[playerid][1], false);
	PlayerTextDrawSetProportional(playerid, barrainfo[playerid][1], true);
	PlayerTextDrawSetSelectable(playerid, barrainfo[playerid][1], true);

	barrainfo[playerid][2] = CreatePlayerTextDraw(playerid, 433.000000, 113.000000, "X");
	PlayerTextDrawFont(playerid, barrainfo[playerid][2], TEXT_DRAW_FONT:1);
	PlayerTextDrawLetterSize(playerid, barrainfo[playerid][2], 0.516666, 1.649999);
	PlayerTextDrawTextSize(playerid, barrainfo[playerid][2], 445.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, barrainfo[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, barrainfo[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, barrainfo[playerid][2], TEXT_DRAW_ALIGN:1);
	PlayerTextDrawColour(playerid, barrainfo[playerid][2], -65281);
	PlayerTextDrawBackgroundColour(playerid, barrainfo[playerid][2], 255);
	PlayerTextDrawBoxColour(playerid, barrainfo[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, barrainfo[playerid][2], false);
	PlayerTextDrawSetProportional(playerid, barrainfo[playerid][2], false);
	PlayerTextDrawSetSelectable(playerid, barrainfo[playerid][2], true);

	barrainfo[playerid][3] = CreatePlayerTextDraw(playerid, 248.000000, 125.000000, "HUD:radar_hostpital");
	PlayerTextDrawFont(playerid, barrainfo[playerid][3], TEXT_DRAW_FONT:4);
	PlayerTextDrawLetterSize(playerid, barrainfo[playerid][3], 0.600000, 2.999999);
	PlayerTextDrawTextSize(playerid, barrainfo[playerid][3], 16.500000, 20.500000);
	PlayerTextDrawSetOutline(playerid, barrainfo[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, barrainfo[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, barrainfo[playerid][3], TEXT_DRAW_ALIGN:1);
	PlayerTextDrawColour(playerid, barrainfo[playerid][3], -1);
	PlayerTextDrawBackgroundColour(playerid, barrainfo[playerid][3], 255);
	PlayerTextDrawBoxColour(playerid, barrainfo[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, barrainfo[playerid][3], true);
	PlayerTextDrawSetProportional(playerid, barrainfo[playerid][3], true);
	PlayerTextDrawSetSelectable(playerid, barrainfo[playerid][3], true);	

	barrainfo[playerid][4] = CreatePlayerTextDraw(playerid, 283.000000, 125.000000, "HUD:radar_ammugun");
	PlayerTextDrawFont(playerid, barrainfo[playerid][4], TEXT_DRAW_FONT:4);
	PlayerTextDrawLetterSize(playerid, barrainfo[playerid][4], 0.600000, 2.999999);
	PlayerTextDrawTextSize(playerid, barrainfo[playerid][4], 16.500000, 20.500000);
	PlayerTextDrawSetOutline(playerid, barrainfo[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, barrainfo[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, barrainfo[playerid][4], TEXT_DRAW_ALIGN:1);
	PlayerTextDrawColour(playerid, barrainfo[playerid][4], -1);
	PlayerTextDrawBackgroundColour(playerid, barrainfo[playerid][4], 255);
	PlayerTextDrawBoxColour(playerid, barrainfo[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, barrainfo[playerid][4], true);
	PlayerTextDrawSetProportional(playerid, barrainfo[playerid][4], true);
	PlayerTextDrawSetSelectable(playerid, barrainfo[playerid][4], true);

	barrainfo[playerid][5] = CreatePlayerTextDraw(playerid, 404.000000, 125.000000, "HUD:radar_ryder");
	PlayerTextDrawFont(playerid, barrainfo[playerid][5], TEXT_DRAW_FONT: 4);
	PlayerTextDrawLetterSize(playerid, barrainfo[playerid][5], 0.600000, 2.999999);
	PlayerTextDrawTextSize(playerid, barrainfo[playerid][5], 16.500000, 20.500000);
	PlayerTextDrawSetOutline(playerid, barrainfo[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, barrainfo[playerid][5], 0);
	PlayerTextDrawAlignment(playerid, barrainfo[playerid][5], TEXT_DRAW_ALIGN:1);
	PlayerTextDrawColour(playerid, barrainfo[playerid][5], -1);
	PlayerTextDrawBackgroundColour(playerid, barrainfo[playerid][5], 255);
	PlayerTextDrawBoxColour(playerid, barrainfo[playerid][5], 50);
	PlayerTextDrawUseBox(playerid, barrainfo[playerid][5], true);
	PlayerTextDrawSetProportional(playerid, barrainfo[playerid][5], true);
	PlayerTextDrawSetSelectable(playerid, barrainfo[playerid][5], true);

	barrainfo[playerid][6] = CreatePlayerTextDraw(playerid, 315.000000, 125.000000, "ld_beat:up");
	PlayerTextDrawFont(playerid, barrainfo[playerid][6],TEXT_DRAW_FONT: 4);
	PlayerTextDrawLetterSize(playerid, barrainfo[playerid][6], 0.600000, 2.999999);
	PlayerTextDrawTextSize(playerid, barrainfo[playerid][6], 16.500000, 20.500000);
	PlayerTextDrawSetOutline(playerid, barrainfo[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, barrainfo[playerid][6], 0);
	PlayerTextDrawAlignment(playerid, barrainfo[playerid][6], TEXT_DRAW_ALIGN: 1);
	PlayerTextDrawColour(playerid, barrainfo[playerid][6], -1);
	PlayerTextDrawBackgroundColour(playerid, barrainfo[playerid][6], 255);
	PlayerTextDrawBoxColour(playerid, barrainfo[playerid][6], 50);
	PlayerTextDrawUseBox(playerid, barrainfo[playerid][6], true);
	PlayerTextDrawSetProportional(playerid, barrainfo[playerid][6], true);
	PlayerTextDrawSetSelectable(playerid, barrainfo[playerid][6], true);

	barrainfo[playerid][7] = CreatePlayerTextDraw(playerid, 346.000000, 125.000000, "ld_beat:down");
	PlayerTextDrawFont(playerid, barrainfo[playerid][7], TEXT_DRAW_FONT:4);
	PlayerTextDrawLetterSize(playerid, barrainfo[playerid][7], 0.600000, 2.999999);
	PlayerTextDrawTextSize(playerid, barrainfo[playerid][7], 16.500000, 20.500000);
	PlayerTextDrawSetOutline(playerid, barrainfo[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, barrainfo[playerid][7], 0);
	PlayerTextDrawAlignment(playerid, barrainfo[playerid][7], TEXT_DRAW_ALIGN:1);
	PlayerTextDrawColour(playerid, barrainfo[playerid][7], -1);
	PlayerTextDrawBackgroundColour(playerid, barrainfo[playerid][7], 255);
	PlayerTextDrawBoxColour(playerid, barrainfo[playerid][7], 50);
	PlayerTextDrawUseBox(playerid, barrainfo[playerid][7], true);
	PlayerTextDrawSetProportional(playerid, barrainfo[playerid][7], true);
	PlayerTextDrawSetSelectable(playerid, barrainfo[playerid][7], true);
}
DestruirBarraInfo(playerid){
	for(new i; i < 8; i++){
		PlayerTextDrawDestroy(playerid, barrainfo[playerid][i]);
	}
}
EsconderBarraInfo(playerid){
	for(new i; i < 8; i++){
		PlayerTextDrawHide(playerid, barrainfo[playerid][i]);
	}	
	CancelSelectTextDraw(playerid);
}
MostrarBarraInfo(playerid){
	for(new i; i < 8; i++){
		PlayerTextDrawShow(playerid, barrainfo[playerid][i]);
	}	
	SelectTextDraw(playerid, cor);
}
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	switch(dialogid){
		case DIALOG_REQUISITAR:{
			//"{fff000}Medico\n{fff000}Municao\n{fff000}Reforcos"
			if(response){
				new mensagem[70];
				if(listitem == 0){
					SetPlayerChatBubble(playerid, "** PRECISO DE MEDICO **", 0xfff000ff, 35.0, 5000);
					format(mensagem, sizeof mensagem, "** %s Preciso de um medico!", nome(playerid));
				}
				if(listitem == 1){
					SetPlayerChatBubble(playerid, "** PRECISO DE MUNICAO **", 0xfff000ff, 35.0, 5000);
					format(mensagem, sizeof mensagem, "** %s Preciso de Municao!", nome(playerid));
				}
				if(listitem == 2){
					SetPlayerChatBubble(playerid, "** PRECISO DE REFORCOS **", 0xfff000ff, 35.0, 5000);
					format(mensagem, sizeof mensagem, "** %s Preciso de Reforcos!", nome(playerid));
				}
				ProxMessage(playerid, 35.0, 0xfff000ff, mensagem);
			}
			else
				MostrarBarraInfo(playerid);
		}
	}
	return 1;
}
hook OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid){
	if(morto[playerid]) return SendClientMessage(playerid, cor, "Voce nao pode fazer isso morto.");
	if(playertextid == barrainfo[playerid][2]){
		EsconderBarraInfo(playerid);
	}
	if(playertextid == barrainfo[playerid][7]){// voltar (capitao)
		if(PlayerInfo[playerid][Classe] != CAPITAO) return SendClientMessage(playerid, cor, "Voce precisa ser Capitao.");
		static timerr;
		if(timerr > gettime()) return SendClientMessage(playerid, cor, "Aguarde %d segundos para usar o Recuar", timerr - gettime());
		timerr = gettime() + 45;

		new Float:x, Float:y, Float: z;
		GetPlayerCameraFrontVector(playerid, x, y, z);
	

		foreach(new i: Player){
			if(PlayerInfo[playerid][Squad] == PlayerInfo[i][Squad] && PlayerInfo[playerid][time] == PlayerInfo[i][time]){
				SendClientMessage(i, 0xFFF000FF, "** Capitao %s mandou todos recuarem.", nome(playerid));
				CriarLabelSquad(LABEL_SQUAD_DELETAR);//, i, texto, x, y, z);
			}
		}
	} 
	if(playertextid == barrainfo[playerid][6]){// ir (capitao)
		if(PlayerInfo[playerid][Classe] != CAPITAO) return SendClientMessage(playerid, cor, "Voce precisa ser Capitao.");
		static timerr;
		if(timerr > gettime()) return SendClientMessage(playerid, cor, "Aguarde %d segundos para usar o Avancar", timerr - gettime());

		new Float:fPx, Float:fPy, Float:fPz, Float:x, Float:y, Float: z;
        GetPlayerCameraPos(playerid, fPx, fPy, fPz);
        GetPlayerCameraFrontVector(playerid, x, y, z);
        new Float:finalpos[3], Float:poscol[3];

        const
            Float:fScale = 250.0;
        

        finalpos[0] = fPx + floatmul(x, fScale);
        finalpos[1] = fPy + floatmul(y, fScale);
        finalpos[2] = fPz + floatmul(z, fScale);
        //if(GetDistanceBetweenPoints(finalpos[0], finalpos[1], finalpos[2], ppos[0], ppos[1], ppos[2]) > 250.0) return SendClientMessage(playerid, cor, "Distancia maior que 250 metros!");
        
        if(CA_RayCastLine(fPx, fPy, fPz, finalpos[0], finalpos[1], finalpos[2], poscol[0], poscol[1], poscol[2])){
			timerr = gettime() + 45;
			foreach(new i: Player){
				if(PlayerInfo[playerid][Squad] == PlayerInfo[i][Squad] && PlayerInfo[playerid][time] == PlayerInfo[i][time]){
					CriarLabelSquad(LABEL_SQUAD_CRIAR, i, "** POSICAO DE ATAQUE **", poscol[0], poscol[1], poscol[2]);
					SendClientMessage(i, 0xFFF000FF,"** Capitao %s Ataquem a posicao!", nome(playerid));
				}
			}
		}
		else
			SendClientMessage(playerid, cor, "Posicao muito longe!");
	} 

	if(playertextid == barrainfo[playerid][5]){ //Requisitar

		static timerr;
		if(timerr > gettime()) return SendClientMessage(playerid, cor, "Aguarde %d segundos para usar o Requisitar", timerr - gettime());
		timerr = gettime() + 10;
		EsconderBarraInfo(playerid);
		ShowPlayerDialog(playerid, DIALOG_REQUISITAR, DIALOG_STYLE_LIST, "{fff000}#Requisitar", "{fff000}Medico\n{fff000}Municao\n{fff000}Reforcos", "Ok", "Voltar");
	}
	if(playertextid == barrainfo[playerid][4]){ //suporte
		if(PlayerInfo[playerid][Classe] != SUPORTE) return SendClientMessage(playerid, cor, "Voce precisa ser Suporte.");

		static timerr;
		if(timerr > gettime()) return SendClientMessage(playerid, cor, "Aguarde %d segundos para usar o Suporte Kit.", timerr - gettime());
		timerr = gettime() + 17;
		foreach(new i: Player){
			new Float: x, Float: y, Float: z;
			GetPlayerPos(playerid, x, y, z);
			if(IsPlayerInRangeOfPoint(i, 3.0, x, y, z) && PlayerInfo[i][time] == PlayerInfo[playerid][time] && !morto[i]){
				ArmarPorClasse(i, true);
				SendClientMessage(i, 0xfff000ff, "** Suporte ** %s rearmou jogadores proximos a ele.", nome(playerid));
			}
		}	
	}
	if(playertextid == barrainfo[playerid][3]){ //medico
		if(PlayerInfo[playerid][Classe] != MEDICO) return SendClientMessage(playerid, cor, "Voce precisa ser medico.");

		static timerr;
		if(timerr > gettime()) return SendClientMessage(playerid, cor, "Aguarde %d segundos para usar o Health Kit.", timerr - gettime());
		timerr = gettime() + 15;
		foreach(new i: Player){
			new Float: x, Float: y, Float: z;
			GetPlayerPos(playerid, x, y, z);
			if(IsPlayerInRangeOfPoint(i, 3.0, x, y, z) && PlayerInfo[i][time] == PlayerInfo[playerid][time] && !morto[i]){
				new Float:hp;
				GetPlayerHealth(playerid, hp);
				if(hp < 88)
					SetPlayerHealth(i, hp + 12.0);
				SendClientMessage(i, 0xfff000ff, "** Health ** %s curou jogadores proximos a ele.", nome(playerid));
			}
		}	
	}
	if(playertextid == barrainfo[playerid][1]){ // spot
		static timerr;
		if(timerr > gettime()) return SendClientMessage(playerid, cor, "Aguarde %d segundos para usar o Spot.", timerr - gettime());
		timerr = gettime() + 2;
		foreach(new i: Player){
			new Float: x, Float: y, Float: z;
			GetPlayerPos(playerid, x, y, z);
			if(IsPlayerInRangeOfPoint(i, 15.0, x, y, z) && PlayerInfo[i][time] == PlayerInfo[playerid][time]){
				SendClientMessage(i, 0xfff000FF, "** SPOT ** %s: inimigos ao %s.", nome(playerid), convertNAME(GetCameraAngle(playerid)));
			}
		}
		EsconderBarraInfo(playerid);
	}
	return 1;
}