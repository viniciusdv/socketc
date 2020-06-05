#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    int socket_desc; /* Variável que contém o socket */
    /* Address Family - AF_INET (IP versão 4)
     * Type - SOCK_STREAM (protocolo TCP orientado a conexão)
     * Protocol - 0 (Protocolo IP)
     */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    /* além de SOCK_STREAM existem os SOCK_DGRAM - UDP */

    if (socket_desc == -1)
    {
        printf("Impossível criar socket\n");
    }

    return 0;
}