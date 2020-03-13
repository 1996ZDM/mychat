#include "Client.h"
int main(int argc,char *argv[]){

	
	pthread_mutex_init(&mux, 0);
	
	gtk_init(&argc, &argv);
	
	Connection_init();
	
	pthread_mutex_destroy(&mux);
	
	return 0;
}

