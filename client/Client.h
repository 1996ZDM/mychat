#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <glib.h>
#include "protocol.h"
#define PORT 		3429
#define MAXDATASIZE	100

int my_id,count_online;
int fd, numbytes;
char buf_recv[MAXDATASIZE],buf_send[MAXDATASIZE];
struct hostent *he;
struct sockaddr_in server;
char str_date[100];

pthread_mutex_t mux;
pthread_cond_t cond_buffer1;

enum {
	NAME_COLUMN,
	ID_COLUMN,
	NUM_COLS,
};

struct G_Info{
	int senderid;
	char name[20];
	int flag;
}g_info[MAXDATASIZE];

GtkTextBuffer *buffer1;
GtkTextBuffer *buffer;
GtkTextIter start,end;
GtkTextIter start_login, end_login;
GtkTextBuffer *buf_id, *buf_pwd;
GtkTextBuffer *buf_name,*buf_pwd_register;
GtkTextIter start_register, end_register;

void G_Chat(void * data);
GtkWidget * Dialog_Info(GtkWindow *parent, int id);
void * Login(gpointer userdata);
void * Register(gpointer userdata);
package_get_userlist_response  Get_UserList();
void Destroy(GtkWidget *widget, gpointer *data);
GtkWidget * G_Login();
GtkWidget * G_Register(gpointer userdata);
GtkWidget * G_Chat_Window(char *name,int id);
GtkWidget * G_Window(GtkWidget *view_hide, gpointer userdata,package_get_userlist_response * p_response_getuserlist);
void Connection_init();
void Send_Package(int fd, char * buf_send);
int Recv_Package(int fd, char * buf_recv);
void * Recv_Message();
void * Send_Message(GtkWidget *button,gpointer userdata);
static GtkWidget *create_view_and_model(package_get_userlist_response * p_response_getuserlist);
static GtkTreeModel *create_and_fill_model(package_get_userlist_response * p_response_getuserlist);
gint delete_event( GtkWidget *widget,GdkEvent  *event,gpointer userdata ) ;
void view_onRowActivated (GtkTreeView *treeview,
                      GtkTreePath *path,
                      GtkTreeViewColumn *col,
                      gpointer userdata);


