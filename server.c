//server.c
/*A simple server in the internet domain using TCP.
This version runs forever, forking off a separate
process for each connection*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "server_functions.h"

int main(int argc, char *argv[])
{
	int sockfd, sockfd2, length, newsockfd, portno, pid;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	//check arguments if there is a port provided
	chkArgument(argc, argv[0]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	sockfd2 = socket(AF_INET, SOCK_DGRAM, 0);

	//check if the socket has been opened
	chkSock(sockfd, sockfd2);

	length = sizeof(serv_addr);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	//check if server is binded
	chkBind(sockfd, serv_addr,sockfd2, length);

	//look for a connection
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	//forking off processes to handle new connections continuously
	while (1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
			error("ERROR on accept");
		pid = fork();
		if (pid < 0)
			error("ERROR on fork");
		if (pid == 0)
		{
			close(sockfd);
			dostuff(newsockfd, cli_addr, clilen, sockfd2);
			exit(0);
		}
		else close(newsockfd);
		signal(SIGCHLD,SIG_IGN);
	}

	//Close sockets before ending program
	close(sockfd);
	close(sockfd2);

	return 0;
}
