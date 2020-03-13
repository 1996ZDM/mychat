#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../../model/msgqueue/msgqueue.h"
#include "../../model/userlist/userlist.h"
#include "../process/process.h"
#include "tcpserver.h"

typedef struct sockaddr_in sockaddr_in;

typedef struct recv_arg
{
	int connfd;
	sockaddr_in client;
	void * queue;
	void * list;
}recv_arg;

typedef struct send_arg
{
	void * queue;
	void * list;
}send_arg;

void * send_message(void * p_arg)
{
	send_arg * arg = (send_arg *)p_arg;
	while(1) send_data(arg->queue, arg->list);
	pthread_exit(NULL);
}

void * recv_message(void * p_arg)
{
	recv_arg * arg = (recv_arg *)p_arg;
	while(1)
	{
		const int buf_size = 1024;
		char buf[buf_size];
		int len_data = recv(arg->connfd, buf, buf_size, 0);
		if (len_data == 0) break;
		else if (len_data == -1) continue;
		else 
		{
			buf[len_data] = '\0';
			recv_data(arg->connfd, (void*)&arg->client, buf, arg->queue, arg->list);
		}
	}
	printf("Disconnnect from %s. Connfd is %d.\n", inet_ntoa(arg->client.sin_addr), arg->connfd);
	user_disconnect(arg->list, arg->connfd);
	close(arg->connfd);
	pthread_exit(NULL);
}

START_SERVER_RESULT start_server(int * p_sockfd)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) return START_SERVER_RESULT_SOCKET_ERROR;
	sockaddr_in server_addr;
	bzero(&server_addr, sizeof(sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(3429);
	if (-1 == bind(sockfd, (struct sockaddr *)&server_addr, sizeof(sockaddr_in))) return START_SERVER_RESULT_BIND_ERROR;
	if (-1 == listen(sockfd, 10)) return START_SERVER_RESULT_LISTEN_ERROR;
	*p_sockfd = sockfd;
	return START_SERVER_RESULT_OK;
}

void accept_connection(const int sockfd)
{
	msg_queue queue = create_queue();
	printf("Create msg queue successfully.\n");
	user_list list = create_list();
	printf("Create user list successfully.\n");
	pthread_t tid = 0;
	send_arg * s_arg = (send_arg *)malloc(sizeof(send_arg));
	s_arg->queue = (void*)queue;
	s_arg->list = (void*)list;
	pthread_create(&tid, NULL, send_message, (void *)s_arg);
	printf("Create send thread successfully.\n");
	sockaddr_in client_addr;
	socklen_t len_client_addr = sizeof(client_addr);
	while(1)
	{
		int connfd = accept(sockfd, (struct sockaddr *)&client_addr, &len_client_addr);
		if (-1 != connfd)
		{
			printf("Get a connection: %s. Connfd is %d.\n", inet_ntoa(client_addr.sin_addr), connfd);
			pthread_t tid = 0;
			recv_arg * p_arg = (recv_arg *)malloc(sizeof(recv_arg));
			p_arg->connfd = connfd;
			memcpy((void*)&p_arg->client, (void*)&client_addr, len_client_addr);
			p_arg->queue = (void*)queue;
			p_arg->list = (void*)list;
			pthread_create(&tid, NULL, recv_message, (void *)p_arg);
			printf("Create recv thread for %s successfully.\n", inet_ntoa(client_addr.sin_addr));
		}
	}
}

int stop_server(const int sockfd)
{
	return close(sockfd);
}