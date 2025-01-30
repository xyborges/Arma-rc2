/*
	Desenvolvido por João Borges.
	ig: @xyborges
*/

/* principal */
#include <open.mp>
#include <3DTryg>
#include <streamer>
#include <samp_bcrypt>
#include <omp_database>
#include <Pawn.CMD>
#include <sscanf2>
#include <colandreas>
#include <YSI-Includes\YSI_Data\y_iterate>
		//#include <progress2>
/* modulos */
#include "../scriptfiles/modulos/gamemodeconfig.inc"
#include "../scriptfiles/modulos/database.inc"
#include "../scriptfiles/modulos/defines.inc"
#include "../scriptfiles/modulos/exes.inc"
#include "../scriptfiles/modulos/classes.inc"
#include "../scriptfiles/modulos/vehicles.inc"
#include "../scriptfiles/modulos/clima.inc"
#include "../scriptfiles/modulos/squads.inc"
#include "../scriptfiles/modulos/gangzone.inc"
#include "../scriptfiles/modulos/dialogs.inc"
#include "../scriptfiles/modulos/login.inc"
#include "../scriptfiles/modulos/antiaereas.inc"
#include "../scriptfiles/modulos/mapa.inc"
#include "../scriptfiles/modulos/moto.inc"
#include "../scriptfiles/modulos/comandos.inc"
#include "../scriptfiles/modulos/comandosadmin.inc"
#include "../scriptfiles/modulos/callantcheat.inc"
//#include "../scriptfiles/modulos/arbustos.inc"
#include "../scriptfiles/modulos/headshot.inc"
//#include "../scriptfiles/modulos/armatemperatura.inc"
//#include "../scriptfiles/modulos/OnPlayerChangeWeapon.inc"
#include "../scriptfiles/modulos/dropbomb.inc"
#include "../scriptfiles/modulos/baseisrael.inc"
#include "../scriptfiles/modulos/basehamas.inc"
#include "../scriptfiles/modulos/rebombear.inc"
#include "../scriptfiles/modulos/fobs.inc"
#include "../scriptfiles/modulos/textdraws.inc"
#include "../scriptfiles/modulos/bussola.inc"
#include "../scriptfiles/modulos/barrainfo.inc"

/* */
main() 
	return 1;

public OnGameModeInit(){
	CA_Init();
	MudarClima();
	hora();
	//CriarArbustos();
	IniciarDB();
	CriarObjetos();
	UsePlayerPedAnims();
	ShowPlayerMarkers(PLAYER_MARKERS_MODE:0);
	SetNameTagDrawDistance(8.0);  
	CriarGZS();
	SetTimer("MudarClima", MINUTOS(20), true);
	SetTimer("hora", MINUTOS(7), true);
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(false);
	return 1;
} 
public OnGameModeExit(){
	for(new i; i < sizeof gzcoord; i++)
		UseGangZoneCheck(GzDom[i][gz], false);
	DestroyAllDynamicObjects();
	closedb();
	return 1;
}
public OnPlayerConnect(playerid){
	RemoveObject(playerid);
	CriarBussola(playerid);
	CriarBarraInfo(playerid);
	dominador[playerid] = -1;
	EnablePlayerCameraTarget(playerid, true);
	SetPlayerColor(playerid, cor_cinza);
	headshot[playerid] = false;
	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 600, playerid);
	IniciarLogin(playerid);
	ShowPGz(playerid);
	return 1;
}
public OnPlayerUpdate(playerid)
{
	if(!PlayerInfo[playerid][logado] && !IsPlayerSpawned(playerid))
		TogglePlayerSpectating(playerid, true);

	//CheckChangeWeapon(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason){
	if(PlayerInfo[playerid][logado])SalvarConta(playerid);

	CriarLabelSquad(LABEL_SQUAD_DELETAR, playerid);
	DestruirBarraInfo(playerid);
	DestruirBussola(playerid);
	CheckSequencia(playerid, ZERAR_SEQUENCIA_SEM_BONUS);
	if(morto[playerid])
		morto[playerid] = false;

	new reset[Infof];
	PlayerInfo[playerid] = reset;

	DestruirMoto(playerid);
	return 1;
}

public OnPlayerSpawn(playerid){

	if(PlayerInfo[playerid][time] == HAMAS){
		SetPlayerColor(playerid, cor_vermelho);
		SetPlayerSkin(playerid, 121);
	}
	if(PlayerInfo[playerid][time] == EXERCITO_DE_ISRAEL){
		SetPlayerColor(playerid, cor_israel);
		SetPlayerSkin(playerid, 287);
	}
	if(PlayerInfo[playerid][Squad] == NENHUM){
		LimparChat(playerid);
		SendClientMessage(playerid, cor, "ATENCAO: Selecione um squad em 30s com '/squads' ou voce sera kickado!");
		SetTimerEx("KickNegoSemSquad", 30000, false, "si", nome(playerid), playerid);
	}
	if(morto[playerid]){
		TogglePlayerSpectating(playerid, true);
		morto[playerid] = false;
		AbrirSpawns(playerid, PlayerInfo[playerid][time]);
	}
	/*[
	CriarBarraTemperatura(playerid);
	ResetTemperatura(playerid);
	*/
	return 1;
}

public OnPlayerText(playerid, text[]){
	if(text[0] == 's' && text[1] == ' ' && PlayerInfo[playerid][Squad] != NENHUM_SQUAD && PlayerInfo[playerid][time] != NENHUM){
		strdel(text, 0, 1);
		SendSquadMessage(PlayerInfo[playerid][Squad], PlayerInfo[playerid][time], text);
		return 0;
	}
	else
		SendClientMessageToAll(CorOrg(PlayerInfo[playerid][time]), "[%s]%s: %s", GetSquadName(PlayerInfo[playerid][Squad]), nome(playerid), text);
	
	return 0;
}
public OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys){
	return 1;
}
function KickNegoSemSquad(const nick[], playerid){
	if(!strcmp(nome(playerid), nick)){
		if(PlayerInfo[playerid][Squad] == NENHUM)
			Kick(playerid);
	}
	return 1;
}