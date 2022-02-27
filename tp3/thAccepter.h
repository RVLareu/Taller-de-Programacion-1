
#include "socket.h"
#include "protectedQueue.h"
#include "thread.h"
#include "thClient.h"

#include <string>
#include <map>
#include <list>

#ifndef THACCEPTER
#define THACCEPTER

class ThAccepter : public Thread {
    private:
        std::map<std::string, ProtectedQueue>& msgs_queue;
        
        std::list<ThClient*> clients;
        
        Socket socket;
    public:
        explicit ThAccepter(std::map<std::string, ProtectedQueue>& msgs_queue);
        
        void initialize(const char* servicename);
        
        virtual void run() override;
        
        void check_dead_clients();
        
        ~ThAccepter();
};

#endif
