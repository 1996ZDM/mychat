#include <stdlib.h>
#include <string.h>
#include "msgqueue.h"

msg_queue create_queue()
{
	p_msg_node header = (p_msg_node)malloc(sizeof(msg_node));
	header->p_msg = NULL;
	header->next = NULL;
	return header;
}

int is_queue_null(msg_queue queue)
{
	if (!queue || !queue->next)
	{
		return 1;
	}
	return 0;
}

void push(msg_queue queue, msg * p_msg)
{
	p_msg_node new_node = (p_msg_node)malloc(sizeof(msg_node));
	new_node->p_msg = p_msg;
	new_node->next = NULL;
	p_msg_node p = queue;
	while(p->next)
	{
		p = p->next;
	}
	p->next = new_node;
}

msg * pop(msg_queue queue)
{
	if (is_queue_null(queue))
	{
		return NULL;
	}
	p_msg_node p = queue->next;
	queue->next = p->next;
	return p->p_msg;
}