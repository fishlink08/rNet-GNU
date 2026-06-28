#include "server.h"

Data * Buffer;
int BufferSize = 2;
int CurrentBuffer = 0;
bool init = false;

int maxClients = 1;
int currentClients = 0;
bool listening = true;
bool awaitingAccept = false;

void InitBuffer(){
    Buffer = malloc(BufferSize * sizeof(Data));

    for (int i = 0; i < BufferSize; i++){
        Data d; 
        Buffer[i] = d;
    }
}

int ServerOnRecieve(Socket * Server_Socket){
    if (!init) {InitBuffer(); init = true;}

    if (listening) {
        printf("Listening on socket\n");
        int listenResult = listen(Server_Socket->tSocket, maxClients);
        if (listenResult == SOCKET_ERROR) {
            printf("Error listening on socket\n");
            return -1;
        }
        
        currentClients++;
        if (currentClients >= maxClients) {
            listening = false;
            awaitingAccept = true;
        }
    }

    if (awaitingAccept) {
        Server_Socket->tAcceptSocket = accept(Server_Socket->tSocket, NULL, NULL); //multithread this
        if (Server_Socket->tAcceptSocket == INVALID_SOCKET) {
            printf("Error accepting connection\n");
            return -1;
        }
        awaitingAccept = false;
    }

    int byteCount = recv(Server_Socket->tAcceptSocket, (char*)&Buffer[CurrentBuffer], sizeof(Data), 0);
    if (byteCount > 0) {

        CurrentBuffer = (CurrentBuffer + 1) % BufferSize;
    } else {
        if (Server_Socket->tAcceptSocket != INVALID_SOCKET) { //check if connected
            printf("Error on Recv\n");
            currentClients--;
            listening = true;
        }
    }

    return CurrentBuffer;
}

Data* FilterIncomingData(int currentThread){
    if (currentThread < 0 || currentThread >= BufferSize) {
        return NULL;
    }
    if (Buffer[currentThread].type == 0) {
        return NULL;
    }
    return &Buffer[currentThread];
}

void SERVER_CLEANUP(){
    if (Buffer != NULL) {
        free(Buffer);
        Buffer = NULL;
    }
}
