/*
 * A simple TCP client implementation in C for Unix-like systems
 * -------------------------------------------------------------
 *
 * This program connects to a TCP server on a specified hostname and port number.
 * It allows the user to send messages to the server and receive responses in real-time.
 * Communication continues until the client sends the message "Bye", at which point
 * the connection is terminated.
 * 
 * The program performs the following steps:
 * 1. Creates a socket for TCP communication.
 * 2. Connects to the server using the specified hostname and port number.
 * 3. Sends user-input messages to the server and receives the server's response.
 * 4. Terminates when the message "Bye" is received from the server.
 * 
 * Compilation:
 * - Compile using a standard GCC command: gcc -o client client.c
 * - Run the program by specifying the server hostname and port number: ./client <hostname> <port>
 * 
 * Usage:
 * - Example: ./client localhost 5000 if running on the same device as server
 * - use a port number greater than 1024 (check out more about when it is necessary and when it's not)
 * - The client sends string-based messages to the server, which the server processes and responds to.
 *
 * Error handling:
 * - The program uses an `error()` function to print error messages and exit the program in case of issues
 *   like socket creation, connection failure, or reading/writing errors.
 * 
 * Notes:
 * - The client reads user input via `stdin` and sends it to the server.
 * - The connection is closed when either side sends "Bye".
 */



#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// error function
void error(const char *str){
    perror(str);
    exit(1);
}

int main(int argc, char *argv[]){
    int sockfd, port_no, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[255];

    // both server hostname and port number must be provided as command line arguments
    if(argc < 3){
        fprintf(stderr, "Error with command line arguments.\n");
        exit(1);
    }

    // convert port number from string to integer
    port_no = atoi(argv[2]);

    // creating a TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Error opening socket");
    }

    // resolving the hostname to get server information
    server = gethostbyname(argv[1]);
    if(server == NULL) {
        fprintf(stderr, "Error, no such host.\n");
        exit(1);
    }

    // zero out the server address structure and initialize it
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    // copy the server's IP address to the address structure
    bcopy((char *) server->h_addr_list[0] , (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port_no); // set the server port number

    // attempt to connect to the server
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection failed.");
    }

    // continuous loop for communication with the server
    while(1){
        bzero(buffer, 255);  // clear the buffer

        // read a message from the user (client-side)
        fgets(buffer, 255, stdin);

        // send the message to the server
        n = write(sockfd, buffer, strlen(buffer));
        if(n < 0) error("Error on writing");

        bzero(buffer, 255);  // clear the buffer

        // read the server's response
        n = read(sockfd, buffer, 255);
        if(n < 0) error("Error reading.");
        printf("Server: %s", buffer);  // display the server's message

        // terminate the connection if the server responds with "Bye"
        int i = strncmp("Bye", buffer, 3);
        if(i == 0) break;
    }

    // close the socket
    close(sockfd);
    return 0;
}
