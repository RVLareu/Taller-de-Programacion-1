#include <vector>
#include <iostream>
#include <utility>
#include <map>


#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>


#include "protectedQueue.h"
#include "socket.h"
#include "thAccepter.h"

ThAccepter::ThAccepter(std::map<std::string, ProtectedQueue>& msgs_queue) : 
                                    msgs_queue(msgs_queue) {
}

void ThAccepter::initialize(const char* servicename) {
    Socket socket;
    socket.bind_and_listen(NULL, servicename);
    this->socket = std::move(socket);
}


void ThAccepter::run() {
    while (1) {
        Socket client_socket(-1);
        try {
            client_socket = socket.accept();
        } catch (std::invalid_argument const& ex) {
            break;
        }
        ThClient* client = new ThClient(std::move(client_socket), std::ref(this->msgs_queue));
        clients.push_back(client);
        client->start();
        check_dead_clients();
    }
}


void ThAccepter::check_dead_clients() {
    std::list<ThClient*>::iterator it;
    for (it = clients.begin(); it != clients.end(); ++it) {
        if (!(*it)->is_dead()) {
            it = clients.erase(it);
            delete *it;
        }
    }
}


ThAccepter::~ThAccepter() {
    for (ThClient* client : clients) {
        delete client;
    }    
    this->socket.close();
    this->join();
}



