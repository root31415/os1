#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

int main(int argc, char const *argv[]){
	
	char username[128];

	read(1, username, sizeof(username));

	
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9001);
	//inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	int connect_status;

	if( (connect_status = connect(client_socket, (struct sockaddr *) &address, sizeof(address) ) ) < 0)
		write(1, "Connecting ended up with an error", sizeof("Connecting ended up with an error"));

	while(1){

		char input[1024] = {};
		char server_resp[128][256] = {};
		read(1, input, sizeof(input));

		if(strncmp(input, "log off", strlen("log off")) == 0){
			//send(client_socket, input, sizeof(input));
			//break;
		}

		if(strncmp(input, "create group", strlen("create group")) == 0){
			send(client_socket, input, sizeof(input), 0);
			write(1, "ENTER YOUR GROUP NAME: ", sizeof("ENTER YOUR GROUP NAME: "));
			char inp_grp_name[256] = {};
			read(1, inp_grp_name, sizeof(inp_grp_name));
			send(client_socket, inp_grp_name, sizeof(inp_grp_name), 0);
		}

		if(strncmp(input, "show groups", strlen("show groups")) == 0){
			send(client_socket, input, sizeof(input), 0);
			recv(client_socket, &server_resp, sizeof(server_resp), 0);
			int k = 0;
			while(strlen(server_resp[k]) > 0){ 
				write(1, strcat(server_resp[k], "\n"), sizeof(strcat(server_resp[k],"\n")));
				k++;
			}
		}

	}

	close(client_socket);
	
}