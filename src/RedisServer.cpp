#include "../include/RedisServer.h"

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

static RedisServer* globalServer = nullptr;

RedisServer::RedisServer(int port) : port(port), server_socket(-1),running(true){
    globalServer = this;
}

void RedisServer::shutdown(){
    running = false;
    if(server_socket != -1){
        close(server_socket);
    }
    std::cout << "Server shut down successfully!\n";
}

void RedisServer::run(){
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0){
        std::cerr << "Error creating a server socket!\n";
        return;
    }
    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Error binding server socket!\n";
        return;
    }

    if (listen(server_socket, 10) < 0)
    {
        std::cerr << "Error listening on server socket!\n";
        return;
    }
    std::cout << "Redis server listening on port " << port << "\n";
}

