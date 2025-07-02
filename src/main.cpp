#include "../include/RedisServer.h"
#include <iostream>
#include <thread> 
#include <chrono> 

int main(int argc, char* argv[]){
    int port = 6379; //default port 
    if(argc>=2)
        port = std::stoi(argv[1]);
    RedisServer server(port);
    std::thread persistenceThread([](){
        while(true){
            std::this_thread::sleep_for(std::chrono::seconds(300));
        } });
    persistenceThread.detach();

    server.run();
    return 0;
}