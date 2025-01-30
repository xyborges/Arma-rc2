#define MAX_ORGS 5

enum org{
	pontos,
	kills,
	mortes,
	Text3D:textoponto
}
new infoorg[MAX_ORGS][org];
new const Float: coordhqs[][] = {
	{0.0,0.0,0.0}, // nenhum
	{ -241.31604, 2687.88232, 62.77743}, // hms
	{-538.31989, -179.93448, 78.38483}
};
OrgNome(i){
	new str[32];
	switch(i){
		case EXERCITO_DE_ISRAEL: str = "Israel";
		case HAMAS: str = "Hamas";
		default: str = "nenhum";
	}
	return str;
}

function AdicionarPontos(orgd, total){
	infoorg[orgd][pontos] += total;
	new str[90];
	format(str, sizeof str, "Pontos de %s\n%d", OrgNome(orgd), infoorg[orgd][pontos]);
	UpdateDynamic3DTextLabelText(infoorg[orgd][textoponto], CorGangZone(orgd), str);
}
function CorOrg(i){
	switch(i){
		case EXERCITO_DE_ISRAEL: return 0x005EB8FF;
		case HAMAS: return 0xff0000FF;
		default: return 0xffffffFF;
	}
}