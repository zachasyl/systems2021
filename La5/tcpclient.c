// Note: I recommend implementing the tcpserver.c first.
//
// Compile with: gcc tcpclient.c -o tcpclient
//
// Implement tcp client below.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>
#include <netinet/in.h>
main(){
int client_socket;


if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Socket creation error \n");
	}


struct sockaddr_in server_address;

server_address.sin_family = AF_INET;

server_address.sin_port = htons(9002);

server_address.sin_addr.s_addr = htons(INADDR_ANY);

int connection_status;


if( (connection_status = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address))) <0 ){
		printf("%d Connection unsuccessful\n", connection_status);
		close(client_socket);
		exit(0);	
	}else{
		printf("Connected successfully\n");
	}

char server_response[256];
	recv(client_socket, &server_response, sizeof(server_response), 0);



	printf("The server sent the data: %s\n",server_response);



	close(client_socket);
return 0;
}
