#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];
    char mensaje[1024];

    // Crear socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("No se pudo crear el socket\n");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Conectar
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("No se pudo conectar al servidor\n");
        return 1;
    }
    printf("Conectado al servidor!\n");

    // Bucle de chat
    while (1) {
        printf("Cliente: ");
        fgets(mensaje, sizeof(mensaje), stdin);
        send(sock, mensaje, strlen(mensaje), 0);

        int leido = read(sock, buffer, sizeof(buffer));
        if (leido <= 0) {
            printf("Servidor desconectado\n");
            break;
        }
        buffer[leido] = '\0';
        printf("Servidor: %s\n", buffer);
    }

    close(sock);
    return 0;
}
