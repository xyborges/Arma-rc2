#include <open.mp>
#include <Pawn.CMD>
main(){

}
cmd:veiculo(playerid, params[]){
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	//CreateVehicle(modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2, respawnDelay, bool:addSiren = false)
	CreateVehicle(strval(params), x, y, z,90.0,0,0, -1);
	return 1;
}