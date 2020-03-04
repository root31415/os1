#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

int main(int argc, char const *argv[]){
	
	char server_msg[256] = "Hello my client!!!";

	int serv_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9003);
	inet_pton(AF_INET, "127.0.0.2", &address.sin_addr);

	bind(serv_socket, (struct sockaddr *) &address, sizeof(address));

	while(1){
		listen(serv_socket, 32);

		int client_socket = accept(serv_socket, NULL, NULL);

		send(client_socket, server_msg, sizeof(server_msg), 0);
	}

	close(serv_socket);
}