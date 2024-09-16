#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include "error_handling.h"

void fd_errorcheck(int fd,const char* error_message);

int main(int argc, char** argv){

    //We need to create the client, tell it where the host lives and connect. Then we can send information back and forth
    int socket_fd, client_fd, port_no;
    port_no = atoi(argv[1]);

    client_fd = socket(AF_INET, SOCK_STREAM,0);
    fd_errorcheck(client_fd, "Could not set up client socket");

    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(port_no);
    int server_addr_len = sizeof(server_adress);

    if (inet_pton(AF_INET, "127.0.0.1", &server_adress.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported\n";
        return 1;
    }


    int connect_fd = connect(client_fd, (struct sockaddr *)&server_adress,sizeof(server_adress));
    //fd_errorcheck(connect_fd, "Could not connect to server");

    std::cout << "Connected sucessfully\n";
    int z;
    std::cout << "What integer do you want to send to the server? \n";
    std::cin >> z;

    int x = htonl(z); //host to network long
    write(client_fd, &x, sizeof(x));

    int y;
    read(client_fd, &y, sizeof(y));
    std::cout << "Received from server : " << ntohl(y) << " or " << y << std::endl; //network to host long

}
