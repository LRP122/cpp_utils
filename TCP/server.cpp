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

    /* We create a socket, make it reusable, bind it to the network, allow it to listen to network connections and allow them
    We then can send information with clients back and forth*/
    if (argc < 2){
        std::cout << "Please enter a port number between 2000 and 16000" << "\n";
        exit(1);
    }

    int socket_fd, client_fd, port_no;
    port_no = atoi(argv[1]);

    if (2000 > port_no || port_no > 16000) {
        std::cout << "Please enter a port number between 2000 and 16000" << "\n";
        exit(1);
    }

    

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    fd_errorcheck(socket_fd,"Error on creating socket");

    int reuse = 1;
    int option_fd = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    fd_errorcheck(option_fd,"Error on changing reuse options");

    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_addr.s_addr = INADDR_ANY;
    server_adress.sin_port = htons(port_no);

    int bind_fd = bind(socket_fd, (struct sockaddr *) &server_adress, sizeof(server_adress));

    if (bind_fd != 0){
        std::cerr << "Can't bind to port " << port_no << "\n";
        exit(1);
    }

    int listen_fd = listen(socket_fd, 2);
    if (listen_fd != 0){
        std::cerr << "Can't listen for a client to connect...\n";
        exit(1);
    }
    else{
        std::cout << "Listening for a client to connect...\n";
    }

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    client_fd = accept(socket_fd, (struct sockaddr *) &client_addr,(socklen_t *) &client_addr_len);
    fd_errorcheck(client_fd, "Client can't connect to server");

    int y;
    read(client_fd, &y, sizeof(y));
    std::cout << "Received " << ntohl(y) << " from client \n";

    int new_num = htonl(25);
    write(client_fd, &new_num, sizeof(new_num));
    std::cout << "Sent " << new_num << " with size " << sizeof(new_num) << std::endl;

    close(socket_fd);
    close(client_fd);
    std::cout << "Server is closed, script ran sucessfully";

    return(0);
}

