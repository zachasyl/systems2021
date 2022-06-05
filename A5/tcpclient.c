

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>
#include <netinet/in.h>

int main(){
int client_socket;


	if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
                printf("\n Socket creation error \n");
        	}


	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;

	server_address.sin_port = htons(9004);

	server_address.sin_addr.s_addr = htons(INADDR_ANY);

	int connection_status;


	if( (connection_status = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address))) <0 ){
                printf("%d Connection unsuccessful\n", connection_status);
                close(client_socket);
                exit(0);
        }else{
                printf("Connected successfully\n");
        }

printf("What is your username?");
char client_username[256];
int len = 0;
fgets(client_username, sizeof(client_username), stdin);
send(client_socket, client_username, sizeof(client_username), 0);

while(1){
	printf("message:");
	char client_message[256];
	len = 0;
	fgets(client_message, sizeof(client_message), stdin);

	if (strncmp(client_message, "exit", 4) == 0){
		break;	
	}else{
	send(client_socket, client_message, sizeof(client_message), 0);

	char server_response[256];
        recv(client_socket, &server_response, sizeof(server_response), 0);

}
}
printf("exiting");
close(client_socket);
exit(0);
return 0;
}
