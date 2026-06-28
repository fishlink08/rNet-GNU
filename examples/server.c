#include "../rNet/rNet.h"

const char* ADDRESS = "127.0.0.1";
#define PORT 1235

int main() {
    Socket * myServer = CreateSocket(ADDRESS, PORT, true, TCP, IPv4);

    while (1) {
        int state = ServerOnRecieve(myServer); 
        if (state == -1) {
            break;
        }

        Data * filteredData = FilterIncomingData(state); //provides viewing of server data
        
        if (filteredData != NULL) {
            if (filteredData->type == intType) {
                printf("Data received: %d\n", filteredData->data.i);
            }
            else if (filteredData->type == floatType) {
                printf("Data received: %f\n", filteredData->data.f);
            }
            else if (filteredData->type == stringType) {
                printf("Data received: %s\n", filteredData->data.s);
            }
            else if (filteredData->type == boolType) {
                printf("Data received: %s\n", filteredData->data.b ? "true" : "false");
            }
        }   


    }

    CLEAN_UP:
    RNET_CLEANUP(myServer);
    return 0;
}