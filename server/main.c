/*
 ============================================================================
 Name        : main.c
 Author      : hemajun
 Version     : V.1.0
 DateTime    : 2017-01-04 08:22
 ============================================================================
*/
#include <stdio.h>
#include "bll/tcpserver/tcpserver.h"
#include "public/foo/common.h"

int main(int argc, char const *argv[])
{
	int sockfd = 0;
	switch(start_server(&sockfd))
	{
		case START_SERVER_RESULT_SOCKET_ERROR:
			print_func_error("socket");
			break;
		case START_SERVER_RESULT_BIND_ERROR:
			print_func_error("bind");
			break;
		case START_SERVER_RESULT_LISTEN_ERROR:
			print_func_error("listen");
			break;
		default:
			printf("Server started.\n");
			accept_connection(sockfd);
			stop_server(sockfd);
			printf("Server stopped.\n");
	}
	return 0;
}