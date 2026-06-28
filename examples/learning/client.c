#include <stdio.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#define port 8000

typedef struct {
    int health;
} clientTestingData;

int main() {
    WSADATA WData; 
    WORD wVersionRequested = MAKEWORD(2,2); 
    int WSASTART = WSAStartup(wVersionRequested, &WData); 
    if (WSASTART != 0) {printf("Winsock DLL Not Found!"); goto CLEANUP;}


    SOCKET clientSocket = INVALID_SOCKET; 
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
    if (clientSocket == INVALID_SOCKET) {printf("Uh oh"); goto CLEANUP;}

    SOCKADDR_IN clientService;
    clientService.sin_family = AF_INET;
    LPCWSTR addr = L"127.0.0.1"; // address
    InetPtonW(AF_INET, addr, &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(port);

    int resultConnect = connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService));
    if (resultConnect == SOCKET_ERROR) {printf("Error"); goto CLEANUP;}

    printf("connected! \n");
    system("pause");

    char buffer[200];
    printf("hello mate");
    strcpy(buffer, "hello mate");
    printf("You Said: %s\n", buffer);

    clientTestingData data;
    data.health = 100;

    //int byteCount = send(clientSocket, buffer, 200, 0);
    int byteCount = send(clientSocket, (char*)&data, sizeof(data), 0);
    if (byteCount == SOCKET_ERROR) {printf("error here"); goto CLEANUP;}
    
    printf("Sent");

    while (1) {
        data.health = 9;
        int byteCount = send(clientSocket, (char*)&data, sizeof(data), 0);
        if (byteCount == SOCKET_ERROR) {printf("error here"); goto CLEANUP;}


    }

    CLEANUP:
    WSACleanup(); // cleanup of winsock, no memory leaks here
    closesocket(clientSocket); //clean up socket
    return 0;
} 
