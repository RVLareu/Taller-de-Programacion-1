#include <iostream>


#include "server.h"




Server::Server() : accepter(std::ref(this->msgs_queue)) {
}

void Server::start_accepting(const char* servicename) {
    this->accepter.initialize(servicename);
    this->accepter.start();
}


void Server::run() {
    std::string c = "n";
    std::string q = "q";
    while (c.compare(q) != 0) {
        std::cin >> c;
    }
}

