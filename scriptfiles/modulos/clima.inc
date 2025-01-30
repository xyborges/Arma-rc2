new climas[] = {
	5, 4, 0, 9
};
forward MudarClima();
public MudarClima(){
	new r = random(sizeof climas);
	SetWeather(climas[r]);
	return 1;
}
forward hora();
public hora(){
	new h, m, s;
	gettime(h,m,s);
	foreach(new i: Player)
		SetPlayerTime(i, h, m);

	return 1;
}