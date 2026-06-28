#ifndef RNET
#define RNET

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../rNet/client/client.h"
#include "../rNet/server/server.h"  

#include "../rNet/types/socket.h"

Socket * CreateSocket(const char* address, int port, bool isServer, ConnectionProtocol SProtocol, InternetProtocol IPType);

void RNET_CLEANUP(Socket * socket);

#endif