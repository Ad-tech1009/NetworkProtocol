# TCP Server and Client in C++

This repository contains basic implementations of a TCP server and client using the Windows Sockets API (Winsock). These examples demonstrate how to set up a TCP server and client, including initialization, socket creation, binding, listening, and connection.

## Features

- **Server:**
  - Initializes Winsock.
  - Creates a TCP socket.
  - Binds the socket to a specified IP address and port.
  - Listens for incoming connections.
  - Accepts a single client connection.
  - Basic error handling and cleanup.

- **Client:**
  - Initializes Winsock.
  - Creates a TCP socket.
  - Connects to a specified server IP address and port.
  - Basic error handling and cleanup.

## Requirements

- **Operating System:** Windows
- **Compiler:** Microsoft Visual Studio or MinGW
- **Library:** Winsock2 (ws2_32.lib)

## Build Instructions

### Using Microsoft Visual Studio

1. Open the project in Visual Studio.
2. Ensure `Ws2_32.lib` is linked. This is typically done by including the following pragma directive in your code:
    ```cpp
    #pragma comment(lib, "Ws2_32.lib")
    ```
3. Build and run the server and client projects separately.

### Using MinGW

1. Open a terminal or command prompt.
2. Navigate to the directory containing your `server.cpp` and `client.cpp` files.
3. Compile the server:
    ```sh
    g++ server.cpp -o server -lws2_32
    ```
4. Compile the client:
    ```sh
    g++ client.cpp -o client -lws2_32
    ```
5. Run the server executable in one terminal:
    ```sh
    ./server
    ```
6. Run the client executable in another terminal:
    ```sh
    ./client
    ```

## Server Code Overview

1. **Initialize Winsock.**
2. **Create a TCP socket.**
3. **Bind the socket to a specific IP address and port.**
4. **Listen for incoming connections.**
5. **Accept a client connection.**
6. **Cleanup resources.**

## Client Code Overview

1. **Initialize Winsock.**
2. **Create a TCP socket.**
3. **Connect to the server using the specified IP address and port.**
4. **Cleanup resources.**
