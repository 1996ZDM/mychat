/*
 ============================================================================
 Name        : userlist.h
 Author      : hemajun
 Version     : V.1.0
 DateTime    : 2017-01-04 08:22
 ============================================================================
*/
#ifndef USERLIST_H
#define USERLIST_H

typedef struct user
{
	char * name;
	char * pwd;
	int connfd;
	void * sock_addr;
}user;

typedef enum IS_ONLINE
{
	IS_ONLINE_YES = 1,
	IS_ONLINE_NO = 0
}IS_ONLINE;

typedef struct user_node
{
	int id;
	IS_ONLINE is_online;
	user * p_user;
	struct user_node * next;
}user_node, *p_user_node, *user_list;

user_list create_list();
int append_user(user_list list, user * p_user);
int existe(user_list list, const int id, const char * pwd);
user * user_at_id(user_list list, const int id);
void update_user(user_list list, const int id, user * p_user);
void user_login(user_list list, const int id);
void user_logoff(user_list list, const int id);

#endif