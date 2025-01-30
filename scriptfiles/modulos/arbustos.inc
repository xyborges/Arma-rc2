#define MAX_ARBUSTOS 180
static arbustos;
Float:Check(&Float:val){
	if(val < 0.0)
		return -val;
	return val;
}
CriarArbustos(){
	//  523.8751831054688, 1808.6041259765625, 734.8751831054688, 2097.6041259765625
	new Float: MaxX = 523.8751831054688, Float: MaxY = 1808.6041259765625;
	new Float: MaxxX = 734.8751831054688, Float:MaxxY = 2097.6041259765625;
	while(arbustos < MAX_ARBUSTOS){//, size = sizeof(retx))){
		arbustos ++;
		
		new Float:pos[2];
		Check(MaxxX); Check(MaxxY); Check(MaxX); Check(MaxY);
		pos[0] = float(RandomEx(floatround(MaxxX), floatround(MaxX)));
		pos[1] = float(RandomEx(floatround(MaxY), floatround(MaxxY)));
		
		new Float: Z;
		CA_FindZ_For2DCoord(pos[0], pos[1], Z);

		CreateDynamicObject(824, pos[0], pos[1], Z+1.0, 0.0,0.0,0.0, -1, -1, -1, STREAMER_OBJECT_SD, STREAMER_OBJECT_DD, -1);
		CA_CreateObject(824, pos[0], pos[1], Z+1.0, 0.0,0.0,0.0);
		printf("%f %f %f", pos[0], pos[1], Z+1.0);
	}
	return 1;
}