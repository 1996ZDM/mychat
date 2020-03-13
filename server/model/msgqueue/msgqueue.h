#ifndef MSGQUEUE_H
#define MSGQUEUE_H

typedef struct msg
{
	int senderid;
	int receiverid;
	char * p_data;
}msg;

typedef struct msg_node
{
	msg * p_msg;
	struct msg_node * next;
}msg_node, *p_msg_node, *msg_queue;

msg_queue create_queue();
void push(msg_queue queue, msg * p_msg);
msg * pop(msg_queue queue);

#endif