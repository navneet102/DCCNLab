#include <sys/socket.h>
#include <netinet/in.h> // For sockaddr_in

#include <bits/stdc++.h>

#define BUFFER_SIZE 256 // Fixed buffer size

int main() {
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    int portno, n;

    // Get port number from command line
    portno = 8080;

    // 1. Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Setup server address structure
    // bzero((char *) &serv_addr, sizeof(serv_addr)); // Clear structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    serv_addr.sin_port = htons(portno);     // Convert port to network byte order

    // 3. Bind socket
    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    // 4. Listen for connections
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);

    // 5. Accept a connection
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    printf("Client connected. Echoing messages...\n");

    // 6. Read from client and echo back
    while (1) {
        bzero(buffer, BUFFER_SIZE); // Clear buffer
        n = read(newsockfd, buffer, BUFFER_SIZE - 1); // Read from socket (-1 for null term)
        printf("Client: %s", buffer); // Print received message

        // Echo back to client
        n = write(newsockfd, buffer, strlen(buffer)); // Write back to socket
    }

    // 7. Close sockets (This part is unreachable in the infinite loop)
    close(newsockfd);
    close(sockfd);
    return 0;
}