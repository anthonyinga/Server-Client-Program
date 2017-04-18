//  prototypes for the functions in server_functions.c

#ifndef server_functions_h
#define server_functions_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg);
void chkArgument(int argc, char *argv0);
void chkSock(int sockfd, int sockfd2);
void chkBind(int sockfd, struct sockaddr_in serv_addr, int sockfd2, int length);
void dostuff (int sock, struct sockaddr_in cli_addr, socklen_t clilen, int sock2);

#endif
