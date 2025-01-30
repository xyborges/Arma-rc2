new SV_LSTREAM:lstream[MAX_PLAYERS] = { SV_NULL, ... };

CriarVoip(playerid){
    if ((lstream[playerid] = SvCreateDLStreamAtPlayer(25.0, SV_INFINITY, playerid, 0xff0000ff, "Local")))
    {
        SendClientMessage(playerid, cor, "#ARMA Voip criado.");
        SvAddKey(playerid, 0x42);
    }
}


DeletarVoip(playerid)
{
    // Removing the player's local stream after disconnecting
    if (lstream[playerid] != SV_NULL)
    {
        SvDeleteStream(lstream[playerid]);
        lstream[playerid] = SV_NULL;
    }
}