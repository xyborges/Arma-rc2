# pip install paramiko
# pip install pathlib

import paramiko
from pathlib import Path

ssh_client = paramiko.SSHClient()

# infos
host = "149.56.41.51" # ip do seu servidor
user = "seuusuario" # usuário 
password = "suasenha" # senha
port = 8822 # porta SFTP
local_file = "C:\\Users\\Borges do parafal\\Desktop\\#ARMA RC2\\gamemodes\\TNC.amx" # diretório do gamemode
remote_path = "149.56.41.51_7776/gamemodes" # diretório do gamemode no host
gamemode = "TNC.amx" # seu gamemode
#

def main():

	ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
	ssh_client.connect(hostname=host,port=port,username=user,password=password)

	ftp = ssh_client.open_sftp()
	print('Feita a conexão!')

	if Path(local_file).exists():
		tamanho = Path(local_file).stat().st_size
		remote_file = remote_path + '/' + gamemode

		ftp.put(local_file, remote_file)
		print(f"{gamemode} foi enviado com sucesso para {remote_path}")
		ssh_client.close()
		ftp.close()
		confirmacao = input()


	else:
		print('AMX não encontrado.')


main()