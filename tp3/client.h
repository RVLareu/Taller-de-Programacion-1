#include <map>
#include <vector>
#include <string>
#include "socket.h"
#include "protocol.h"

#ifndef CLIENT_H
#define CLIENT_H

class Client {
    private:
        Socket socket;
        std::vector<std::string> split_line(std::string line);
        Protocol protocol;
    public:
        Client(const char* hostname, const char* servicename);
        void start();
        int process_define(std::string splited_line);
        int process_push(std::string splited_line_1, std::string splited_line_2);
        int process_pop(std::string splited_line);
        int process_commands(std::vector<std::string> splited_line);
};

#endif
