#include <stdio.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#define port 8000

typedef struct {
    int health;
} clientTestingData;


int main() {
    WSADATA WData; // Cleate empty variable of Winsock Data
    WORD wVersionRequested = MAKEWORD(2,2); // Wanting version 2.2, this allows it to unify it and be able to be understood by WSAStartup
    int WSASTART = WSAStartup(wVersionRequested, &WData); // intialize winsock, this is required before using any winsock functions (it takes both the version and a reference to WData)
    if (WSASTART != 0) {printf("Winsock DLL Not Found!"); goto CLEANUP;}
    

    SOCKET serverSocket = INVALID_SOCKET; // create variable first
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //create socket (param one is ipv4, param 2 means tcp (dgram = udp). and ipprotovo is something)
    if (serverSocket == INVALID_SOCKET) {printf("Uh oh"); goto CLEANUP;}


    SOCKADDR_IN service; //socket binding struct creation
    service.sin_family = AF_INET; //Family type, ipv4 or ipv6
    LPCWSTR addr = L"127.0.0.1"; // address
    InetPtonW(AF_INET, addr, &service.sin_addr.s_addr); // converts the string address to a format that can be used by the socket, it takes the family type, the string address, and a reference to where to store the converted address (in this case, the sin_addr.s_addr field of the service struct)
    service.sin_port = htons(port); // converts the port number to network byte order (big-endian) and stores it in the sin_port field of the service struct

    int resultBind = bind(serverSocket, (SOCKADDR*)&service, sizeof(service)); // binds the socket to the address and port specified in the service struct, it takes the socket, a pointer to the service struct (cast to a SOCKADDR pointer), and the size of the service struct
    if (resultBind == SOCKET_ERROR) {printf("Ass"); goto CLEANUP;}


    int listenResponse = listen(serverSocket, 1); // listen for clients, up to 1 connection max
    if (listenResponse == SOCKET_ERROR) {printf("nope"); goto CLEANUP;}
    

    SOCKET acceptSocket; // accept socket
    acceptSocket = accept(serverSocket, NULL, NULL); // waits until its accepted
    if (acceptSocket == INVALID_SOCKET) {printf("Error"); goto CLEANUP;}

    printf("client connected to me! \n");


    char RecieveBuffer[200] = "";
    clientTestingData data;
    int byteCount = recv(acceptSocket, (char*)&data, sizeof(data), 0); // receive data from the client, it takes the accepted socket, a buffer to store the received data, the size of the buffer, and flags (0 means no flags)
    //int byteCount = recv(acceptSocket, RecieveBuffer, 200, 0);
    if (byteCount < 0) {printf("Error on Recv"); goto CLEANUP;}

    printf("Got: %d\n", data.health);

    while (1) {
        int byteCount = recv(acceptSocket, (char*)&data, sizeof(data), 0);
        if (byteCount < 0) {printf("Error on Recv"); goto CLEANUP;}

        printf("Got: %d\n", data.health);
    }


    CLEANUP:
    WSACleanup(); // cleanup of winsock, no memory leaks here
    closesocket(serverSocket); //clean up socket
    return 0;
}