#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <arpa/inet.h>
#include <string.h>
#include <functional>

#include "client.h"


Client::Client(const char* hostname, const char* servicename) {
    this->socket.connect(hostname, servicename);
}

void Client::start() {
    for (std::string line; std::getline(std::cin, line);) {
        std::vector<std::string> splited_line = split_line(std::move(line));
        if (process_commands(splited_line)) {
            break;
        }
    }
}

int Client::process_commands(std::vector<std::string> splited_line) {
    if (splited_line[0] == "define") {
        return process_define(std::move(splited_line[1]));
    } else if (splited_line[0] == "push") {
        return process_push(std::move(splited_line[1]),
                                 std::move(splited_line[2]));
    } else if (splited_line[0] == "pop") {
        return process_pop(std::move(splited_line[1]));
    } else if (splited_line[0] == "exit") {
        this->socket.close();
        return 1;
    } else {
        std::cout << "wrong command, try again\n";
    }
    return 0;
}
int Client::process_define(std::string splited_line) {
    return this->protocol.send_command("d", 
                                    std::move(splited_line), 
                                        std::ref(this->socket));
}

int Client::process_push(std::string splited_line_1, std::string splited_line_2) {
    if (this->protocol.send_command("u",
                         std::move(splited_line_1), 
                            std::ref(this->socket)) == 1) {
       return 1;
    }
    this->protocol.send_msg(std::ref(this->socket),
                                     std::move(splited_line_2));
    return 0;
}

int Client::process_pop(std::string splited_line) {
    if (this->protocol.send_command("o",
                                     std::move(splited_line),
                                         std::ref(this->socket)) == 1) {
        return 1;
    }
    std::vector<char> msg = 
        this->protocol.receive_name_lenght(std::ref(this->socket));
    std::cout << msg.data() << '\n'; 
    return 0;
}

std::vector<std::string> Client::split_line(std::string line) {
    std::vector<std::string> tokens;
    std::stringstream ss(std::move(line));
    std::string token;
    while (ss >> token) {
        tokens.push_back(token.c_str());
    }
    return std::ref(tokens);
}
