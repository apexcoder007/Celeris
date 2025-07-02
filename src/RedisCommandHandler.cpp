#include "include/RedisCommandHandler.h"
#include <vector>
#include <sstream>
#include <algorithm>

std::vector<std::string> parseRespCommand(const std::string &input){
    std::vector<std::string> tokens;
    if(input.empty())
        return tokens;
    if(input[0] != '*'){
        std::istringstream iss(input);
        std::string token;
        while(iss >> token){
            tokens.push_back(token);
        }
        return tokens;
    }
    size_t pos = 0;
    if(input[pos] != '*')
        return tokens;
    pos++;

    size_t crlf = input.find("\r\n", pos);
    if(crlf == std::string::npos)
        return tokens;

    int numElements = std::stoi(input.substr(pos, crlf - pos));
    pos = crlf + 2;

    for (int i = 0; i < numElements; ++i){
        if(pos > input.size() || input[pos] != '$')
            break;
        pos++;
        crlf = input.find("\r\n", pos);
        if(crlf == std::string::npos)
            break;
        int len = std::stoi(input.substr(pos, crlf - pos));
        pos = crlf + 2;

        if(pos + len > input.size())
            break;
        std::string token = input.substr(pos, len);
        tokens.push_back(token);
        pos += len + 2;
    }
    return tokens;
}

RedisCommandHandler::RedisCommandHandler(){}

std::string RedisCommandHandler::processCommand(const std::string &commandLine){
    auto tokens = parseRespCommand(commandLine);
    if(tokens.empty())
        return "-Error: Empty command\r\n";
    std::string cmd = tokens[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    std::ostringstream response;

    return response.str();
}