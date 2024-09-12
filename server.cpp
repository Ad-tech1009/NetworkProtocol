#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

//for MSVC
// #pragma comment(lib, "Ws2_32.lib")
//for mingw
//g++ server.cpp -o server -lws2_32

int main() {

    // Set up DLL
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed"<<endl;
    }
    else{
        cout << "WSAStartup success"<<endl;
        cout <<"The status: "<< wsaData.szSystemStatus<<endl;
    }


    // Create TCP socket
    SOCKET server_socket = INVALID_SOCKET;
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        cout<< "Socket creation error :"<< WSAGetLastError()<<endl;
        WSACleanup();
        return 0;
    }else{
        cout<< "Socket creation success" <<endl;
    }


    // Bind socket
    // Setup the server address structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // IPv4
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Accept connections from any IP address
    server_address.sin_port = htons(8080); // Server port
    // Bind the socket to our specified IP and port
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        cout << "Bind failed :"<< WSAGetLastError() <<endl;
        closesocket(server_socket);
        WSACleanup();
        return 0;
    }else{
        cout << "Bind success" <<endl;
    }


    // Listen for incoming connections
    if (listen(server_socket, 1) == SOCKET_ERROR) { // Maximum 1 connection
        cout << "Listen failed :"<< WSAGetLastError() <<endl;
        closesocket(server_socket);
        WSACleanup();
        return 0;
    }else{
        cout << "Listen success , Waiting for incoming connections..."<<endl;
    }


    // Accept a connection
    // Create a new socket for the client
    SOCKET client_socket = INVALID_SOCKET;
    // struct sockaddr_in client_address;
    // int client_addr_size = sizeof(client_address);
    // cli ent_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_addr_size);
    client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == INVALID_SOCKET) {
        cout << "Accept failed :"<< WSAGetLastError() <<endl;
        closesocket(server_socket);
        WSACleanup();
        return 0;
    }else{
        cout << "Accept success"<<endl;
    }

    // // Read the request
    // int bytesReceived = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    // if (bytesReceived > 0) {
    //     buffer[bytesReceived] = '\0'; // Null-terminate the received data
    //     std::cout << "Request received:\n" << buffer << std::endl;
    // }

    // // Send a simple HTTP response
    // std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";
    // send(client_socket, response.c_str(), response.length(), 0);

    // Cleanup
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
