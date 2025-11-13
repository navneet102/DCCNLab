#include <sys/socket.h>
#include <netinet/in.h>

#include <bits/stdc++.h>

#define BUFFER_SIZE 256

int main(){
    //Make socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    //Make servAddr
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);
    //Bind
    bind(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    //Listen
    listen(sock_fd, 5);
    //Make new socket

    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    int new_sock_fd = accept(sock_fd, (struct sockaddr *) &cli_addr, &cli_len);
    //Repeate till ends

    char buffer[BUFFER_SIZE];

    while(1){
        bzero(buffer, BUFFER_SIZE);
        read(new_sock_fd, buffer, BUFFER_SIZE-1);
        std::cout << "Recieved message " << buffer;

        write(new_sock_fd, buffer, strlen(buffer));
    }

    return 0;
}