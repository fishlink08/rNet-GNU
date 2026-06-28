#ifndef CLIENT_SOURCE
#define CLIENT_SOURCE

#include "../types/socket.h"
#include "../types/data.h"

int awaitConnection(Socket * client);
void ClientSendData(Socket * client, void * data, DataType type);

Data * ClientRecieveData(Socket * client);

#endif