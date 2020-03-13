/*
 ============================================================================
 Name        : userlist.c
 Author      : hemajun
 Version     : V.1.0
 DateTime    : 2017-01-04 08:22
 ============================================================================
 */
#include <stdlib.h>
#include <string.h>
#include "userlist.h"

user_list create_list()
{
	p_user_node header = (p_user_node)malloc(sizeof(user_node));
	header->p_user = NULL;
	header->next = NULL;
	return header;
}

int is_list_null(user_list list)
{
	if (!list || !list->next)
	{
		return 1;
	}
	return 0;
}

int append_user(user_list list, user * p_user)
{
	p_user_node new_node = (p_user_node)malloc(sizeof(user_node));
	new_node->p_user = p_user;
	new_node->is_online = IS_ONLINE_NO;
	new_node->next = NULL;
	int id = 1;
	p_user_node p = list;
	while(p->next)
	{
		id++;
		p = p->next;
	}
	new_node->id = id;
	p->next = new_node;
	return id;
}

int existe(user_list list, const int id, const char * pwd)
{
	p_user_node p = list->next;
	while(p)
	{
		if (id == p->id && 0 == strcmp(p->p_user->pwd, pwd))
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

user * user_at_id(user_list list, const int id)
{
	p_user_node p = list->next;
	while(p)
	{
		if (id == p->id)
		{
			return p->p_user;
		}
		p = p->next;
	}
	return 0;
}

void update_user(user_list list, const int id, user * p_user)
{
	p_user_node p = list->next;
	while(p)
	{
		if (id == p->id)
		{
			memcpy((void*)p->p_user, (void*)p_user, sizeof(user));
			return;
		}
		p = p->next;
	}
}

void user_online(user_list list, const int id, IS_ONLINE is_online)
{
	p_user_node p = list->next;
	while(p)
	{
		if (id == p->id)
		{
			p->is_online = is_online;
			return;
		}
		p = p->next;
	}
}

void user_login(user_list list, const int id)
{
	user_online(list, id, IS_ONLINE_YES);
}

void user_logoff(user_list list, const int id)
{
	user_online(list, id, IS_ONLINE_NO);
}