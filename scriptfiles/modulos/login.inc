
IniciarLogin(playerid){
	new DBResult:R = DB_ExecuteQuery(Data, "SELECT * FROM `Contas` WHERE `Nome` = '%q' COLLATE NOCASE", nome(playerid));
	if(DB_GetRowCount(R)){
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "{33ccff}Troca No Complexo", "Seja bem vindo(a) ao nosso servidor!\nDigite a senha de login da sua conta.", "Login", "Sair");
	}
	else
		ShowPlayerDialog(playerid, DIALOG_REGISTRO, DIALOG_STYLE_PASSWORD, "{33ccff}Troca No Complexo", "Seja bem vindo(a) ao nosso servidor!\nDigite uma senha no campo abaixo para criar sua conta.", "Registar", "Sair");
	
	DB_FreeResultSet(R);
	return 1;
}