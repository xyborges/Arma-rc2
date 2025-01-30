#define TRYG3D_ENABLE_COLANDREAS
/**/
new bool: headshot[MAX_PLAYERS];
new bool: morto[MAX_PLAYERS];
new bool: PosicaoTrocada[MAX_PLAYERS];

/* anti cheater */
#include <weaponcheat>
#include <carspam>
#include <cartroll>
#include <jetpack>
#include <airbreak>
#include <tick-difference>
//#include <rapidfire>
/**/
#if defined MAX_PLAYERS
	#undef MAX_PLAYERS 
	#define MAX_PLAYERS 50
#endif 
new nomesfracos[][32] = {
	"Fresquinho",
	"Lambe Saco",
	"Fracote",
	"Tetudo",
	"Ratao",
	"Tapete",
	"Cliente"
};
enum Infof{
	user,
	Kills,
	Mortes,
	bool:logado,
	time, Favela,
	Dinheiro,
	Admin,
	CMDPERM,
	Classe,
	Squad
	 
}
new PlayerInfo[MAX_PLAYERS][Infof];
/* modulos */
enum (<<= 1){
	HELPER = 1,
	ADMIN,
	DONO 
}