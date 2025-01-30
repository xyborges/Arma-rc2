
enum TIMES{
	SEM_TIME,
	TIME_TCP,
	TIME_CV
}
enum ENUM_INFOTIME{
	Time,
	Float:TimeX, Float:TimeY, Float:TimeZ, Float:TimeA
}
new Float: SpawnTime[TIMES][ENUM_INFOTIME] = {
	{SEM_TIME, 0, 0, 0,},
	{TIME_TCP, -213.86075, 2282.43311, 9166.38965, 90.0},
	{TIME_CV, 56.7799, 2371.4226, 9165.7686, 90.0}
};