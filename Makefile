SHELL = /bin/sh
FLAGS = -Wall
CC = g++

all:	server client

server.o: server.c
	$(CC) $(FLAGS) -c server.c

client.o: client.c
	$(CC) $(FLAGS) -c client.c
	
server_functions.o: server_functions.c server_functions.h
	$(CC) $(FLAGS) -c server_functions.c
	
client_functions.o: client_functions.c client_functions.h
	$(CC) $(FLAGS) -c client_functions.c

server: server.o server_functions.o
	$(CC) -o server server.o server_functions.o
	
client: client.o client_functions.o
	$(CC) -o client client.o client_functions.o

clean:
	rm server client server.o client.o server_functions.o client_functions.o
