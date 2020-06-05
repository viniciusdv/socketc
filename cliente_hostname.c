#include <stdio.h> //printf
#include <string.h> //strcpy
#include <sys/socket.h>
#include <netdb.h>	//hostent
#include <arpa/inet.h>

int main(int argc , char *argv[])
{
	char *hostname = "www.google.com";
	char ip[100];
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
		
	if ( (he = gethostbyname( hostname ) ) == NULL) 
	{
		/* gethostbyname falhou */
		herror("gethostbyname");
		return 1;
	}
	
	/*  Transforma h_addr_list ao in_addr */
    addr_list = (struct in_addr **) he->h_addr_list;
	
	for(i = 0; addr_list[i] != NULL; i++) 
	{
		//Retorna o primeiro
		strcpy(ip , inet_ntoa(*addr_list[i]) );
	}
	
	printf("%s resolvido para : %s\n" , hostname , ip);
	return 0;
}