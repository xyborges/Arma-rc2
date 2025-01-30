#include <YSI-Includes\YSI_Coding\y_hooks>
new bomb[MAX_VEHICLES];

hook OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys){ 
	if(PRESSED( KEY_YES)){
		if(!IsPlayerInAnyVehicle(playerid)) return 1;

		new pveh = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(pveh) == RUSTLER){

			if(VehInfo[pveh][Bombas] < 1) return SendClientMessage(playerid, cor, "Aviao sem bombas.");
			new Float: x,Float:y,Float:z;
			GetVehiclePos(pveh, x, y, z);
			bomb[pveh] = CreateDynamicObject(3786, x, y, z-2, 0.0,0.0,90.0);//, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
			CA_FindZ_For2DCoord(x, y, z);
			MoveDynamicObject(bomb[pveh], x, y, z, 35.0);//, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0)
			VehInfo[pveh][Bombas]--;
			ContextoExplosao(bomb[pveh], playerid);
			SendClientMessage(playerid, cor, "Total de bombas ainda no aviao: %d", VehInfo[pveh][Bombas]);
		}
	}
	if(PRESSED(KEY_NO)){
		if(!IsPlayerInAnyVehicle(playerid)) return 1;

		new pveh = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(pveh) == RUSTLER){
			if(VehInfo[pveh][Misseis] < 1) return SendClientMessage(playerid, cor, "Aviao sem misseis.");
			VehInfo[pveh][Misseis] --;
			new Float: x,Float:y,Float:z, Float:a, Float:posrot[4];
			GetVehicleZAngle(pveh, a);
			GetVehiclePos(pveh, x, y, z);
			Tryg3D::GetVehicleRotation(pveh, posrot[0], posrot[1], posrot[2]);
			x = (x + 3.5 * floatsin(-a,degrees));
			y = (y + 3.5 * floatcos(-a,degrees));
			new ojt = CreateDynamicObject(345, x, y, z-1.0, posrot[0], posrot[1],posrot[2]);
			ContextoExplosao(ojt, playerid);
			initmissil(ojt, playerid);
		}
	}
	return 1;
}

forward initmissil(mis, playerid);
public initmissil(mis, playerid) {
    new Float: Object[3], Float:fimpos[3], Float:velX, Float:velY, Float:velZ, Float:rot[3];
   	GetDynamicObjectRot(mis, rot[0], rot[1], rot[2]);
    GetDynamicObjectPos(mis, Object[0], Object[1], Object[2]);

    // Calcula a velocidade nas direcoes X, Y e Z com base no angulo
	velX = 25.0 * floatsin(-rot[2] , degrees);
	velY = 25.0 * floatcos(-rot[2], degrees);
	velZ = 25.0 * floatsin(rot[0], degrees);

	Object[0] += velX;
	Object[1] += velY;
	Object[2] += velZ;
    MoveDynamicObject(mis, Object[0], Object[1], Object[2]-0.7, 78.0, rot[0], rot[1], rot[2]);

    // Verifica se o missil colidiu com algm obj usando ColAndreas
    if (CA_RayCastLine(Object[0]- velX, Object[1]- velY, Object[2]- velZ, Object[0], Object[1], Object[2], fimpos[0], fimpos[1], fimpos[2])) {
        CreateExplosion(Object[0], Object[1], Object[2], 6, 7.0);
		foreach(new i: Player){
			if(IsPlayerInRangeOfPoint(i, 9.0, Object[0], Object[1], Object[2]) && i != ContextoExplosao(mis) && !morto[i]){
				ApplyAnimation(i, "CRACK", "CRCKIDLE2", 4.0, true, false, false, true, 0, SYNC_ALL);
				CallRemoteFunction("OnPlayerDeath", "iii", i, ContextoExplosao(mis, playerid), WEAPON_BOMB);
				SetPlayerHealth(i,1.354678);
				morto[i] = true;
				Sleep(1);
				OnPlayerSpawn(i);
			}
		}
		ContextoExplosao(mis, 3);
        DestroyDynamicObject(mis);
    
  	}
  	else{
        SetTimerEx("initmissil", 300, false, "i", mis);
    }

    return 1;
}
hook OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid){
	if(GetDynamicObjectModel(objectid) == 3786){
		new Float:p[3];
		GetDynamicObjectPos(objectid,p[0], p[1], p[2]);
		CreateExplosion(p[0], p[1], p[2], 6, 6.0);
		foreach(new i: Player){
			if(IsPlayerInRangeOfPoint(i, 9.0, p[0], p[1], p[2]) && i != ContextoExplosao(objectid) && !morto[i]){
				//ApplyAnimation(playerid,  , Float:delta, bool:loop, bool:lockX, bool:lockY, bool:freeze, time, FORCE_SYNC:forceSync = SYNC_NONE)
				ApplyAnimation(i, "CRACK", "CRCKIDLE2", 4.0, true, false, false, true, 0, SYNC_ALL);
				morto[i] = true;
				CallRemoteFunction("OnPlayerDeath", "iii", i, ContextoExplosao(objectid), WEAPON_BOMB);
				SetPlayerHealth(i, 1.354678);
				Sleep(2);
				OnPlayerSpawn(i);
			}
		}
		ContextoExplosao(objectid, 3);
		DestroyDynamicObject(objectid);
	}
	return 1;
}
ContextoExplosao(obj, playerid = -1){
	static dono =-1;
	if(playerid != -1){
		dono = playerid;
	}

	return dono;

}