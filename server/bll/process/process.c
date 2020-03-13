#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "../../public/protocol/protocol.h"
#include "../../model/msgqueue/msgqueue.h"
#include "../../model/userlist/userlist.h"
#include "process.h"

void process_user_login_request(const int connfd, void * p_sockaddr, const char * buf, void * queue, void * list)
{
	package_user_login_request * p_request = decode_package(buf);
	package_user_login_response * p_response = (package_user_login_response *)malloc(sizeof(package_user_login_response));
	if (1 == existe((user_list)list, p_request->id, p_request->pwd))
	{
		user * p_user = user_at_id((user_list)list, p_request->id);
		p_user->connfd = connfd;
		p_user->sock_addr = p_sockaddr;
		update_user((user_list)list, p_request->id, p_user);
		user_login((user_list)list, p_request->id);
		p_response->success = 1;
		msg * p_msg = (msg *)malloc(sizeof(msg));
		p_msg->senderid = 0;
		p_msg->receiverid = p_request->id;
		p_msg->p_data = encode_package(PACKAGE_TYPE_USER_LOGIN_RESPONSE, (void*)p_response);
		push((msg_queue)queue, p_msg);
	}
	else
	{
		p_response->success = 0;
		char * p_temp = encode_package(PACKAGE_TYPE_USER_LOGIN_RESPONSE, (void*)p_response);
		send(connfd, p_temp, strlen(p_temp), 0);
		printf("Send to connfd %d:%s.\n", connfd, p_temp);
	}
}

void process_user_register_request(const int connfd, void * p_sockaddr, const char * buf, void * queue, void * list)
{
	package_user_register_request * p_request = decode_package(buf);
	package_user_register_response * p_response = (package_user_register_response *)malloc(sizeof(package_user_register_response));
	user * p_user = (user *)malloc(sizeof(user));
	p_user->name = p_request->name;
	p_user->pwd = p_request->pwd;
	p_user->connfd = connfd;
	p_user->sock_addr = p_sockaddr;
	p_response->id = append_user((user_list)list, p_user);
	msg * p_msg = (msg *)malloc(sizeof(msg));
	p_msg->senderid = 0;
	p_msg->receiverid = p_response->id;
	p_msg->p_data = encode_package(PACKAGE_TYPE_USER_REGISTER_RESPONSE, (void*)p_response);
	push((msg_queue)queue, p_msg);
}

void process_get_userlist_request(const int connfd, void * p_sockaddr, const char * buf, void * queue, void * list)
{
	package_get_userlist_request * p_request = decode_package(buf);
	package_get_userlist_response * p_response = (package_get_userlist_response *)malloc(sizeof(package_get_userlist_response));
	p_user_node p = ((user_list)list)->next;
	int count = 0;
	while(p)
	{
		if (IS_ONLINE_YES == p->is_online && p->id != p_request->id)
		{
			count++;
			if (1 == count)
			{
				p_response->ids = (int *)malloc(sizeof(int));
				p_response->names = (char **)malloc(sizeof(char*));
			}
			else
			{
				p_response->ids = (int *)realloc(p_response->ids, count);
				p_response->names = (char **)realloc(p_response->names, count);
			}
			p_response->ids[count - 1] = p->id;
			p_response->names[count - 1] = (char *)malloc(sizeof(char) * strlen(p->p_user->name));
			strcpy(p_response->names[count - 1], p->p_user->name);
		}
		p = p->next;
	}
	p_response->count = count;
	msg * p_msg = (msg *)malloc(sizeof(msg));
	p_msg->senderid = 0;
	p_msg->receiverid = p_request->id;
	p_msg->p_data = encode_package(PACKAGE_TYPE_GET_USERLIST_RESPONSE, (void*)p_response);
	push((msg_queue)queue, p_msg);
}

void process_send_message(const int connfd, void * p_sockaddr, const char * buf, void * queue, void * list)
{
	package_send_message * p = decode_package(buf);
	if (0 != user_at_id((user_list)list, p->senderid) && 0 != user_at_id((user_list)list, p->receiverid))
	{
		msg * p_msg = (msg *)malloc(sizeof(msg));
		p_msg->senderid = p->senderid;
		p_msg->receiverid = p->receiverid;
		p_msg->p_data = encode_package(PACKAGE_TYPE_SEND_MESSAGE, (void*)p);
		push((msg_queue)queue, p_msg);
	}
}

void send_data(void * queue, void * list)
{
	msg * p_msg = pop((msg_queue)queue);
	if (p_msg)
	{
		user * p_user = user_at_id((user_list)list, p_msg->receiverid);
		send(p_user->connfd, p_msg->p_data, strlen(p_msg->p_data), 0);
		printf("Send to connfd %d: %s.\n", p_user->connfd, p_msg->p_data);
	}
}
void recv_data(const int connfd, void * p_sockaddr, const char * buf, void * queue, void * list)
{
	printf("Recv from connfd %d:%s.\n", connfd, buf);
	switch(get_package_type(buf))
	{
		case PACKAGE_TYPE_USER_LOGIN_REQUEST:
			process_user_login_request(connfd, p_sockaddr, buf, queue, list);
			break;
		case PACKAGE_TYPE_USER_REGISTER_REQUEST:
			process_user_register_request(connfd, p_sockaddr, buf, queue, list);
			break;
		case PACKAGE_TYPE_GET_USERLIST_REQUEST:
			process_get_userlist_request(connfd, p_sockaddr, buf, queue, list);
			break;
		case PACKAGE_TYPE_SEND_MESSAGE:
			process_send_message(connfd, p_sockaddr, buf, queue, list);
			break;
		default:
			break;
	}
}

void user_disconnect(void * list, const int connfd)
{
	p_user_node p = ((user_list)list)->next;
	while(p)
	{
		if (connfd == p->p_user->connfd)
		{
			p->p_user->connfd = 0;
			p->is_online = IS_ONLINE_NO;
			break;
		}
		p = p->next;
	}
}