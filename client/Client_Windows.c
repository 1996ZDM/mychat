#include "Client.h"
#include "protocol.h"


char g_name[20]={0};

void file_ok_sel( GtkWidget *w,GtkFileSelection *fs )
{
	g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
}

void wenjian(){
	GtkWidget *filew;
	filew = gtk_file_selection_new ("File selection");
	g_signal_connect (G_OBJECT (filew), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),"clicked",G_CALLBACK (file_ok_sel), filew);
	g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),"clicked",G_CALLBACK (gtk_widget_destroy), filew);
	gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew),"");
	gtk_widget_show (filew);
	gtk_main ();

}

GtkWidget * G_Login(){
	
	
	GtkWidget *window;
    
	GtkWidget *vbox;

	GtkWidget *h_box;

  	GtkWidget *one;

  	GtkWidget *two;

  	GtkWidget *three;

  	GtkWidget *close;

  	GtkWidget *login; 

	GtkWidget *sep;

	GtkWidget *id;
	GtkWidget *pwd;
	GtkWidget *id_text;
	GtkWidget *pwd_text;
	
  	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window),200,200);
  	gtk_window_set_title(GTK_WINDOW(window),"Login");
	

	vbox=gtk_vbox_new(FALSE,0);
  	gtk_container_add(GTK_CONTAINER(window),vbox);
  

  	one = gtk_hbox_new(FALSE,0);
  	gtk_widget_set_size_request(one,200,200);

	one = gtk_table_new(1,3,TRUE);
  	gtk_widget_set_size_request(one,200,40);
	gtk_table_set_row_spacings(GTK_TABLE(one),0);
	gtk_box_pack_start(GTK_BOX(vbox),one,TRUE,TRUE,0);
	id = gtk_label_new("id");
	gtk_table_attach_defaults(GTK_TABLE(one),id,0,1,0,1);
	id_text = gtk_text_view_new();
	gtk_table_attach_defaults(GTK_TABLE(one),id_text,1,3,0,1);

	two = gtk_table_new(1,3,TRUE);
  	gtk_widget_set_size_request(two,200,40);
	gtk_table_set_row_spacings(GTK_TABLE(two),0);
	gtk_box_pack_start(GTK_BOX(vbox),two,TRUE,TRUE,0);
	pwd = gtk_label_new("pwd");
	gtk_table_attach_defaults(GTK_TABLE(two),pwd,0,1,0,1);
	pwd_text = gtk_text_view_new();
	//gtk_text_set_visibility(GTK_ENTRY(pwd_text),FALSE);
	gtk_table_attach_defaults(GTK_TABLE(two),pwd_text,1,3,0,1);

	
	sep = gtk_hseparator_new();//分割线  
    	gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,5); 

	three = gtk_table_new(1,4,TRUE);
  	gtk_widget_set_size_request(three,200,40);
	gtk_table_set_row_spacings(GTK_TABLE(three),0);
	gtk_box_pack_start(GTK_BOX(vbox),three,TRUE,TRUE,0);
	close = gtk_button_new_with_label("register");
	gtk_table_attach_defaults(GTK_TABLE(three),close,0,2,0,1);
	login = gtk_button_new_with_label("login");;
	gtk_table_attach_defaults(GTK_TABLE(three),login,2,4,0,1);

	gtk_container_set_border_width(GTK_CONTAINER(one),20);
	gtk_container_set_border_width(GTK_CONTAINER(two),20);
	gtk_container_set_border_width(GTK_CONTAINER(three),15);

	buf_id = gtk_text_view_get_buffer(GTK_TEXT_VIEW(id_text));
	buf_pwd = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwd_text));
	
  	gtk_widget_show_all(window); 
	
  	g_signal_connect_swapped(G_OBJECT(close),"clicked",G_CALLBACK(G_Register),window);

  	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_widget_destroy),window);
    	g_signal_connect_swapped(G_OBJECT(login),"clicked",G_CALLBACK(Login),window);         

	gtk_main();
	
}

GtkWidget * G_Register(gpointer userdata){
	gtk_widget_hide(userdata);

	GtkWidget *window;
    
	GtkWidget *vbox;

	GtkWidget *h_box;

  	GtkWidget *one;

  	GtkWidget *two;

  	GtkWidget *three;

  	GtkWidget *close;

  	GtkWidget *login; 
	
	GtkWidget *sep;

	GtkWidget *name;
	GtkWidget *pwd;
	GtkWidget *name_text;
	GtkWidget *pwd_text;
	
  	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window),200,200);
  	gtk_window_set_title(GTK_WINDOW(window),"Register");

	vbox=gtk_vbox_new(FALSE,0);
  	gtk_container_add(GTK_CONTAINER(window),vbox);
  
  	one = gtk_hbox_new(FALSE,0);
  	gtk_widget_set_size_request(one,200,200);

	one = gtk_table_new(1,3,TRUE);
  	gtk_widget_set_size_request(one,200,40);
	gtk_table_set_row_spacings(GTK_TABLE(one),0);
	gtk_box_pack_start(GTK_BOX(vbox),one,TRUE,TRUE,0);
	name = gtk_label_new("name");
	name_text = gtk_text_view_new();
	buf_name = gtk_text_view_get_buffer(GTK_TEXT_VIEW(name_text));
	gtk_text_view_set_editable (GTK_TEXT_VIEW(name_text), TRUE);
	gtk_table_attach_defaults(GTK_TABLE(one),name,0,1,0,1);
	
	gtk_table_attach_defaults(GTK_TABLE(one),name_text,1,3,0,1);

	two = gtk_table_new(1,3,TRUE);
  	gtk_widget_set_size_request(two,200,40);
	gtk_table_set_row_spacings(GTK_TABLE(two),0);
	gtk_box_pack_start(GTK_BOX(vbox),two,TRUE,TRUE,0);
	pwd = gtk_label_new("pwd");
	gtk_table_attach_defaults(GTK_TABLE(two),pwd,0,1,0,1);
	pwd_text = gtk_text_view_new();
	buf_pwd_register = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwd_text));
	gtk_table_attach_defaults(GTK_TABLE(two),pwd_text,1,3,0,1);

	sep = gtk_hseparator_new();//分割线  
    	gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,5); 

	three = gtk_table_new(1,4,TRUE);
  	gtk_widget_set_size_request(three,200,40);
	gtk_table_set_row_spacings(GTK_TABLE(three),0);
	gtk_box_pack_start(GTK_BOX(vbox),three,TRUE,TRUE,0);
	close = gtk_button_new_with_label("close");
	gtk_table_attach_defaults(GTK_TABLE(three),close,0,2,0,1);
	login = gtk_button_new_with_label("register");;
	gtk_table_attach_defaults(GTK_TABLE(three),login,2,4,0,1);
	
	gtk_container_set_border_width(GTK_CONTAINER(one),20);
	gtk_container_set_border_width(GTK_CONTAINER(two),20);
	gtk_container_set_border_width(GTK_CONTAINER(three),15);

  	gtk_widget_show_all(window); 
	
  	g_signal_connect_swapped(G_OBJECT(close),"clicked",G_CALLBACK(gtk_widget_destroy),window);

  	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_widget_destroy),window);
    g_signal_connect_swapped(G_OBJECT(login),"clicked",G_CALLBACK(Register),window);         //

	gtk_main();
	
}

GtkWidget * G_Window(GtkWidget *view_hide, gpointer userdata,package_get_userlist_response * p_response_getuserlist)
{
	gtk_widget_hide(userdata);
	GtkWidget *view;
    GtkWidget *window;
    GtkTreeSelection *selection;
    GtkWidget *vbox;
    GtkWidget *statusbar;
    
    	

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
    gtk_window_set_title(GTK_WINDOW(window), "QQ");
    gtk_widget_set_size_request(window, 200, 500);
    
    vbox = gtk_vbox_new(FALSE, 2);
    gtk_container_add(GTK_CONTAINER(window), vbox);

	view = create_view_and_model(p_response_getuserlist);
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));

        
    
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 1);
    
    statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);
    	
		

    g_signal_connect(view, "row-activated", (GCallback) view_onRowActivated, NULL);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(Destroy),window);
    
    gtk_widget_show_all(window);
    	
    gtk_main();
}

void view_onRowActivated (GtkTreeView *treeview,
                      GtkTreePath *path,
                      GtkTreeViewColumn *col,
                      gpointer userdata)
{
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(treeview);

	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gchar *name,*id;

		gtk_tree_model_get(model, &iter, NAME_COLUMN, &name, ID_COLUMN, &id, -1);

		g_print ("Double-clicked row contains name %s, id: %s\n", name,id);
		
		if(strcmp(name,"My Friend"))
		{
			int i;

			for(i=0;i<count_online;i++)
			{
				if(!strcmp(name,g_info[i].name))
				{
					printf("flag: %d\n",g_info[i].flag);
					if(1 != g_info[i].flag)
					{
						g_info[i].flag = 1;
						G_Chat_Window(name,atoi(id));
						break;
					}else
						continue;
									
				}
			}
			
		}

		g_free(name);
    }
}

static GtkTreeModel *create_and_fill_model(package_get_userlist_response * p_response_getuserlist)
{
	GtkTreeStore *treestore;    
	GtkTreeIter toplevel, child;
	treestore = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING,G_TYPE_STRING);
	count_online = p_response_getuserlist->count;
	char str_id[20];
	
	gtk_tree_store_append(treestore, &toplevel, NULL);
	gtk_tree_store_set(treestore, &toplevel, 0, "OnLine Friend", -1);
	int i;
	for(i = 0; i < p_response_getuserlist->count; i++)
	{	
		g_info[i].senderid = p_response_getuserlist->ids[i];
		sprintf(str_id,"%d",p_response_getuserlist->ids[i]);
		gtk_tree_store_append(treestore, &child, &toplevel);
		strcpy(g_info[i].name,p_response_getuserlist->names[i]); 
		g_info[i].flag = 0;
		gtk_tree_store_set(treestore, &child, NAME_COLUMN, p_response_getuserlist->names[i],ID_COLUMN,str_id, -1);
	}

	pthread_t pid;
	pthread_create(&pid,NULL,Recv_Message,NULL);
	return GTK_TREE_MODEL(treestore);
}

static GtkWidget *create_view_and_model(package_get_userlist_response * p_response_getuserlist)
{
	GtkTreeViewColumn *col;
	GtkCellRenderer *renderer;
	GtkWidget *view;
	GtkTreeModel *model;

	view = gtk_tree_view_new();

	col = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(col, "OnLine Friend");
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(col, renderer, TRUE);
	gtk_tree_view_column_add_attribute(col, renderer, "text", NAME_COLUMN);

	model = create_and_fill_model(p_response_getuserlist);
	gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
	g_object_unref(model);

	return view;
}
void G_Chat(void * data){
	
	G_Chat_Window("huang", 7);
	
}
GtkWidget * G_Chat_Window(char *name,int id)
{
	GtkWidget *window;
    	
	
	//定义一个竖向盒，用于整合界面
	GtkWidget *vbox;

	//定义一个横向盒，用于装入对话框和按钮
	GtkWidget *h_box;

	//定义接收框
  	GtkWidget *one;

	//定义工具栏
  	GtkWidget *two;

	//定义发送框
  	GtkWidget *three;

	//定义发送、关闭工具栏
  	GtkWidget *four;

	//定义查询聊天记录按钮
  	GtkWidget *History;
  	
  	GtkWidget *transport;
	
	//定义按钮用于发送文件
	GtkWidget *file;

	//定义关闭按钮
  	GtkWidget *close;

	//定义发送按钮
  	GtkWidget *send; 

	GtkWidget *send_entry;
	GtkWidget *receive_entry;
	
    //定义主窗口
  	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	//设置主窗口位置、大小、标题
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window),500,500);
  	gtk_window_set_title(GTK_WINDOW(window),name);

  	//建立vbox，并将其装入主窗口
	vbox=gtk_vbox_new(FALSE,0);
  	gtk_container_add(GTK_CONTAINER(window),vbox);
  
	//建立hbox，并设置其大小，用于接收消息
  	one = gtk_hbox_new(FALSE,0);
  	gtk_widget_set_size_request(one,500,300);

	//将one装入vbox中
	gtk_box_pack_start(GTK_BOX(vbox),one,TRUE,TRUE,0);
  	
  	//定义一个滚动窗口
  	GtkWidget *scrolled_window; 

	//建立一个文本框，用于接收消息
  	receive_entry = gtk_text_view_new();

	//定义接收区缓冲
  	buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(receive_entry));
     
	//创建滚动窗体
	scrolled_window = gtk_scrolled_window_new(NULL, NULL); 

	//设置滚动条为需要时显示
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 

	//将滚动窗体放到盒子中
	gtk_box_pack_start (GTK_BOX(one), scrolled_window, TRUE, TRUE, 0); 

	//将text放到滚动窗体中
	gtk_container_add (GTK_CONTAINER(scrolled_window), receive_entry); 

	//设置textview构件为自动换行
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(receive_entry), GTK_WRAP_WORD_CHAR); 
	gtk_text_view_set_editable (GTK_TEXT_VIEW(receive_entry), FALSE);
	
	//设置textview构件大小
	gtk_widget_set_size_request (GTK_WIDGET(receive_entry), 110, 50); 
	
	two = gtk_table_new(1,4,TRUE);
  	gtk_widget_set_size_request(two,500,40);
	gtk_table_set_row_spacings(GTK_TABLE(two),0);
	
	//将two装入vbox
  	gtk_box_pack_start(GTK_BOX(vbox),two,FALSE,TRUE,0);
	
	//建立发送按钮，并设置其位置及大小
  	History = gtk_button_new_with_label("消息记录");
	gtk_table_attach_defaults(GTK_TABLE(two),History,3,4,0,1);
	
	//transport
	transport = gtk_button_new_with_label("文件传输");
	gtk_table_attach_defaults(GTK_TABLE(two),transport,2,3,0,1);
	g_signal_connect (G_OBJECT (transport),"clicked",G_CALLBACK (wenjian),NULL);

	//建立hbox，并设置大小，用于文本输入
  	three = gtk_hbox_new(FALSE,0);
  	gtk_widget_set_size_request(three,500,100);
   	gtk_box_pack_start(GTK_BOX(vbox),three,TRUE,TRUE,0);

	//建立文本输入框
   	send_entry = gtk_text_view_new(); 

	//建立文本输入缓冲区
   	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(send_entry));
     
	//创建滚动窗体
	scrolled_window = gtk_scrolled_window_new(NULL, NULL); 

	//设置滚动条为需要时显示
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 

	//将滚动窗体放到盒子中
	gtk_box_pack_start (GTK_BOX(three), scrolled_window, TRUE, TRUE, 0); 

	//将text放到滚动窗体中
	gtk_container_add (GTK_CONTAINER(scrolled_window), send_entry); 

	//设置textview构件为自动换行
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(send_entry), GTK_WRAP_WORD_CHAR); 
	gtk_text_view_set_editable (GTK_TEXT_VIEW(send_entry), TRUE);
	
	//设置textview构件大小
	gtk_widget_set_size_request (GTK_WIDGET(send_entry), 110, 50); 
	gtk_widget_grab_focus(send_entry);

	//建立一个表格，并设置大小，用于装入发送和关闭按钮
	four = gtk_table_new(1,4,TRUE);
  	gtk_widget_set_size_request(four,500,40);
	gtk_table_set_row_spacings(GTK_TABLE(four),0);
	
	//将four装入vbox
  	gtk_box_pack_start(GTK_BOX(vbox),four,FALSE,TRUE,0);
	
	//建立关闭按钮，并设置其位置及大小
  	close = gtk_button_new_with_label("关闭");
	gtk_table_attach_defaults(GTK_TABLE(four),close,2,3,0,1);

	//建立发送按钮，并设置其位置及大小
  	send=gtk_button_new_with_label("发送");
	gtk_table_attach_defaults(GTK_TABLE(four),send,3,4,0,1);

	//显示主窗口函数
  	gtk_widget_show_all(window); 
	
	
	strcpy(g_name,name);

	 g_signal_connect (G_OBJECT(window), "delete_event",G_CALLBACK (delete_event),(gpointer)g_name); 

	//回调发送函数
	g_signal_connect(G_OBJECT(send),"clicked",G_CALLBACK(Send_Message),(gpointer)id); 
	
	gtk_main();
}

GtkWidget * Dialog_Info(GtkWindow *parent, int id){
	GtkWidget *dialog;  
    GtkWidget *label;  
    GtkWidget *image;  
    GtkWidget *hbox;  
   
    char str_id[5];
    sprintf(str_id,"%d",id);
#ifndef SCHEMALESS_WINDOW  
    dialog = gtk_dialog_new_with_buttons("Notice",parent,GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);  
#else  
    dialog = gtk_dialog_new_with_buttons("Notice",parent,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);  
#endif    
    gtk_dialog_set_has_separator(GTK_DIALOG(dialog),FALSE);  
    char str[70]={0};
    strcat(str,"Register Successfully!\nYour ID: ");
    strcat(str,str_id);
    strcat(str," .\nPlease Remeber It!");

    label = gtk_label_new(str); 
 
   
    image = gtk_image_new_from_stock(GTK_STOCK_DIALOG_INFO,GTK_ICON_SIZE_DIALOG);  
      
    hbox = gtk_hbox_new(FALSE,5);  
    gtk_container_set_border_width(GTK_CONTAINER(hbox),10);  
    gtk_box_pack_start_defaults(GTK_BOX(hbox),image);  
    gtk_box_pack_start_defaults(GTK_BOX(hbox),label);  
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox),hbox);  
    gtk_widget_show_all(dialog);  
  
#ifndef SCHEMALESS_WINDOW  
    /*显示对话框*/  
    gtk_dialog_run(GTK_DIALOG(dialog));  
    gtk_widget_destroy(dialog);  
#else  
    g_signal_connect(G_OBJECT(dialog),"response",G_CALLBACK(gtk_widget_destroy),NULL);  
#endif  
  
}

void Destroy(GtkWidget *widget, gpointer *data)
{
	close(fd);
	gtk_main_quit ();
}
gint delete_event( GtkWidget *widget,GdkEvent  *event,gpointer userdata ){
	int i = 0;
	for(;i<count_online;i++){
		if(!strcmp(userdata,g_info[i].name)){
			g_info[i].flag = 0;
			break;
		}else
			continue;
	}
	return FALSE;
} 

