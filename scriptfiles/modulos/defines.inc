#include <YSI-Includes\YSI_Coding\y_va>
#if !defined isnull
    #define isnull(%1) \
                ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif
#if !defined HOLDING
	#define HOLDING(%0)		((newkeys & (%0)) == (%0))
#endif
#define function%0(%1) forward %0(%1); public %0(%1)
#if !defined PRESSED
	#define PRESSED(%0)		(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define GetDynamicObjectModel(%0) Streamer_GetIntData(STREAMER_TYPE_OBJECT, %0, E_STREAMER_MODEL_ID)
enum{
	RUSTLER = 476,
	BARRACKS = 433,
	ANTI_AEREA = 554
}
enum{
	DIALOG_REGISTRO,
	DIALOG_LOGIN,
	DIALOG_ESCOLHEREXE,
	DIALOG_QUEROKICK,
	DIALOG_PEGAR_ARMA,
	DIALOG_AJUDA,
	DIALOG_SELECT_EXE,
	OPCAO_SPAWN,
	DIALOG_REQUISITAR,
	DIALOG_SELECT_SQUAD
}
enum{
	HAMAS = 1,
	EXERCITO_DE_ISRAEL = 2
}
LimparChat(playerid, linhas = 50){
	for(new i; i < linhas; i++){
		SendClientMessage(playerid, -1, " ");
	}
	return 1;
}
Float:GetCameraAngle(playerid){
 	new Float:angle;
 	if(IsPlayerInAnyVehicle(playerid))
 		GetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
 	else
 		GetPlayerFacingAngle(playerid, angle);

 	return angle;
}
Float:GetDistanceBetweenPoints(Float:pos1X, Float:pos1Y, Float:pos1Z, Float:pos2X, Float:pos2Y, Float:pos2Z)
{
	return floatadd(floatadd(floatsqroot(floatpower(floatsub(pos1X, pos2X), 2)), floatsqroot(floatpower(floatsub(pos1Y, pos2Y), 2))), floatsqroot(floatpower(floatsub(pos1Z, pos2Z), 2)));
}
Sleep(seconds)
{
    new
        sec_a = gettime(),
        sec_b = (sec_a + seconds)
    ;

    sleep_loop:
    if(sec_a < sec_b)
    {
        sec_a = gettime();
        goto sleep_loop;
    }
}
stock semprepositivo(valor){
	if(valor < 0)
		return -valor;
	
	return valor;
}	
stock RandomEx(min ,max){
	new retorno = min;
	if(max > min){
		retorno = random(max - min + 1) + min;
	}
	else
		retorno = random(min - max + 1) + max;
	
	return retorno;
	
}
new JogadorCongelado[MAX_PLAYERS];
ProxMessage(playerid, Float:metros, color, const message[]){
	new Float: x, Float: y, Float: z;
	GetPlayerPos(playerid, x, y, z);
	foreach(new i: Player){
		if(IsPlayerInRangeOfPoint(i, metros, x, y, z)){
			SendClientMessage(i, color, message);
		}
	}
	return 1;
}
Congelar(playerid, tempovv){
	JogadorCongelado[playerid] = true;
	TogglePlayerControllable(playerid, false);
	SetTimerEx("descongelar", tempovv, false, "i", playerid);
	return 1;
}
forward descongelar(playerid);
public descongelar(playerid){
	JogadorCongelado[playerid] = false;
	TogglePlayerControllable(playerid, true);
	return 1;
}
#define KEY_AIM KEY_HANDBRAKE 
#define MINUTOS(%0) %0 * 1000 * 60
#define cor 0x33ccffFF
#define cor_amarelo 0xFFF00055
#define cor_israel 0x005EB855
#define cor_vermelho 0xFF000055
#define cor_cinza 0x80808055
enum gun{
	armaname[15],
	armaid
}
new Float:antaresELENCO[][] = {
	{-179.4431,2313.5032,9165.4014},
	{-221.8673,2305.8381,9165.5029},
	{-179.9147,2420.6304,9165.3613}
};
new Float:antaresZL[][] = {
	{20.1105,2442.8369,9175.5332},
	{25.1704,2382.5137,9165.2910},
	{-17.4793,2312.2729,9165.4463}
};
new Float:randomdesertoELENCO[][] = {
	{528.2203,1695.2710,11.1586},
	{585.4826,1912.9497,48.2868},
	{713.8136,1989.2125,6.7205}
};
new Float:randomdesertoZL[][] = {
	{661.3362,1814.4233,5.4888},
	{585.8257,1957.9786,67.4868},
	{573.3511,1813.2917,13.7975}
};
nome(playerid){
	static name[MAX_PLAYER_NAME];
	name[0] = EOS;
	GetPlayerName(playerid, name, sizeof name);
	return name;
}
enum{
	AUMENTAR_SEQUENCIA,
	ZERAR_SEQUENCIA,
	ZERAR_SEQUENCIA_SEM_BONUS
}
CheckSequencia(playerid, OPCAO){
	static sequencia, bonus;
	switch(OPCAO){
		case AUMENTAR_SEQUENCIA:{
			sequencia+= 1;
			if(sequencia > 5){
				new Float: porcentagem = float(sequencia) / 100.0;
				new Float: conta = porcentagem * 100.0;
				bonus += conta;
				PlayerInfo[playerid][Dinheiro] += floatround(conta);
				SendClientMessage(playerid, cor, "#ARMA Você ganhou um bonus de %dR$ por fazer uma sequencia de %d kills.", floatround(conta), sequencia);
			}
		}
		case ZERAR_SEQUENCIA:{
			switch(sequencia){
				case 3..4:
					SendClientMessageToAll(GetPlayerColor(playerid), "%s morreu apos fazer uma sequencia de %d kills. o cara e F0D#!!!", nome(playerid), sequencia);
				case 5..14:
					SendClientMessageToAll(GetPlayerColor(playerid), "%s MORREU APOS CANCELAR %d CPF'S!!!!", nome(playerid), sequencia);
				case 15..45:{
					SendClientMessageToAll(0x33ccffFF, "O DONO DO SERVIDOR: %s MORREU APOS UMAS SEQUENCIA DE %d KILLS!!! TODOS, AJOELHEM-SE!", nome(playerid), sequencia);
					foreach(new i: Player){
						if(i != playerid){
							ApplyAnimation(i, "PED", "IDLE_CHAT", 4.1, false, true, true, false, 1, SYNC_ALL);
						}
					}
				}
			}
			if(sequencia > 1) SendClientMessage(playerid, 0x808080FF, "#ARMA Você acumulou um bonus de %dR$!", bonus);
			sequencia = 0;
			bonus = 0;
		}
		case ZERAR_SEQUENCIA_SEM_BONUS:{
			sequencia = 0;
			bonus = 0;			
		}

	}
}
SetPlayerPosEx(playerid, Float: x, Float: y, Float: z){
	PosicaoTrocada[playerid] = true;
	Congelar(playerid, 3200);
	SetPlayerPos(playerid, x, y, z);
	SetTimerEx("removep", 2000, false, "i", playerid);
}
forward removep(playerid);
public removep(playerid){
	PosicaoTrocada[playerid] = false;
}
SendAdminsMessage(colour, const format[]){
	foreach(new i: Player){
		if(PlayerInfo[i][Admin] > 0){
			SendClientMessage(i, colour, format);
		}
	}
}
stock SetarFavela(playerid){
	switch(PlayerInfo[playerid][Favela]){
		case 1:{ // favela do deserto
			if(PlayerInfo[playerid][time] == HAMAS){
				Toggle(playerid);
				new r = random(sizeof randomdesertoZL);
				SetPlayerPosEx(playerid, randomdesertoZL[r][0], randomdesertoZL[r][1], randomdesertoZL[r][2]);
			}
			if(PlayerInfo[playerid][time] == EXERCITO_DE_ISRAEL){
				Toggle(playerid);
				new r = random(sizeof randomdesertoELENCO);
				SetPlayerPosEx(playerid, randomdesertoELENCO[r][0], randomdesertoELENCO[r][1], randomdesertoELENCO[r][2]);
			}
		}
		case 2:{ // morro de atenas
			if(PlayerInfo[playerid][time] == HAMAS){
				Toggle(playerid);
				SetPlayerPosEx(playerid,1230.5475,-2140.5630,67.2275);
			}
			if(PlayerInfo[playerid][time] == EXERCITO_DE_ISRAEL){
				Toggle(playerid);
				SetPlayerPosEx(playerid,1240.4482,-1923.6343,31.4457);
			}						
		}
		case 3:{ // morro de atenas
			if(PlayerInfo[playerid][time] == HAMAS){
				new r = random(sizeof antaresELENCO);
				Toggle(playerid);
				SetPlayerPosEx(playerid, antaresELENCO[r][0], antaresELENCO[r][1], antaresELENCO[r][2]);
				Streamer_Update(playerid);
			}
			if(PlayerInfo[playerid][time] == EXERCITO_DE_ISRAEL){
				new r = random(sizeof antaresZL);
				Toggle(playerid);
				SetPlayerPosEx(playerid, antaresZL[r][0], antaresZL[r][1], antaresZL[r][2]);
				Streamer_Update(playerid);
			}						
		}
	}
}
GetIDByName(const nick[]){
	static retorno = -1;
	foreach(new i: Player){

		if(!strcmp(nick, nome(i))){
			retorno = i;
			break;
		}
	}
	return retorno;
}