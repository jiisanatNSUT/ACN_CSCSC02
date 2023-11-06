#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

void main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    int port = atoi(argv[1]);
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        exit(1);
    }

    SOCKET sockfd;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    int addr_size = sizeof(serverAddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    strcpy(buffer, "Hello Server\n");
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, addr_size);
    printf("[+]Data Sent: %s\n", buffer);

    closesocket(sockfd);
    WSACleanup();
}
