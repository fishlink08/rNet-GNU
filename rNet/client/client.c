#include "client.h"
#include <stdio.h>

int awaitConnection(Socket * client) {
    bool ok = true;
    int result = connect(client->tSocket, (struct sockaddr*)&client->address, sizeof(client->address));
    if (result == SOCKET_ERROR) {
        if (WSAGetLastError() == 10056) {
            ok = true;
        }
        else {
            printf("Connect failed: %d\n", WSAGetLastError());
            ok = false;
        }
    }
    
    if (ok) {return 0;} else {return -1;}
    return 0;
}

void ClientSendData(Socket * client, void * data, DataType type) {
    content d = *(content*)data;

    Data dataToSend;
    dataToSend.data = d;
    dataToSend.type = type;

    int bCount = send(client->tSocket, (char*)&dataToSend, sizeof(dataToSend), 0);
    if (bCount == SOCKET_ERROR) {
        if (WSAGetLastError() == 10035) {
            return;
        }
    }
}