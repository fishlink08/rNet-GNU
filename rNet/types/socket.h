#ifndef SOCKET_TEMPLATE
#define SOCKET_TEMPLATE

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include <stdint.h>
#include <stdbool.h>

typedef enum {TCP = SOCK_STREAM, UDP = SOCK_DGRAM} ConnectionProtocol;
typedef enum {IPv4 = AF_INET, IPv6 = AF_INET6} InternetProtocol;

typedef struct {
    const char* address;
    uint16_t port;
    bool server;

    WSADATA WinData;
    SOCKET tSocket;
    SOCKADDR_IN tService;
    ConnectionProtocol SProtocol;
    InternetProtocol IPType;

    SOCKET tAcceptSocket;
} Socket;

#endif