#ifndef TCPSERVER_H
#define TCPSERVER_H

typedef enum START_SERVER_RESULT
{
	START_SERVER_RESULT_OK,
	START_SERVER_RESULT_SOCKET_ERROR,
	START_SERVER_RESULT_BIND_ERROR,
	START_SERVER_RESULT_LISTEN_ERROR
}START_SERVER_RESULT;

START_SERVER_RESULT start_server(int * p_sockfd);
void accept_connection(const int sockfd);
int stop_server(const int sockfd);

#endif