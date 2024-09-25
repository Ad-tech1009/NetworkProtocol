
# HTTP Server Implementation in Unix-based Systems

This repository provides a step-by-step tutorial on how to build a basic HTTP server from scratch in Unix-based systems. It starts with a simple TCP server and client to facilitate terminal-based communication and concludes with the implementation of an HTTP server.

## Table of Contents

1. [Overview](#overview)
2. [Basic TCP Communication](#basic-tcp-communication)
   - [TCP Server](#tcp-server)
   - [TCP Client](#tcp-client)
3. [HTTP Server](#http-server)
4. [How to Run](#how-to-run)
   - [Running the TCP Server and Client](#running-the-tcp-server-and-client)
   - [Running the HTTP Server](#running-the-http-server)
5. [Contributing](#contributing)

## Overview

This project serves as a foundational tutorial for beginners who wish to understand how communication protocols like TCP and HTTP work at the socket level. The steps begin with establishing a TCP connection between a server and a client and gradually evolve into building a complete HTTP/1.1-compliant server.

## Basic TCP Communication

Before we dive into the HTTP server implementation, it’s essential to understand how a basic TCP server-client interaction works. The provided `tcp_server.c` and `tcp_client.c` files establish a basic communication link between two systems over the terminal.

### TCP Server

The `tcp_server.c` file demonstrates how to:
- Create a TCP socket.
- Bind it to a specific port.
- Accept incoming client connections.
- Exchange messages between the server and the client.

### TCP Client

The `tcp_client.c` file serves as a counterpart to the server, allowing:
- The client to establish a connection to the TCP server.
- Communication via the terminal.

## HTTP Server

The `httpserv.c` file is the culmination of this project. It demonstrates:
- How to implement a basic HTTP/1.1 server.
- Handling different types of HTTP requests (GET, POST, etc.).
- Responding to client requests with appropriate status codes and content.

### Features:
- Basic request parsing (method, path, protocol).
- Handling simple file serving.
- Sending appropriate HTTP responses.

This HTTP server is minimal and intended to give a deep understanding of the inner workings of HTTP without the complexities of modern web servers.

## How to Run

### Running the TCP Server and Client

1. **Compile the server and client:**
   ```bash
   gcc tcp_server.c -o tcp_server
   gcc tcp_client.c -o tcp_client
   ```

2. **Start the TCP server:**
   ```bash
   ./tcp_server
   ```

3. **Connect the TCP client to the server:**
   ```bash
   ./tcp_client
   ```

4. The client and server can now exchange messages via the terminal.

### Running the HTTP Server

1. **Compile the HTTP server:**
   ```bash
   gcc httpserv.c -o httpserv
   ```

2. **Run the HTTP server:**
   ```bash
   ./httpserv
   ```

3. You can now send HTTP requests (e.g., via a browser or a tool like `curl`) to the server running on the specified port (default is usually 8080). Example:
   ```bash
   curl http://localhost:8080
   ```

## Contributing

Feel free to contribute to this project by submitting a pull request or opening an issue.

---

Happy Coding!
