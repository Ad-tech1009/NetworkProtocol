#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <tchar.h>     // For _T() macro (if using it)

using namespace std;

//for MSVC
// #pragma comment(lib, "Ws2_32.lib")
//for mingw
//g++ client.cpp -o client -lws2_32

// void handleClient(SOCKET clientSocket) {
//     char buffer[4096];
//     int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
//     if (bytesReceived > 0) {
//         // Convert the received data into a string
//         std::string request(buffer, bytesReceived);
//         std::cout << "Received request:\n" << request << std::endl;

//         // Simple parsing to extract the HTTP method and path
//         std::string method, path;
//         std::istringstream requestStream(request);
//         requestStream >> method >> path;

//         std::cout << "Method: " << method << std::endl;
//         std::cout << "Path: " << path << std::endl;

//         // Construct a simple HTTP response
//         std::string response =
//             "HTTP/1.1 200 OK\r\n"
//             "Content-Type: text/plain\r\n"
//             "Content-Length: 12\r\n"
//             "\r\n"
//             "Hello, World";

//         // Send the response back to the client
//         send(clientSocket, response.c_str(), response.length(), 0);
//     }

//     // Close the client socket
//     closesocket(clientSocket);
// }

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
    SOCKET client_socket = INVALID_SOCKET;
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == INVALID_SOCKET) {
        cout<< "Socket creation error :"<< WSAGetLastError()<<endl;
        WSACleanup();
        return 0;
    }else{
        cout<< "Socket creation success" <<endl;
    }


    // Connect to the server
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // IPv4
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Accept connections from any IP address
    server_address.sin_port = htons(8080); // Server port
    if(connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        cout << "Connect failed :"<< WSAGetLastError() <<endl;
        closesocket(client_socket);
        WSACleanup();
        return 0;
    }else{
        cout << "Connect success, Can start sending or recieving data..." <<endl;
    }

    // Main server loop: Accept and handle incoming connections
    // while (true) {
    //     SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &addrLen);
    //     if (clientSocket == INVALID_SOCKET) {
    //         std::cerr << "Accept failed\n";
    //         closesocket(serverSocket);
    //         WSACleanup();
    //         return 1;
    //     }

    //     // Spawn a new thread to handle the client
    //     // std::thread clientThread(handleClient, clientSocket);
    //     // clientThread.detach(); // Detach the thread to allow it to run independently
    // }

    // Cleanup
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
