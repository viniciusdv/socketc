#include <netinet/in.h>
#include <stdio.h>
#include <string.h> // strlen
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr
#include <unistd.h> // close

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

    /* para conectar ao servidor necessitamos do endereço IP e da porta */
    /* criamos uma variável com a struct sockaddr_in:
     * // IPv4 AF_INET sockets:
        struct sockaddr_in {
            short            sin_family;   // e.g. AF_INET, AF_INET6
            unsigned short   sin_port;     // e.g. htons(3490) 
            struct in_addr   sin_addr;     // ver struct in_addr, abaixo
            char             sin_zero[8];  // atribuir zero aqui se quiser
        };

        struct in_addr {
            unsigned long s_addr;          // carregar com inet_pton() endereço IP
        };

        struct sockaddr {
            unsigned short    sa_family;    // família de endereço, AF_xxx
            char              sa_data[14];  // 14 bytes de endereço
        };
    */
    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr("172.217.28.132"); /* ip www.google.com */
    server.sin_family = AF_INET; /* ipv4 */
    server.sin_port = htons(80); /* porta */

    // conecta ao servidor remoto
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)))
    {
        printf("Erro ao conectar\n");
        return 1;
    }

    printf("Conectado\n");

    /* envia alguns dados */
    char *message;
    message = "GET / HTTP/1.1\r\n\r\n";
    /* a função send envia dados pelo socket aberto */
    if (send(socket_desc, message, strlen(message), 0) < 0)
    {
        printf("Erro ao enviar mensagem\n");
        return 1;
    }
    printf("Dados enviados\n");

    /* a função recv recebe dados do servidor, via socket */
    char server_reply[2000];
    if (recv(socket_desc, server_reply, 2000, 0) < 0)
    {
        printf("Erro ao receber.\n");
        return 1;
    }
    printf("Resposta recebida \n");
    puts(server_reply);

    /* fecha o socket e termina a conexão */
    close(socket_desc);

    return 0;
}