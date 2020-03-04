#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

int main(int argc, char const *argv[]){
	
	char server_resp[256];

	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9003);
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

	int connect_status;
	if( (connect_status = connect(client_socket, (struct sockaddr *) &address, sizeof(address) ) ) < 0)
		printf("Connecting ended up with an error");

	
	
	recv(client_socket, &server_resp, sizeof(server_resp), 0);
	//printf("Server response was %s", server_resp);
	char output[256] = "Server response was : ";
	strcat(output, server_resp); 
	write(1, output, sizeof(output));
	close(client_socket);

}