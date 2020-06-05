#include <stdio.h>
#include <string.h>	//strlen
#include <sys/cdefs.h>
#include <unistd.h> // close
#include <sys/socket.h> 
#include <arpa/inet.h>	//inet_addr

int main(int argc , char *argv[])
{ 
	int socket_desc;
    struct sockaddr_in server;
    char message[2000], server_reply[2000];


    // Criar socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if (socket_desc == -1)
	{
		printf("Impossível criar socket");
	}
	
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Conectar ao socket remoto
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	
	puts("Connected");
    
    printf("Digite a sua Perguntinha : ");
    scanf("%[^\n]s", message);
 
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Falha ao enviar");
		return 1;
	}
	puts("Dados enviados\n");
	
	//Recebe resposta do servidor
	if( recv(socket_desc, server_reply , 2000 , 0) < 0)
	{
		puts("Falha ao receber.");
        return 1;
	}
	puts("Resposta recebida\n");
	puts(server_reply);

    close(socket_desc); // termina o socket

	return 0;
}