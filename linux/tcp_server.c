/*
 * A simple TCP server implementation in C for Unix-like systems
 * -------------------------------------------------------------
 *
 * This program initializes a TCP server that listens on a user-specified port
 * and communicates with a single client at a time. The server receives and
 * responds to messages from the client in a continuous loop until the client 
 * sends the message "Bye", at which point the connection is terminated.
 * 
 * The program performs the following steps:
 * 1. Creates a socket for TCP communication.
 * 2. Binds the socket to a specified port number.
 * 3. Listens for incoming client connection requests (with a limit of 3).
 * 4. Accepts a connection from a client and initializes a new socket for communication.
 * 5. Reads the client's messages and responds, echoing input from the server's stdin.
 * 6. Terminates when the client sends "Bye".
 * 
 * Compilation:
 * - Compile using a standard GCC command: gcc -o server server.c
 * - Run the program by specifying the port number as a command-line argument: ./server <port>
 * 
 * Usage:
 * - Example: ./server 5000
 * - The client can connect to this server using tools like `telnet` or a custom TCP client.
 *
 * Error handling:
 * - The program uses an `error()` function to print error messages and exit
 *   the program in case of issues like socket creation, binding, or reading/writing errors.
 * 
 * Notes:
 * - The server runs in an infinite loop until the client sends "Bye".
 * - The server expects string-based communication, reading and responding line by line.
 */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// error function
void error(const char *str){
    perror(str);
    exit(1);
}

int main(int argc, char *argv[]){
    // port number is needed as command line argument to start the server
    if(argc < 2){
        fprintf(stderr, "port number not provided. program terminated.\n");
        exit(1);
    }

    // initializing a TCP socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) error("Error opening socket.\n");

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));

    int port_no = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port_no);

    // binding or assigning a specific address to our initialized socket
    // it can start listening for connection requests only after binding
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("Binding error.\n");

    // listening for connections with a limit of 3
    listen(sockfd, 3);

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    // accepting a connection request and initializing a new socket for communication with the client 
    int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if(newsockfd < 0) error("Error accepting.\n");

    // buffer stores the server's response to any request by the client
    char buffer[255];

    // continuous loop for communication with the server
    while(1) {
        bzero(buffer, 255);
    
        // reading and displaying the request
        int n = read(newsockfd, buffer, 255);
        if(n < 0) error("Error reading.\n");

        printf("Client: %s\n", buffer);

	// reading data from the stream and writing it as the server's response
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if(n < 0) error("Error writing.\n");

	// the infinite loop of reading and writing terminates with "Bye"
        int i = strncmp("Bye", buffer, 3);
        if(i == 0) break;
    }
    
    // all initialized sockets are closed
    close(newsockfd);
    close(sockfd);
    return 0;
}