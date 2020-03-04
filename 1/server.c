#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

int main(int argc, char const *argv[]){
	
	char group[128][256] = {};
	int groups_len = 0;
	strcpy(group[0], "Group 0");
	groups_len = 1;
	//strcpy(group[1], "Group 1000");

	int serv_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9001);
	//inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(serv_socket, (struct sockaddr *) &address, sizeof(address));

	listen(serv_socket, 1024);

	int client_socket = accept(serv_socket, NULL, NULL);
	
	while(1){		

		char client_msg[128] = {};

		recv(client_socket, &client_msg, sizeof(client_msg), 0);

		if(strncmp(client_msg, "show groups", strlen("show groups")) == 0){
			send(client_socket, group, sizeof(group), 0);
		}

		if(strncmp(client_msg, "create group", strlen("create group")) == 0){
			char inp_grp_name[256] = {};
			recv(client_socket, &inp_grp_name, sizeof(inp_grp_name), 0);
			write(1, inp_grp_name, sizeof(inp_grp_name));
			write(1, "asf", sizeof("asf"));
			strncpy(group[groups_len], inp_grp_name, sizeof(inp_grp_name));
			groups_len++;
		}
		if(strncmp(client_msg, "log off", strlen("log off")) == 0){
			close(client_socket);
		}

	}

	close(serv_socket);

}