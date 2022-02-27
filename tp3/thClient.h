#include "thread.h"
#include "socket.h"
#include "protocol.h"
#include <atomic>
#include <map>
#include <string>
#include <mutex>

#ifndef THCLIENT_H
#define THCLIENT_H

class ThClient : public Thread {
    private:
        Socket peer;
        
        std::map<std::string, ProtectedQueue>& msgs_queue;
        
        std::atomic_bool is_running;
        
        std::atomic_bool keep_talking;
        
        Protocol protocol;
        
        std::mutex mutex;
        
    public:
        ThClient(Socket socket, std::map<std::string, ProtectedQueue>& msgs_queue);
        
        bool is_dead();
        
        virtual void run() override;
        
        void  process_define_command(Socket& client_socket);
        
        void process_push_command(Socket& client_socket);
        
        void process_pop_command(Socket& client_socket);
        
        void execute_command(char command, Socket& client_socket);
        
        ~ThClient();
};

#endif
