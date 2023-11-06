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

    SOCKET sock;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        perror("Socket error");
        return 1;
    }
    printf("[+] TCP client socket created.\n");

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connect error");
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Connected to the server.\n");

    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "HELLO, THIS IS CLIENT.");
    printf("Client: %s\n", buffer);
    send(sock, buffer, strlen(buffer), 0);

    memset(buffer, 0, sizeof(buffer));
    n = recv(sock, buffer, sizeof(buffer), 0);
    if (n <= 0) {
        perror("Recv error");
    } else {
        printf("Server: %s\n", buffer);
    }

    closesocket(sock);
    WSACleanup();
    printf("Disconnected from the server.\n");

    return 0;
}
