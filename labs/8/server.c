#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

void main(int argc, char **argv) {
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
    struct sockaddr_in si_me, si_other;
    char buffer[1024];
    int addr_size = sizeof(si_other);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me)) == SOCKET_ERROR) {
        fprintf(stderr, "bind failed\n");
        closesocket(sockfd);
        WSACleanup();
        exit(1);
    }

    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&si_other, &addr_size);
    printf("[+]Data Received: %s\n", buffer);

    closesocket(sockfd);
    WSACleanup();
}
