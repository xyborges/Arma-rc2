new bool: morto;
public OnPlayerDeath(playerid, killerid, reason){
	morto[playerid] = true;
	EsconderBarraInfo(playerid);
	SendDeathMessage(killerid, playerid, reason)
	TogglePlayerSpectating(playerid, true);
	return 1;
}