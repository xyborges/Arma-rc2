#include <YSI-Includes\YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys){
	if(PRESSED(KEY_CTRL_BACK)){ //H
		MostrarBarraInfo(playerid);
	}
	return 1;
}