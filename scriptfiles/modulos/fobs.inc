#include <YSI-Includes\YSI_Coding\y_hooks>
#define MAX_AMMO_BOX 8
#define MAX_FOB_POINTS 8
enum enumammobox{
	Ammobox, Ammo, bool:caixacriada, Float:ammox, Float:ammoy, Float:ammoz
}
new InfoAmmobox[MAX_AMMO_BOX][enumammobox];
enum enumFOB{
	Text3D: FOBText,
	TheFOB,
	TotalCriado,
	Float:FOBPos[3], OrgFOB, bool:FOBCriado, bool:FOBTerminado
}
new InfoFOB[MAX_FOB_POINTS][enumFOB];
new meuFOB[MAX_PLAYERS];
abrirarma(playerid, comrraly){
	meuFOB[playerid] = comrraly;
	new string[255];

	
	for(new i=1; i < MAX_CLASSES; i++){
		new str[12];
		format(str, sizeof str, "%s\n", GetClassName(i));
		strcat(string, str);
		str[0] = EOS;
	}
	if(comrraly != 50) strcat(string, "{fff000}Definir FOB");

	if(comrraly != -1)
		ShowPlayerDialog(playerid, DIALOG_PEGAR_ARMA, DIALOG_STYLE_LIST, "{33ccff}Caixa de Arma", string, "Ok", "Sair");

}
CriarFOBPoint(myteam, Float:x, Float: y, Float: z){
	for(new i; i < MAX_FOB_POINTS; i++){
		if(!InfoFOB[i][FOBCriado]){
			InfoFOB[i][FOBPos][0] = x;
			InfoFOB[i][FOBPos][1] = y;
			InfoFOB[i][FOBPos][2] = z;
			InfoFOB[i][FOBCriado] = true;
			InfoFOB[i][FOBTerminado] = false;
			InfoFOB[i][TotalCriado] = 0;
			InfoFOB[i][OrgFOB] = myteam;
			new str[60];
			format(str, sizeof str, "%s FOB\nClique 'N' para cria-lo.", OrgNome(myteam));
			InfoFOB[i][FOBText] = CreateDynamic3DTextLabel(str, CorOrg(myteam), x,y,z, 5.0);//, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
			//InfoFOB[i][TheFOB] = CreateDynamicObject(1685, x,y,z,0,0,0);//, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
			return i;
		}
	}
	return -1;
}
function IsPlayerInAnyFOBPoint(playerid, const Float:distance){
	new retorno = -1;
	for(new i; i < MAX_FOB_POINTS; i++){
		if(InfoFOB[i][FOBCriado] && IsPlayerInRangeOfPoint(playerid, distance, InfoFOB[i][FOBPos][0], InfoFOB[i][FOBPos][1], InfoFOB[i][FOBPos][2])){
			retorno = i;
			break;
		}
	}
	return retorno;
}
stock Float:ReturnZ(Float:x, Float:y){
	new Float:z;
	CA_FindZ_For2DCoord(x, y, z);
	return z;
}
IsAmmoBoxInThisPoint(i, Float:dist, Float: x, Float:y, Float:z){

	if(InfoAmmobox[i][caixacriada])
		if(GetDistanceBetweenPoints(InfoAmmobox[i][ammox], InfoAmmobox[i][ammoy], InfoAmmobox[i][ammoz], x, y, z) < dist)
			return true;
	
	return false;
}
IsAnyAmmoBoxInThisPoint(Float: x, Float: y, Float: z, Float: dist){
	new retorno = -1;
	for(new i; i < MAX_AMMO_BOX; i++){
		if(InfoAmmobox[i][caixacriada]){
			if(IsAmmoBoxInThisPoint(i, dist, x, y, z)){
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
function AbrirSpawns(playerid, orgd){
	new str[255] = "Spawn\tFOBPoint\n", Float: x, Float: y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	for(new i; i < MAX_FOB_POINTS; i++){
		//OPCAO_SPAWN
		if(InfoFOB[i][FOBCriado] && InfoFOB[i][OrgFOB] == orgd){
			new tr[50];
			format(tr, sizeof tr, "FOB %d(%0.1fm)\t{008000}Sim\n", i, GetDistanceBetweenPoints(InfoFOB[i][FOBPos][0], InfoFOB[i][FOBPos][1], InfoFOB[i][FOBPos][2], x, y, z));
			strcat(str, tr);
		}
	}
	strcat(str, "Base\t{ff0000}Nao\n");
	ShowPlayerDialog(playerid, OPCAO_SPAWN, DIALOG_STYLE_TABLIST_HEADERS, "{FFF000}#Opcoes Spawn", str, "Spawn", #);
	return 1;
}
function CriarAmmoBox(playerid, pveh){


	new Float: x,Float:y,Float:z, Float:a, Float:posrot[4];
	GetVehicleZAngle(pveh, a);
	GetVehiclePos(pveh, x, y, z);
	Tryg3D::GetVehicleRotation(pveh, posrot[0], posrot[1], posrot[2]);
	x = (x + -5.5 * floatsin(-a,degrees));
	y = (y + -5.5 * floatcos(-a,degrees));	
	for(new i; i < MAX_AMMO_BOX; i++){
		if(IsAmmoBoxInThisPoint(i, 3.5, x, y, z)){
			if(InfoAmmobox[i][Ammo] < 100){
				InfoAmmobox[i][Ammo] = 200;
				SendClientMessage(playerid, cor, "Esta caixa foi reabastecida");
				break;
			}
			
		}
		else{
			if(!InfoAmmobox[i][caixacriada]){
				InfoAmmobox[i][ammox] = x;
				InfoAmmobox[i][ammoy] = y;
				InfoAmmobox[i][ammoz] = z-1.0;

				InfoAmmobox[i][Ammobox] = CreateDynamicObject(1685, InfoAmmobox[i][ammox], InfoAmmobox[i][ammoy], InfoAmmobox[i][ammoz], posrot[0], posrot[1],posrot[2]);
			
				InfoAmmobox[i][caixacriada] = true;
				InfoAmmobox[i][Ammo] = 200;
				VehInfo[pveh][CaixasMunicao] -= 1;
				break;
			}
		}
	}
	return -1;
}
function ContarFOBs(orgd){
	new contar;
	for(new i; i < MAX_FOB_POINTS; i++){
		if(InfoFOB[i][FOBCriado] && InfoFOB[i][OrgFOB] == orgd)
			contar++;
	}
	return contar;
}
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	switch(dialogid){
		case OPCAO_SPAWN:{
			if(response){
				new orgd = PlayerInfo[playerid][time];
				if(ContarFOBs(orgd) == 0 || listitem == (ContarFOBs(orgd))){
					Toggle(playerid);
					SetPlayerPosEx(playerid, coordhqs[orgd][0], coordhqs[orgd][1], coordhqs[orgd][2]);
				}
				else{
					if(listitem >= 0){
						for(new i; i < MAX_FOB_POINTS; i++){
							if(InfoFOB[i][FOBCriado] && InfoFOB[i][OrgFOB] == orgd){
									
								if(listitem == i){
										
									Toggle(playerid);
									SetPlayerPosEx(playerid, InfoFOB[i][FOBPos][0], InfoFOB[i][FOBPos][1], InfoFOB[i][FOBPos][2]);
									break;
								}
								else
									continue;
							}
							else
								listitem++;
						
						}
					}
				}
			}
		}
		case DIALOG_PEGAR_ARMA:{
			if(response){
				if(listitem < 5){
					static tempor;
					if(tempor > gettime()) return SendClientMessage(playerid, cor, "Espere %d segundos para se equipar novamente.", tempor-gettime());
					tempor = gettime() + 20;


					if(PlayerInfo[playerid][Classe] == listitem+1){
						ArmarPorClasse(playerid, true);
					}else{
						if(listitem+1 != SOLDADO && HasClassInSquad(listitem+1, PlayerInfo[playerid][Squad], PlayerInfo[playerid][time])){
							SendClientMessage(playerid, cor, "Voce nao pode pegar esta classe. Alguem do seu Squad ja pegou.");
							PC_EmulateCommand(playerid, "arma");
						}
						else{
							SendClientMessage(playerid, cor, "Voce definiu sua classe.");
							PlayerInfo[playerid][Classe] = listitem+1;
							ArmarPorClasse(playerid, false);
						}
					}

					new str[29 + 10];
					format(str, sizeof str, "#ARMA %s pegou uma arma.", nome(playerid));
					ProxMessage(playerid, 35.0, 0xFFF000FF, str);
				}
				else{
					if(PlayerInfo[playerid][Classe] != CAPITAO) return SendClientMessage(playerid, cor, "Voce precisa ser da classe Capitao para criar uma FOB.");
					if(GangZoneAtual[playerid] == INVALID_GANG_ZONE || GzDom[GangZoneAtual[playerid]][donogz] != PlayerInfo[playerid][time]) return SendClientMessage(playerid, cor, "Para criar uma FOB aqui, voce primeiro precisa dominar o gangzone.");
					new Float: x,Float:y,Float:z, objeto = InfoAmmobox[meuFOB[playerid]][Ammobox];
					
					GetDynamicObjectPos(objeto, x, y, z);
					new Float:posrot[4];
					GetDynamicObjectRot(objeto, posrot[0], posrot[1], posrot[2]);
					x = (x + 3.2 * floatsin(-posrot[2],degrees));
					y = (y + 3.2 * floatcos(-posrot[2],degrees));
					if(IsPlayerInAnyFOBPoint(playerid, 4.5) != -1) return SendClientMessage(playerid, cor, "Ja existe uma FOB nesta posicao.");
					new FOBp = CriarFOBPoint(PlayerInfo[playerid][time], x, y, z);
					if(FOBp == -1) return SendClientMessage(playerid, cor, "Nao foi possivel criar a FOB.");
					else
						SendClientMessage(playerid, cor, "FOB definida! Comece a cria-la.");
				}
			}
		}
	}
	return 1;
}
hook OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys){
	if(PRESSED(KEY_YES)){
		if(!IsPlayerInAnyVehicle(playerid)) return 1;
		new pveh = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(pveh) == BARRACKS){
			if(VehInfo[pveh][CaixasMunicao] == 0) return SendClientMessage(playerid, cor, "Veiculo sem caixas.");
			CriarAmmoBox(playerid, pveh);
		}
	}
	if(HOLDING(KEY_NO)){
		new FOBpoint = IsPlayerInAnyFOBPoint(playerid, 2.2);

		if(FOBpoint != -1){
			if(!InfoFOB[FOBpoint][FOBTerminado]){
				if(IsPlayerInAnyVehicle(playerid)) return 1;
				if(GetPlayerWeapon(playerid)) return SendClientMessage(playerid, cor, "Voce nao pode construir a FOB com uma arma na mao.");
				if(InfoFOB[FOBpoint][TotalCriado] < 100){
					static conta;
					ApplyAnimation(playerid, "SWORD", "sword_4", 2.8, false, false, false, false, false, SYNC_ALL);
					conta++;
					if(conta >= 6){
						InfoFOB[FOBpoint][TotalCriado] ++;
						SendClientMessage(playerid, cor, "%d%% construido.", InfoFOB[FOBpoint][TotalCriado]);
						conta = 0;
						if(InfoFOB[FOBpoint][TotalCriado] >= 100){
							new Float:rot[3];
							GetDynamicObjectPos(InfoAmmobox[IsAnyAmmoBoxInThisPoint(InfoFOB[FOBpoint][FOBPos][0], InfoFOB[FOBpoint][FOBPos][1], InfoFOB[FOBpoint][FOBPos][2], 5.8)][Ammobox], rot[0], rot[1], rot[2]);
							
							SendClientMessageToAll(cor, "%s criou uma FOB.", OrgNome(PlayerInfo[playerid][time]));
							InfoFOB[FOBpoint][FOBTerminado] = true;
					
							InfoFOB[FOBpoint][TheFOB] = CreateDynamicObject(3403, InfoFOB[FOBpoint][FOBPos][0], InfoFOB[FOBpoint][FOBPos][1], InfoFOB[FOBpoint][FOBPos][2]+2.4, 0,0, rot[2]);// worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
							new str[32];
							format(str, sizeof str, "* %s FOB *", OrgNome(PlayerInfo[playerid][time]));
							UpdateDynamic3DTextLabelText(InfoFOB[FOBpoint][FOBText], CorGangZone(PlayerInfo[playerid][time]), str);
						}
					}
				}
			}
		}
	}
	return 1;
}
cmd:arma(playerid){
	if(PlayerInfo[playerid][Squad] == NENHUM) return SendClientMessage(playerid, cor, "Voce precisa entrar em um Squad antes de pegar alguma arma.");
	if(IsPlayerInRangeOfPoint(playerid, 3.0,  -241.31604, 2687.88232, 62.77743) && PlayerInfo[playerid][time] == HAMAS){
		abrirarma(playerid, 50);
	}
	else if(IsPlayerInRangeOfPoint(playerid, 3.0, -538.2888,-175.3368,78.4047) && PlayerInfo[playerid][time] == EXERCITO_DE_ISRAEL){
		abrirarma(playerid, 50);
	}
	else{
		new Float:x, Float: y, Float: z;
		GetPlayerPos(playerid, x, y, z);
		new ammo = IsAnyAmmoBoxInThisPoint(x, y, z, 3.5);
		if(ammo != -1)
			abrirarma(playerid, ammo);
	}
	return 1;
}