#include "Client.h"
#include "protocol.h"

void Connection_init(){
	
	
	if(!inet_aton("192.168.38.129",&server.sin_addr)) //调用inet_aton()，将ptr点分十进制转in_addr
    {
	        printf("Inet_aton error\n");
	        exit(1);
    }
	if ((he = gethostbyaddr((void *)&server.sin_addr,4,AF_INET)) == NULL) 
	{
		printf("%s\n",hstrerror(h_errno));
		exit(1);
	}
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("Create socket failed.\n");
		exit(1);
	}

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr = *((struct in_addr *) he->h_addr);
	if (connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) 
	{
		perror("connect failed.\n");
		exit(1);
	}
	printf("Successful!\n");
	
	G_Login();
}


void * Send_Message(GtkWidget *button,gpointer userdata)
{
	int id = userdata;
	char str[50];
	struct tm *p;
    time_t t1;
	struct tm *t2;
	t1=time(NULL);
	t2=localtime(&t1);

    //定义时间，该时间为1970年1月1日0时0分0秒到现在所经过的秒数
    time_t ti;

	//将时间转化成日历时间
	ti = time(NULL);

	//将时间转化成当地时间
	p = localtime(&ti);

	//以“时：分：秒”的形式存在str中
	strftime(str,20,"%H:%M:%S",p);
	
    gtk_text_buffer_get_start_iter(buffer,&start);
    gtk_text_buffer_get_end_iter(buffer,&end);
	do{
    	strcpy(buf_send, gtk_text_buffer_get_text(buffer,&start,&end,TRUE));
		if(strlen(buf_send)<=0)
		{
			printf("pls input again: \n");
			return 0;
		}
		break;
	}while(1);
	
	pthread_mutex_lock(&mux);
	gtk_text_buffer_get_end_iter(buffer1,&end);
	gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer1),&end,"I   said:   ",strlen("I   said:   "));	
	gtk_text_buffer_get_end_iter(buffer1,&end);
	gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer1),&end,buf_send,strlen(buf_send));
	gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer1),&end,"\t",strlen("\t"));
	gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer1),&end,str,strlen(str));
	gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer1),&end,"\n",strlen("\n"));
	
	package_send_message * p_request = (package_send_message *)malloc(sizeof(package_send_message));
	p_request->senderid=my_id;
	p_request->receiverid=id;
	p_request->msg = buf_send;
	
	char * buf = encode_package(PACKAGE_TYPE_SEND_MESSAGE, (void *)p_request);
    Send_Package(fd,buf);

	//清空发送区的内容
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
	gtk_text_buffer_delete(buffer,&start,&end);

	pthread_mutex_unlock(&mux);
	
}

void *Recv_Message(){
	pthread_detach(pthread_self());
	while(1){

	//定义字符数组，用来存贮聊天时间
    char str[50];
   	struct tm *p;
	int len_data;
    	
    //定义时间，该时间为1970年1月1日0时0分0秒到现在所经过的秒数
    time_t ti;
	
    //将时间转化成日历时间
    ti = time(NULL);
    //将时间转化成当地时间
    p = localtime(&ti);

    //以“时：分：秒”的形式存在str中
    strftime(str,20,"%H:%M:%S",p);
 
    //获得聊天时的日期，存贮在str_date中，形式为： 月／天／年 (年为后两位)
    struct tm *p_date;
    time_t ti_date;
    ti_date = time(NULL);
    p_date = localtime(&ti_date);
    strftime(str_date,20,"%D",p_date);
    if((len_data = Recv_Package(fd,buf_recv)) > 0)
    {
		g_print("server said：%s\n",buf_recv);	
		pthread_mutex_lock(&mux);
		buf_recv[len_data] = '\0';
		if (PACKAGE_TYPE_SEND_MESSAGE == get_package_type(buf_recv))
		{

			package_send_message * p_response = decode_package(buf_recv);
			printf("%s\n", p_response->msg);
			gtk_text_buffer_get_end_iter(buffer1,&end);
			gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer1),&end,"He said:  ",strlen("He said:  "));	
			gtk_text_buffer_get_end_iter(buffer1,&end);		
            gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer1),&end,p_response->msg,strlen(p_response->msg));  
			gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer1),&end,"\t",strlen("\t"));
  			gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer1),&end,str,strlen(str));
			gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer1),&end,"\n",strlen("\n"));
		}
		pthread_mutex_unlock(&mux);
			
    }
    }//while(1)
	
}

void * Login(gpointer userdata){
	/*struct Login_Info * login_info = (struct Login_Info *)userdata;
	const gchar * pUser = gtk_entry_get_text (GTK_ENTRY(login_info->id));
	printf("id_login: %s  pwd_login: %s\n",pUser,pUser);*/
	char pwd_[20];
	char id_[20];
	
	gtk_text_buffer_get_start_iter(buf_id,&start_login);
    gtk_text_buffer_get_end_iter(buf_id,&end_login);
    strcpy(id_, gtk_text_buffer_get_text(buf_id,&start_login,&end_login,TRUE));
	gtk_text_buffer_get_start_iter(buf_pwd,&start_login);
    gtk_text_buffer_get_end_iter(buf_pwd,&end_login);
    strcpy(pwd_, gtk_text_buffer_get_text(buf_pwd,&start_login,&end_login,TRUE));
	 
	package_user_login_request * p_request = (package_user_login_request *)malloc(sizeof(package_user_login_request));
	my_id = p_request->id = atoi(id_);
	p_request->pwd = pwd_;
	char * buf = encode_package(PACKAGE_TYPE_USER_LOGIN_REQUEST, (void *)p_request);
	Send_Package(fd, buf);
	char buf_recv[100];
	int len_data = Recv_Package(fd, buf_recv);
	printf("login\n");
	if (0 != len_data && -1 != len_data)
	{
		printf("login...\n");
		buf_recv[len_data] = '\0';
		if (PACKAGE_TYPE_USER_LOGIN_RESPONSE == get_package_type(buf_recv))
		{
			package_user_login_response * p_response = decode_package(buf_recv);
			printf("houge\n");
			if( 1 == p_response->success)
			{
				printf("success\n");
				printf("%d\n",p_response->success);
				gtk_widget_hide(userdata);
				Get_UserList();
			}
			else 
				printf("failed");
		}
	}
}

void * Register(gpointer userdata){
	char name_[255];
	char pwd_[255];
	gtk_text_buffer_get_start_iter(buf_name,&start_register);
    gtk_text_buffer_get_end_iter(buf_name,&end_register);
	
    strcpy(name_, gtk_text_buffer_get_text(buf_name,&start_register,&end_register,TRUE));
	gtk_text_buffer_get_start_iter(buf_pwd_register,&start_register);
    gtk_text_buffer_get_end_iter(buf_pwd_register,&end_register);
    strcpy(pwd_, gtk_text_buffer_get_text(buf_pwd_register,&start_register,&end_register,TRUE));	
	package_user_register_request * p_request = (package_user_register_request *)malloc(sizeof(package_user_register_request));
	p_request->name = name_;
	p_request->pwd = pwd_;
	char * buf = encode_package(PACKAGE_TYPE_USER_REGISTER_REQUEST, (void *)p_request);
	Send_Package(fd, buf);
	char buf_recv[20];
	int len_data = Recv_Package(fd, buf_recv);
	package_user_register_response * p_response = decode_package(buf_recv);
	if ( (my_id = p_response->id) > 0 )
	{
		Dialog_Info(userdata,p_response->id);
		gtk_widget_hide(userdata);
		G_Login();
	}
}

package_get_userlist_response Get_UserList(){
	package_get_userlist_request * p_request = (package_get_userlist_request *)malloc(sizeof(package_get_userlist_request));
	p_request->id = my_id;
	char * buf = encode_package(PACKAGE_TYPE_GET_USERLIST_REQUEST, (void *)p_request);
	Send_Package(fd, buf);
	char buf_recv[500];
	int len_data = Recv_Package(fd, buf_recv);
	package_get_userlist_response * p_response = decode_package(buf_recv);
	printf("UserList: %d\n",p_response->ids[0]);
	if(p_response->count >= 0){
		G_Window(NULL,NULL,p_response);
		return *p_response;
	}
}

void Send_Package(int fd, char * buf_send){
	send(fd, buf_send, strlen(buf_send),0);
}

int Recv_Package(int fd, char * buf_recv){
	return recv(fd,buf_recv,MAXDATASIZE,0);	
}
