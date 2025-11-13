#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // For sockaddr_in
#include <netdb.h>      // For gethostbyname

#define BUFFER_SIZE 256 // Fixed buffer size

int main() {
    int clientSocket, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BUFFER_SIZE];
    char *hostname; // Renamed from 'host' to avoid conflict with `hostent`

    hostname = (char *)"127.0.0.1"; // Server hostname (e.g., 127.0.0.1)
    portno = 8080; // Server port number

    // 1. Create client socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Setup server address structure
    server = gethostbyname(hostname); // Get server IP by name
    // bzero((char *) &serv_addr, sizeof(serv_addr)); // Clear structure
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); // Copy IP
    serv_addr.sin_port = htons(portno); // Convert port to network byte order

    // 3. Connect to server
    connect(clientSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    printf("Connected to server. Enter message:\n");

    // 4. Read input, send to server, receive echo, print
    while (1) {
        printf("> ");
        bzero(buffer, BUFFER_SIZE); // Clear buffer
        fgets(buffer, BUFFER_SIZE - 1, stdin); // Read from keyboard (-1 for null term)

        // Send message to server
        n = write(clientSocket, buffer, strlen(buffer));

        bzero(buffer, BUFFER_SIZE); // Clear buffer for incoming message
        // Read echoed message from server
        n = read(clientSocket, buffer, BUFFER_SIZE - 1);
        printf("Server echo: %s", buffer);
    }

    // 5. Close socket (This part is unreachable in the infinite loop)
    close(clientSocket);
    return 0;
}