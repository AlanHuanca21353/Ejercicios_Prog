// servidor_simple.c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int servidor, cliente;
    struct sockaddr_in direccion;
    int tam = sizeof(direccion);
    char buffer[1024];
    char mensaje[] = "Hola soy servidor";

    // crear socket
    servidor = socket(AF_INET, SOCK_STREAM, 0);

    // configurar direccion
    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(8080);

    // enlazar
    bind(servidor, (struct sockaddr*)&direccion, sizeof(direccion));

    // escuchar
    listen(servidor, 1);
    printf("Servidor escuchando en puerto 8080...\n");

    // aceptar cliente
    cliente = accept(servidor, (struct sockaddr*)&direccion, (socklen_t*)&tam);
    printf("Cliente conectado\n");

    // leer mensaje del cliente
    int leido = read(cliente, buffer, 1024);
    buffer[leido] = '\0';
    printf("Cliente dijo: %s\n", buffer);

    // enviar respuesta
    send(cliente, mensaje, strlen(mensaje), 0);
    printf("Mensaje enviado al cliente\n");

    // cerrar sockets
    close(cliente);
    close(servidor);

    return 0;
}
