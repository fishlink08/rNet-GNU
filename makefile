CC = gcc
CFLAGS = -I./rNet -I./rNet/client -I./rNet/server -I./rNet/types 
LIBS = -lws2_32
SRC = rNet/rNet.c \
      rNet/server/server.c \
      rNet/client/client.c \
      rNet/protocol/RUDP.c

all: client server

client:
	$(CC) examples/client.c $(SRC) $(CFLAGS) $(LIBS) -o bin/client

server:
	$(CC) examples/server.c $(SRC) $(CFLAGS) $(LIBS) -o bin/server