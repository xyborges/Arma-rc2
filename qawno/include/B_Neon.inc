/*

created by: borges

	
	 PegarNeon(vehicleid)
	 AnexarNeon(vehicleid, neon);
	 RemoverNeon(vehicleid);
	 NeonAnexado(vehicleid);
	 AtualizarNeon(vehicleid, novoneon);

*/

#include "streamer"

#define MAX_NEONS 2

new Neon[MAX_VEHICLES];
new AnexosEmVeiculo[MAX_VEHICLES][MAX_NEONS];
enum{
	NEON_VERDE = 18649,
	NEON_AZUL = 18648,
	NEON_VERMELHO = 18647,
	NEON_AMARELO = 18650,
	NEON_ROXO = 18651
}

forward PegarNeon(vehicleid);
forward NeonAnexado(vehicleid);
forward AnexarNeon(vehicleid, neon);
forward RemoverNeon(vehicleid);
forward AtualizarNeon(vehicleid, novoneon);


public PegarNeon(vehicleid){
	return Neon[vehicleid];
}
public NeonAnexado(vehicleid){
	return Neon[vehicleid] != 0 ? (true) : (false);
}
public AnexarNeon(vehicleid, neon){
	
	if(NeonAnexado(vehicleid))
		RemoverNeon(vehicleid);
	

	AnexarObjeto(neon, 0, vehicleid, -0.8, 0.0, -0.55, 0.0, 0.0, 0.0);
	AnexarObjeto(neon, 1, vehicleid, 0.8, 0.0, -0.55, 0.0, 0.0, 0.0);	

}
public RemoverNeon(vehicleid){
	if(NeonAnexado(vehicleid)){
		for(new i; i < MAX_NEONS; i++){
			DestroyDynamicObject(AnexosEmVeiculo[vehicleid][i]);
			AnexosEmVeiculo[vehicleid][i] = 0;
		}
		Neon[vehicleid] = 0;
	}
}
public AtualizarNeon(vehicleid, novoneon){
	if(NeonAnexado(vehicleid)){
		RemoverNeon(vehicleid);
		AnexarNeon(vehicleid, novoneon);
		return true;
	}
	return false;
}
stock AnexarObjeto(objectid, index, vehicleid, Float:ofsx, Float:ofsy, Float:ofsz, Float:RotationX, Float:RotationY, Float:RotationZ){
	
	Neon[vehicleid] = objectid;
	AnexosEmVeiculo[vehicleid][index] = CreateDynamicObject(objectid, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	AttachDynamicObjectToVehicle(AnexosEmVeiculo[vehicleid][index], vehicleid, ofsx, ofsy, ofsz, RotationX, RotationY, RotationZ);

}


