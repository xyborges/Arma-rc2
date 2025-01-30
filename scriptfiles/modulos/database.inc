
new DB:Data = DB:0;
IniciarDB(){
	if(Data) return print("#DATABASE Conexao ja existente.");
	else
		Data = DB_Open("TNC.db");

	if(Data) print("#DATABASE A Conexao foi estabelecida.");
	else
		print("#DATABASE Erro! A conexão falhou miseravelmente.");

	DB_ExecuteQuery(Data, "CREATE TABLE IF NOT EXISTS Contas (user INTEGER PRIMARY KEY AUTOINCREMENT,\
		Nome TEXT DEFAULT '',\
		Senha TEXT DEFAULT '',\
		Kills INTEGER DEFAULT 0,\
		Mortes INTEGER DEFAULT 0);");

	DB_ExecuteQuery(Data, "CREATE TABLE IF NOT EXISTS Gangzones (Gzid INTEGER PRIMARY KEY,\
		Dono INTEGER DEFAULT 0);");
	return 1;
}
closedb(){
	DB_Close(Data);
	Data = DB:0;
	return 1;
}
SalvarConta(playerid){
	if(!PlayerInfo[playerid][logado]) return 1;

	new DBResult: R = DB_ExecuteQuery(Data, "UPDATE `Contas` SET `Dinheiro` = '%d', `Kills` = '%d', `Mortes` = '%d', `Admin` = '%d' WHERE `user` = '%d'",
		PlayerInfo[playerid][Dinheiro], PlayerInfo[playerid][Kills], PlayerInfo[playerid][Mortes], PlayerInfo[playerid][Admin], PlayerInfo[playerid][user]);
	DB_FreeResultSet(R);

	PlayerInfo[playerid][logado] = false;

	return 1;
}
CarregarConta(playerid){
	new DBResult:R = DB_ExecuteQuery(Data, "SELECT * FROM `Contas` WHERE `Nome` = '%q'", nome(playerid));
	if(DB_GetRowCount(R)){
		PlayerInfo[playerid][Dinheiro] = DB_GetFieldIntByName(R, "Dinheiro");
		PlayerInfo[playerid][user] = DB_GetFieldIntByName(R, "user");
		PlayerInfo[playerid][Admin] = DB_GetFieldIntByName(R, "Admin");
		PlayerInfo[playerid][Kills] = DB_GetFieldIntByName(R, "Kills");
		PlayerInfo[playerid][Mortes] = DB_GetFieldIntByName(R, "Mortes");
		if(PlayerInfo[playerid][Admin] > 0)
			PlayerInfo[playerid][CMDPERM] = 1 << PlayerInfo[playerid][Admin]-1;
		else
			PlayerInfo[playerid][CMDPERM] = 0;
	}
	DB_FreeResultSet(R);
	return 1;
}
GetPlayerUser(playerid){
	new DBResult:r = DB_ExecuteQuery(Data, "SELECT `user` FROM `Contas` WHERE `Nome` = '%q'", nome(playerid)), resultado = 0;
	if(DB_GetRowCount(r)){
		resultado = DB_GetFieldIntByName(r, "user");
		printf("%d", resultado);
	}

	DB_FreeResultSet(r);
	return resultado;
}