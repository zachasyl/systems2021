// Compile with: gcc tcpserver.c -o tcpserver
//
// Implement tcp server below.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

main(){
int server_socket;

server_socket = socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in server_address;

server_address.sin_family = AF_INET;

server_address.sin_port = htons(9002); 

server_address.sin_addr.s_addr = htons(INADDR_ANY);

bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
printf("Server bind()\n");

listen(server_socket, 27);

int client_socket;
client_socket = accept(server_socket, NULL, NULL);

char server_message[256] = "You have reached the server";

send(client_socket, server_message, sizeof(server_message), 0);

close(server_socket);
return 0;
}











