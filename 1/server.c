#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

int main(int argc, char const *argv[]){
	
	char group[128][32] = {};
	char client_msg[128];
	strcpy(group[0], "Group 0");
	//strcpy(group[1], "Group 1000");

	int serv_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9001);
	//inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(serv_socket, (struct sockaddr *) &address, sizeof(address));

	while(1){
		listen(serv_socket, 32);

		int client_socket = accept(serv_socket, NULL, NULL);

		recv(client_socket, client_msg, sizeof(client_msg), 0);

		if(strcmp(client_msg, "show groups")){
			send(client_socket, group, sizeof(group), 0);
		}
		
	}

	close(serv_socket);
}