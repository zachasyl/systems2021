

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
int server_socket;
//install signal handler from A3

void sigint_handler(int sig){
	close(server_socket);
	write(1, "terminating via signal handler\n", 35);
	exit(0);
}


int main(){

	signal(SIGINT, sigint_handler);

	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;

	server_address.sin_port = htons(9004);

	server_address.sin_addr.s_addr = htons(INADDR_ANY);

	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	printf("Server bind()\n");
while(1){
	listen(server_socket, 27);

	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);


	char client_username[256];
	recv(client_socket, &client_username, sizeof(client_username), 0);
	printf("client has joined: %d\n", client_socket);  
	printf("%s\n", client_username);


	char server_message[256] = "You've reached the server";
	send(client_socket, server_message, sizeof(server_message), 0);



	while(1){
		char client_response[256];
		recv(client_socket, &client_response, sizeof(client_response), 0);

		printf("Message from %s received: %s", client_username, client_response);

	}
}

return 0;
}
