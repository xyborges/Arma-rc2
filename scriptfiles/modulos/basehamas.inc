#include <YSI-Includes\YSI_Coding\y_hooks>
hook OnGameModeInit(){
	CriarVeiculo(HAMAS, 433, -230.1622, 2685.9424, 63.1154, 270.0000, -1, -1, 100);
	CriarVeiculo(HAMAS, 445, -234.5170, 2720.9731, 62.4636, 180.0000, -1, -1, 100);
	CriarVeiculo(HAMAS, 445, -230.7902, 2720.9897, 62.4636, 180.0000, -1, -1, 100);
	CriarVeiculo(HAMAS, 445, -226.6891, 2720.9353, 62.4636, 180.0000, -1, -1, 100);
	CriarVeiculo(HAMAS, 445, -222.6131, 2720.9326, 62.4636, 180.0000, -1, -1, 100);
	//aa
	CriarVeiculo(HAMAS, 554, -235.5342, 2619.4712, 62.5132, 0.0000, -1, -1, 100);
	CriarVeiculo(HAMAS, 554, -199.6417, 2618.1726, 62.8716, 0.0000, -1, -1, 100);


	infoorg[HAMAS][textoponto] = CreateDynamic3DTextLabel("{ff0000}PONTOS HAMAS:\n0", -1, -117.2704,1030.7722,19.7728, 80.0);
	return 1;
}

