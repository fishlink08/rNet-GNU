#include "../rNet/rNet.h"
#include <stdio.h>
#include <stdlib.h>

const char* ADDRESS = "127.0.0.1";
#define PORT 1235

int main() {
    system("pause");
    Socket * client = CreateSocket(ADDRESS, PORT, false, TCP, IPv4);

    while (1) {
        int awaitResult = awaitConnection(client);
        if (awaitResult == 0) {
            ClientSendData(client, "Hello, Server!", stringType);
        }
    }

    RNET_CLEANUP(client);
    return 0;
}