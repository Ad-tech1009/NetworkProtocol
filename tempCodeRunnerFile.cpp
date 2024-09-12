e) {
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