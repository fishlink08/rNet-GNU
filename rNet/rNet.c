#include "../rNet/rNet.h"

#include <stdio.h>

bool ServerSocketCreation(Socket * newSocket){ 
    bool fail = false;

    newSocket->tSocket = socket(newSocket->IPType, newSocket->SProtocol, IPPROTO_TCP);
    if (newSocket->tSocket == INVALID_SOCKET) {printf("Error Creating Socket"); fail = true;}

    newSocket->tService.sin_family = newSocket->IPType;
    InetPtonA(newSocket->IPType, newSocket->address, &newSocket->tService.sin_addr.s_addr);
    newSocket->tService.sin_port = htons(newSocket->port);

    int bindResult = bind(newSocket->tSocket, (SOCKADDR*)&newSocket->tService, sizeof(newSocket->tService));
    if (bindResult == SOCKET_ERROR) {printf("Socket Bind Error"); fail = true;} 
    
    newSocket->server = true;

    if (!fail) { return false;} else { return true;}
    return false;
}
bool ClientSocketCreation(Socket * newSocket){
    bool fail = false;

    newSocket->tSocket = socket(newSocket->IPType, newSocket->SProtocol, IPPROTO_TCP);
    if (newSocket->tSocket == INVALID_SOCKET) {printf("Error Creating Socket"); fail = true;}

    newSocket->tService.sin_family = AF_INET;
    InetPtonA(newSocket->IPType, newSocket->address, &newSocket->tService.sin_addr.s_addr);
    newSocket->tService.sin_port = htons(newSocket->port);

    int connectResult = connect(newSocket->tSocket, (SOCKADDR*)&newSocket->tService, sizeof(newSocket->tService));
    if (connectResult == SOCKET_ERROR) {printf("Error connecting to server"); fail = true;};

    newSocket->server = false;

    u_long mode = 1;
    ioctlsocket(newSocket->tSocket, FIONBIO, &mode);

    if (!fail) {return false;} else { return true;}
    printf("Connected to Server!");
    return false;
}

Socket * CreateSocket(const char* address, int port, bool isServer, ConnectionProtocol SProtocol, InternetProtocol IPType)
{   

    Socket * newSocket = malloc(sizeof(Socket));
    newSocket->address = address;
    newSocket->port = port;
    newSocket->SProtocol = SProtocol;
    newSocket->IPType = IPType;

    WORD wVersionRequested = MAKEWORD(2,2);
    int WSAStartUpResp = WSAStartup(wVersionRequested, &newSocket->WinData);
    if (WSAStartUpResp != 0) {printf("Winsock DLL Not Found"); goto SOCKET_MAKE_END;}
    
    if (isServer) {
        if (ServerSocketCreation(newSocket)) {
            goto SOCKET_MAKE_END;
        }
    } else {
        if (ClientSocketCreation(newSocket)) {
            goto SOCKET_MAKE_END;
        }
    }
    //printf("successful socket creation");

    SOCKET_MAKE_END:
    return newSocket;
}

void RNET_CLEANUP(Socket * socket) {
    WSACleanup();
    closesocket(socket->tSocket);
    free(socket);
    SERVER_CLEANUP();
}

