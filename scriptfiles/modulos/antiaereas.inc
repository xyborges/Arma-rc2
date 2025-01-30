#include <YSI-Includes\YSI_Coding\y_hooks>
#define MAX_AREAS 15 
//
new bool: Perseguido[MAX_VEHICLES];
new Missil[MAX_VEHICLES];
new AreaID[MAX_AREAS];
new TimerMis[MAX_VEHICLES];
//
enum iNf{
	Float:Pos[3], MisseisAA, AAA, 
	ZoneAA, Text3D: TextoAA, OrgAA
};
//
new AInfo[MAX_AREAS][iNf];
new bool: AreaVigiada[MAX_AREAS];

//

stock Aeronave(veh){
	switch(GetVehicleModel(veh)){ 
		case 548,425,563,497,469,577,511,592,520,593,512,476,553,460,413,519,488,487,417,447:{
		    return true;
		}
	}
	return false;
}

// defina como padrão a velocidade '77' no missil da anti-aerea do Yosemite
function teleguiar(veiculo)
{
	if(Perseguido[veiculo]){
		static combustivel = 250;
    	new Float: X, Float: Y, Float: Z, Float: A;
   		GetVehiclePos(veiculo, X,Y,Z);
   		GetVehicleZAngle(veiculo, A);
   		MoveObject(Missil[veiculo], X,Y,Z, 70,  0.00000, 0.00000, A); // aq
	    new Float: objectx, Float: objecty, Float: objectz, Float: exx, Float: exy, Float: exz;
     	GetObjectPos(Missil[veiculo], objectx, objecty, objectz);
     	combustivel --;
		if(combustivel < 1 || CA_RayCastLine(objectx, objecty, objectz,X,Y,Z, exx, exy, exz) > 0 || GetDistanceBetweenPoints(X,Y,Z, objectx, objecty, objectz) <= 15.0){
			CreateExplosion(objectx, objecty, objectz, 6, 20.0);
			DestroyObject(Missil[veiculo]);
			KillTimer(TimerMis[veiculo] );
			combustivel = 250;
 			Perseguido[veiculo] = false;
		}
		
	}
	return 1;
}
hook OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys){
	if(PRESSED(KEY_YES) && GetVehicleModel(GetPlayerVehicleID(playerid)) == ANTI_AEREA){
		static timerd = 0;
		if(timerd > gettime()) return SendClientMessage(playerid, cor, "Voce precisa esperar %d segundos para usar novamente.", timerd - gettime() );
		timerd = gettime() + 10;
		new veh = GetPlayerVehicleID(playerid);
		if(VehInfo[veh][Misseis] < 1) return SendClientMessage(playerid, cor, "Voce nao possui misseis.");
		foreach(new i: Player){
			if(i == playerid) continue;
			new Float: x, Float: y, Float:z;
			GetPlayerPos(i, x, y, z);
			if(!Perseguido[GetPlayerVehicleID(i)] && Aeronave(GetPlayerVehicleID(i)) && PlayerInfo[i][time] != PlayerInfo[playerid][time] && IsPlayerInRangeOfPoint(playerid, 95.0, x, y,z)){
				VehInfo[veh][Misseis] -- ;
				derrubar_comAAmovel(GetPlayerVehicleID(playerid), GetPlayerVehicleID(i));
				break;
			}
		}
	}
	return 1;
}
function derrubar_comAAmovel(anti_aerea_id, alvo_veiculo)
{
	if(Aeronave(alvo_veiculo)){
		if(Perseguido[alvo_veiculo]) return 1;

		new Float: anti_aereaX, Float: anti_aereaY, Float: anti_aereaZ, Float: X, Float: Y, Float: Z, Float: A;
		
		GetDynamicObjectPos(VehInfo[anti_aerea_id][Anti_Aerea], anti_aereaX, anti_aereaY, anti_aereaZ); 
		CreateExplosion(anti_aereaX, anti_aereaY, anti_aereaZ-20, 2, 0.5);
		GetVehicleZAngle(alvo_veiculo, A);
		AttachDynamicObjectToVehicle(VehInfo[anti_aerea_id][Anti_Aerea], anti_aerea_id, 0.000000,-1.875000,-0.524999,0.000000,0.000000,A);
	

  		GetVehiclePos(alvo_veiculo, X, Y, Z);

        
        Missil[alvo_veiculo] = CreateObject(345, anti_aereaX, anti_aereaY, anti_aereaZ+3,   0.00000, 0.00000, A);//, -1, -1, -1, 350.0, 350.0);
        MoveObject(Missil[alvo_veiculo], X, Y, Z, 5);
       	
       	TimerMis[alvo_veiculo] = SetTimerEx("teleguiar", 300, true, "i", alvo_veiculo);
        Perseguido[alvo_veiculo] = true;
	}
	return 1;
}

function derrubasaporrakk(playerid, anti_aerea, veiculo)
{
	if(IsPlayerInDynamicArea(playerid, AInfo[anti_aerea][ZoneAA]) && Aeronave(veiculo)){
		if(Perseguido[veiculo]) return 1;

		new Float: anti_aereaX, Float: anti_aereaY, Float: anti_aereaZ, Float: X, Float: Y, Float: Z, Float: A;
		GetDynamicObjectPos(AInfo[anti_aerea][AAA], anti_aereaX, anti_aereaY, anti_aereaZ); 
  		GetVehiclePos(veiculo, X, Y, Z);
        new Float: Xx, Float: Xy, Float: Xz;
        GetPlayerPos(playerid, Xx, Xy, Xz);
        GetPlayerFacingAngle(playerid, A);
        Missil[veiculo] = CreateObject(345, anti_aereaX, anti_aereaY, anti_aereaZ+4,   0.00000, 0.00000, A);//, -1, -1, -1, 350.0, 350.0);
        MoveObject(Missil[veiculo], Xx, Xy, Xz, random(7));
        CreateExplosion(anti_aereaX, anti_aereaY, anti_aereaZ-20, 2, 1.0);
       	TimerMis[GetPlayerVehicleID(playerid)] = SetTimerEx("teleguiar", 300, true, "i", GetPlayerVehicleID(playerid));
        Perseguido[veiculo] = true;
        AInfo[anti_aerea][MisseisAA] --;

		new str[64];
		format(str, sizeof(str), "{fff000}* Anti-Aerea *\n{ffffff}%d Misseis", AInfo[anti_aerea][MisseisAA]);
		UpdateDynamic3DTextLabelText(AInfo[anti_aerea][TextoAA], -1, str);
	}
	return 1;
}

hook OnPlayerLeaveDynamicArea(playerid, areaid){
	return 1;
}

hook OnPlayerEnterDynamicArea(playerid, areaid){
	if(!Aeronave(GetPlayerVehicleID(playerid))) return 1;
	if(!AreaVigiada[areaid]) return 1;
	new i = AreaID[areaid];
	if(AInfo[i][MisseisAA] == 0) return SendClientMessage(playerid, cor, "A Anti-Aerea que controla esta regiao esta sem municao!");			
	if(AInfo[i][OrgAA] == PlayerInfo[playerid][time]) return 1;
	SendClientMessage(playerid,cor, "Saia desta zona ou sua aeronave sera derrubada!");
	Sleep(4);
	if(IsPlayerInDynamicArea(playerid, areaid) && Aeronave(GetPlayerVehicleID(playerid))){	
		SendClientMessage(playerid, cor, "Uma Anti-Aerea disparou contra voce.");		
		derrubasaporrakk(playerid, i, GetPlayerVehicleID(playerid));
		new Float: pOS[4];
		GetObjectPos(AInfo[i][AAA], pOS[0], pOS[1], pOS[2]);
		GetVehicleZAngle(GetPlayerVehicleID(playerid), pOS[3]);
		MoveObject(AInfo[i][AAA], pOS[0], pOS[1], pOS[2], 5.9, 0.0, 0.0, pOS[3]);
	}
	return 1;
}
function CriarAA(orge, Float:x, Float: y, Float: z){
	for(new i; i<MAX_AREAS; i++){
	    if(AInfo[i][AAA] == 0){
	        AInfo[i][AAA] = CreateDynamicObject(3267, x, y, z, 0.0, 0.0, 0.0);
	        AInfo[i][MisseisAA] = 15;
	        AInfo[i][OrgAA] = orge;

	        AInfo[i][ZoneAA] = CreateDynamicCircle(x, y, 95.0); // defina aqui o tamanho da area (180 definido)
			AreaID[AInfo[i][ZoneAA]] = i;
			AttachDynamicAreaToObject(AInfo[i][ZoneAA], AInfo[i][AAA]);
			new str[64];
			format(str, sizeof(str), "{fff000}* Anti-Aerea *\n{ffffff}%d Misseis", AInfo[i][MisseisAA]);
			AInfo[i][TextoAA] = CreateDynamic3DTextLabel(str, -1, x, y, z, 30.0);
			AreaVigiada[AInfo[i][ZoneAA]] = true;
			return i;
		}
	}
	return -1;
}
