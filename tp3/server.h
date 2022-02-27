#include <map>
#include <queue>
#include <vector>
#include <string>

#include "protectedQueue.h"
#include "socket.h"
#include "thAccepter.h"

#ifndef SERVER_H
#define SERVER_H


class Server {
    private:
        ThAccepter accepter;
        
        std::map<std::string, ProtectedQueue> msgs_queue;
        
        uint16_t recv_msg_len(std::vector<char> msg_lenght_buffer, Socket& socket);
        
        void process_define_command(Socket& client_socket);
        
        void process_push_command(Socket& client_socket);
        
        void process_pop_command(Socket& client_socket);
        
        void send_pop_result(Socket& client_socket, std::string msg);
        
    public:
        Server();
        
        void start_accepting(const char* servicename);
        
        void execute_command(char command, Socket& client_socket);
        
        void run();
        
        Socket accept();
};

#endif
