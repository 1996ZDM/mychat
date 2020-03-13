#ifndef PROCESS_H
#define PROCESS_H

void send_data(void * queue, void * list);
void recv_data(const int connfd, void * p_sockaddr, const char * buf, void * queue, void * list);
void user_disconnect(void * list, const int connfd);

#endif