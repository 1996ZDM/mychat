/*
 ============================================================================
 Name        : protocol.h
 Author      : hemajun
 Version     : V.1.0
 DateTime    : 2017-01-04 08:22
 ============================================================================
*/
#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef enum PACKAGE_TYPE
{
	PACKAGE_TYPE_USER_LOGIN_REQUEST,
	PACKAGE_TYPE_USER_LOGIN_RESPONSE,
	PACKAGE_TYPE_USER_REGISTER_REQUEST,
	PACKAGE_TYPE_USER_REGISTER_RESPONSE,
	PACKAGE_TYPE_GET_USERLIST_REQUEST,
	PACKAGE_TYPE_GET_USERLIST_RESPONSE,
	PACKAGE_TYPE_SEND_MESSAGE,
	PACKAGE_TYPE_UNKOWN
}PACKAGE_TYPE;

typedef struct package_user_login_request
{
	int id;
	char * pwd;
}package_user_login_request;

typedef struct package_user_login_response
{
	int success;
}package_user_login_response;

typedef struct package_user_register_request
{
	char * name;
	char * pwd;
}package_user_register_request;

typedef struct package_user_register_response
{
	int id;
}package_user_register_response;

typedef struct package_get_userlist_request
{
	int id;
}package_get_userlist_request;

typedef struct package_get_userlist_response
{
	int count;
	int * ids;
	char ** names;
}package_get_userlist_response;

typedef struct package_send_message
{
	int senderid;
	int receiverid;
	char * msg;
}package_send_message;

char * encode_package(PACKAGE_TYPE type, void * data);
PACKAGE_TYPE get_package_type(const char * data);
void * decode_package(const char * data);

#endif