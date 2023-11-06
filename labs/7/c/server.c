#include <stdio.h>
#include <winsock2.h>

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup error");
        return 1;
    }

    char *ip = "127.0.0.1";
    int port = 5566;

    SOCKET server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    int addr_size = sizeof(client_addr);
    char buffer[1024];
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == INVALID_SOCKET) {
        perror("Socket error");
        return 1;
    }
    printf("[+] TCP server socket created.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n == SOCKET_ERROR) {
        perror("Bind error");
        closesocket(server_sock);
        WSACleanup();
        return 1;
    }
    printf("[+] Bind to the port number: %d\n", port);

    n = listen(server_sock, 5);
    if (n == SOCKET_ERROR) {
        perror("Listen error");
        closesocket(server_sock);
        WSACleanup();
        return 1;
    }
    printf("Listening...\n");

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        if (client_sock == INVALID_SOCKET) {
            perror("Accept error");
            closesocket(server_sock);
            WSACleanup();
            return 1;
        }
        printf("[+] Client connected.\n");

        memset(buffer, 0, sizeof(buffer));
        n = recv(client_sock, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            perror("Recv error");
        } else {
            printf("Client: %s\n", buffer);
        }

        memset(buffer, 0, sizeof(buffer));
        strcpy(buffer, "HI, THIS IS SERVER. HAVE A NICE DAY!!!");
        printf("Server: %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);

        closesocket(client_sock);
        printf("[+] Client disconnected.\n\n");
    }

    closesocket(server_sock);
    WSACleanup();

    return 0;
}
