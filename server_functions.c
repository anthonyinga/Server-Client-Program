//server_functions.c
//Contains functions to manage server

#include "server_functions.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

//Displays error message and terminates program
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

//Checks that program has passed an appropriate amount of arguments.
//Displays error with proper execution command and terminates program.
void chkArgument(int argc, char *argv0)
{
	if (argc < 2)
	{
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
}

//Checks that socket file descriptor was successfully assigned.
void chkSock(int sockfd, int sockfd2)
{
	if (sockfd < 0)
	  error("ERROR opening socket");
	if (sockfd2 < 0)
		error("ERROR opening socket");
}

//Checks status of binded ports
void chkBind(int sockfd, struct sockaddr_in serv_addr, int sockfd2, int length)
{
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");

	if (bind(sockfd2,(struct sockaddr *) &serv_addr, length)<0)
    error("ERROR on binding");
}

//Servers process to send and receive information from client
void dostuff(int sock, struct sockaddr_in cli_addr, socklen_t clilen, int sock2)
{
	int n, n2;
	char buffer[256];
	char buffer2[256];

	bzero(buffer,256);

	n = read(sock,buffer,255);
	n2 = recvfrom(sock2,buffer2,255,0,(struct sockaddr *)&cli_addr,&clilen);

	//Check for errors in reading from socket
	if (n2 < 0)
		error("ERROR recvfrom");
	if (n < 0)
		error("ERROR reading from socket");

	//print message
	printf("Here is the message from TCP: %s", buffer);
	printf("Here is the message from UDP: %s\n", buffer2);


	n = write(sock,"I got your message (TCP)",25);
	n2 = sendto(sock2,"I got your message (UDP)",25,0, (struct sockaddr *) &cli_addr,clilen);

	//Check for errors in writing to socket
	if (n2 < 0)
		error("ERROR sendto");
	if (n < 0)
		error("ERROR writing to socket");
}
