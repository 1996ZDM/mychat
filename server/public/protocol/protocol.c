/*
 ============================================================================
 Name        : protocol.c
 Author      : hemajun
 Version     : V.1.0
 DateTime    : 2017-01-04 08:22
 ============================================================================
*/
#include <stdlib.h>
#include <string.h>
#include "../../helper/cjson/cjson.h"
#include "protocol.h"

const char * type_node_name = "PACKAGE_TYPE";
const char * data_name = "data";

char * encode_package_user_login_request(void * data)
{
	package_user_login_request * package = (package_user_login_request *)data;
	cJSON * p_root = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_root, type_node_name, (int)PACKAGE_TYPE_USER_LOGIN_REQUEST);
	cJSON * p_data = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_data, "id", package->id);
	cJSON_AddStringToObject(p_data, "pwd", package->pwd);
	cJSON_AddItemToObject(p_root, data_name, p_data);
	char * str_json = cJSON_PrintUnformatted(p_root);
	cJSON_Delete(p_root);
	return str_json;
}

char * encode_package_user_login_response(void * data)
{
	package_user_login_response * package = (package_user_login_response *)data;
	cJSON * p_root = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_root, type_node_name, (int)PACKAGE_TYPE_USER_LOGIN_RESPONSE);
	cJSON * p_data = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_data, "success", package->success);
	cJSON_AddItemToObject(p_root, data_name, p_data);
	char * str_json = cJSON_PrintUnformatted(p_root);
	cJSON_Delete(p_root);
	return str_json;
}

char * encode_package_user_register_request(void * data)
{
	package_user_register_request * package = (package_user_register_request *)data;
	cJSON * p_root = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_root, type_node_name, (int)PACKAGE_TYPE_USER_REGISTER_REQUEST);
	cJSON * p_data = cJSON_CreateObject();
	cJSON_AddStringToObject(p_data, "name", package->name);
	cJSON_AddStringToObject(p_data, "pwd", package->pwd);
	cJSON_AddItemToObject(p_root, data_name, p_data);
	char * str_json = cJSON_PrintUnformatted(p_root);
	cJSON_Delete(p_root);
	return str_json;
}

char * encode_package_user_register_response(void * data)
{
	package_user_register_response * package = (package_user_register_response *)data;
	cJSON * p_root = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_root, type_node_name, (int)PACKAGE_TYPE_USER_REGISTER_RESPONSE);
	cJSON * p_data = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_data, "id", package->id);
	cJSON_AddItemToObject(p_root, data_name, p_data);
	char * str_json = cJSON_PrintUnformatted(p_root);
	cJSON_Delete(p_root);
	return str_json;
}

char * encode_package_get_userlist_request(void * data)
{
	package_get_userlist_request * package = (package_get_userlist_request *)data;
	cJSON * p_root = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_root, type_node_name, (int)PACKAGE_TYPE_GET_USERLIST_REQUEST);
	cJSON * p_data = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_data, "id", package->id);
	cJSON_AddItemToObject(p_root, data_name, p_data);
	char * str_json = cJSON_PrintUnformatted(p_root);
	cJSON_Delete(p_root);
	return str_json;
}

char * encode_package_get_userlist_response(void * data)
{
	package_get_userlist_response * package = (package_get_userlist_response *)data;
	cJSON * p_root = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_root, type_node_name, (int)PACKAGE_TYPE_GET_USERLIST_RESPONSE);
	cJSON * p_data = cJSON_CreateObject();
	cJSON * p_ids = cJSON_CreateIntArray(package->ids, package->count);
	cJSON * p_names = cJSON_CreateStringArray(package->names, package->count);
	cJSON_AddItemToObject(p_data, "ids", p_ids);
	cJSON_AddItemToObject(p_data, "names", p_names);
	cJSON_AddNumberToObject(p_data, "count", package->count);
	cJSON_AddItemToObject(p_root, data_name, p_data);
	char * str_json = cJSON_PrintUnformatted(p_root);
	cJSON_Delete(p_root);
	return str_json;
}

char * encode_package_send_message(void * data)
{
	package_send_message * package = (package_send_message *)data;
	cJSON * p_root = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_root, type_node_name, (int)PACKAGE_TYPE_SEND_MESSAGE);
	cJSON * p_data = cJSON_CreateObject();
	cJSON_AddNumberToObject(p_data, "senderid", package->senderid);
	cJSON_AddNumberToObject(p_data, "receiverid", package->receiverid);
	cJSON_AddStringToObject(p_data, "msg", package->msg);
	cJSON_AddItemToObject(p_root, data_name, p_data);
	char * str_json = cJSON_PrintUnformatted(p_root);
	cJSON_Delete(p_root);
	return str_json;
}

char * encode_package(PACKAGE_TYPE type, void * data)
{
	switch(type)
	{
		case PACKAGE_TYPE_USER_LOGIN_REQUEST:
			return encode_package_user_login_request(data);
			break;
		case PACKAGE_TYPE_USER_LOGIN_RESPONSE:
			return encode_package_user_login_response(data);
			break;
		case PACKAGE_TYPE_USER_REGISTER_REQUEST:
			return encode_package_user_register_request(data);
			break;
		case PACKAGE_TYPE_USER_REGISTER_RESPONSE:
			return encode_package_user_register_response(data);
			break;
		case PACKAGE_TYPE_GET_USERLIST_REQUEST:
			return encode_package_get_userlist_request(data);
			break;
		case PACKAGE_TYPE_GET_USERLIST_RESPONSE:
			return encode_package_get_userlist_response(data);
			break;
		case PACKAGE_TYPE_SEND_MESSAGE:
			return encode_package_send_message(data);
			break;
		default:
			return 0;
	}
}

PACKAGE_TYPE get_package_type(const char * data)
{
	cJSON * p_root = cJSON_Parse(data);
	return (PACKAGE_TYPE)cJSON_GetObjectItem(p_root, type_node_name)->valueint;
}

void * decode_package_user_login_request(cJSON * p_data)
{
	package_user_login_request * package = (package_user_login_request *)malloc(sizeof(package_user_login_request));
	package->id = cJSON_GetObjectItem(p_data, "id")->valueint;
	package->pwd = cJSON_GetObjectItem(p_data, "pwd")->valuestring;
	return (void *)package;
}

void * decode_package_user_login_response(cJSON * p_data)
{
	package_user_login_response * package = (package_user_login_response *)malloc(sizeof(package_user_login_response));
	package->success = cJSON_GetObjectItem(p_data, "success")->valueint;
	return (void *)package;
}

void * decode_package_user_register_request(cJSON * p_data)
{
	package_user_register_request * package = (package_user_register_request *)malloc(sizeof(package_user_register_request));
	package->name = cJSON_GetObjectItem(p_data, "name")->valuestring;
	package->pwd = cJSON_GetObjectItem(p_data, "pwd")->valuestring;
	return (void *)package;
}

void * decode_package_user_register_response(cJSON * p_data)
{
	package_user_register_response * package = (package_user_register_response *)malloc(sizeof(package_user_register_response));
	package->id = cJSON_GetObjectItem(p_data, "id")->valueint;
	return (void *)package;
}

void * decode_package_get_userlist_request(cJSON * p_data)
{
	package_get_userlist_request * package = (package_get_userlist_request *)malloc(sizeof(package_get_userlist_request));
	package->id = cJSON_GetObjectItem(p_data, "id")->valueint;
	return (void *)package;
}

void * decode_package_get_userlist_response(cJSON * p_data)
{
	package_get_userlist_response * package = (package_get_userlist_response *)malloc(sizeof(package_get_userlist_response));
	cJSON * p_ids = cJSON_GetObjectItem(p_data, "ids");
	cJSON * p_names = cJSON_GetObjectItem(p_data, "names");
	package->count = cJSON_GetArraySize(p_ids);
	package->ids = (int *)malloc(sizeof(int) * package->count);
	package->names = (char **)malloc(sizeof(char *) * package->count);
	for (int i = 0; i < package->count; ++i)
	{
		char * buf = (char *)malloc(sizeof(char) * 100);
		package->ids[i] = cJSON_GetArrayItem(p_ids, i)->valueint;
		buf = cJSON_GetArrayItem(p_names, i)->valuestring;
		package->names[i] = (char *)malloc(sizeof(char) * strlen(buf));
		strcpy(package->names[i], buf);
		free(buf);
	}
	return (void *)package;
}

void * decode_package_send_message(cJSON * p_data)
{
	package_send_message * package = (package_send_message *)malloc(sizeof(package_send_message));
	package->senderid = cJSON_GetObjectItem(p_data, "senderid")->valueint;
	package->receiverid = cJSON_GetObjectItem(p_data, "receiverid")->valueint;
	package->msg = cJSON_GetObjectItem(p_data, "msg")->valuestring;
	return (void *)package;
}

void * decode_package(const char * data)
{
	cJSON * p_root = cJSON_Parse(data);
	cJSON * p_data = cJSON_GetObjectItem(p_root, data_name);
	switch(get_package_type(data))
	{
		case PACKAGE_TYPE_USER_LOGIN_REQUEST:
			return decode_package_user_login_request(p_data);
			break;
		case PACKAGE_TYPE_USER_LOGIN_RESPONSE:
			return decode_package_user_login_response(p_data);
			break;
		case PACKAGE_TYPE_USER_REGISTER_REQUEST:
			return decode_package_user_register_request(p_data);
			break;
		case PACKAGE_TYPE_USER_REGISTER_RESPONSE:
			return decode_package_user_register_response(p_data);
			break;
		case PACKAGE_TYPE_GET_USERLIST_REQUEST:
			return decode_package_get_userlist_request(p_data);
			break;
		case PACKAGE_TYPE_GET_USERLIST_RESPONSE:
			return decode_package_get_userlist_response(p_data);
			break;
		case PACKAGE_TYPE_SEND_MESSAGE:
			return decode_package_send_message(p_data);
			break;
		default:
			return 0;
	}
}