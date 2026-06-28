#ifndef SERVER_SOURCE
#define SERVER_SOURCE

#include "../types/data.h"
#include "../types/socket.h"

#include <stdio.h>
#include <stdint.h>

int ServerOnRecieve(Socket * Server_Socket);
Data * FilterIncomingData(int currentThread);

int SendData(Socket * Server_Socket, Socket * Recieving_Socket, Data * Trasmitting_Data);
int SendDataToAll(Socket * Server_Socket, Data * Trasmitting_Data);

void SERVER_CLEANUP();

#endif