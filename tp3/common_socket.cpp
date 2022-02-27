#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdexcept>
#include <iostream>


#include "socket.h"

Socket::Socket() {}

/*creates socket with AF_INET, SOCK_STREAM*/
Socket::Socket(int file_desc) {
    this->fd = file_desc;
}

void Socket::close() {
    if (this->fd != -1) {
        shutdown(this->fd, SHUT_RDWR);
        ::close(this->fd);  
    }
}

/*binds socket and is set to listen up to 8. Uses
getaddrinfo, setsockopt(), bind() and liste()
*/
void Socket::bind_and_listen(const char *host, const char *service) {
    struct addrinfo *ptr = getAddrinfo(host, service, AI_PASSIVE);
    this->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    try {
        if (this->fd == -1) {
            throw std::invalid_argument("error socket()");
        }
    } catch (std::invalid_argument const& ex) {
        std::cout << ex.what() << '\n';
    }
    int val = 1;  
    setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    bind(this->fd, ptr->ai_addr, ptr->ai_addrlen);
    freeaddrinfo(ptr);
    listen(this->fd, 8);
}

/*accepts an incomming socket (peer)*/
Socket Socket::accept() {
    int file_desc = ::accept(this->fd, NULL, NULL);
    if (file_desc == -1) {
        throw std::invalid_argument("error accepting");
    }
    return std::move(Socket(file_desc));
}

struct addrinfo* Socket::getAddrinfo(const char *host, const char * service, int ai_flags) {
    struct addrinfo hints;
    struct addrinfo *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;       
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = ai_flags;
    if (getaddrinfo(host, service, &hints, &ptr) != 0) {
        return nullptr;
    }
    return ptr;
}



/*connects to socket (from server). Uses getaddrinfo, socket()
and connect()
*/
void Socket::connect(const char *host, const char *service) {
    struct addrinfo *ptr;
    struct addrinfo *aux;
    bool connected = false;
    ptr = getAddrinfo(host, service, 0);
    aux = ptr;
    for (; aux && connected == false; aux = aux->ai_next) {
        int e = 0;
        this->fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        e = ::connect(this->fd, aux->ai_addr, aux->ai_addrlen);
        connected = (e != -1);
    }
    freeaddrinfo(ptr);
}


int Socket::send_msg(const char *buffer, size_t length){
    size_t sent = 0;
    bool is_the_socket_valid = true;
    while (sent < length && is_the_socket_valid) {
        int s = 0;
        s = send(this->fd, &buffer[sent], 1, MSG_NOSIGNAL);
        if (s == 0 || s == -1) {
            is_the_socket_valid = false;
        } else {
            sent += s;
        }
    }
    if (is_the_socket_valid == false) {
        return 1;
    }
    return 0;
}

int Socket::receive_msg(std::vector<char>& buffer, size_t length){
    size_t received = 0;
    bool is_the_socket_valid = true;
    while (received < length && is_the_socket_valid) {
        int s = 0;
        s = recv(this->fd, &buffer[received], 1, 0);
        if (s == 0 || s == -1) { 
            is_the_socket_valid = false;
        } else {
            received += s;
        }
    }
    if (is_the_socket_valid == false) {
        return 1;
    }
    return 0;
}


Socket::Socket(Socket &&other) {
    if (this != &other) {
        this->fd = other.fd;
        other.fd = -1;
    }
}

/*destroys socket*/
Socket::~Socket() {
    if (this->fd != -1) {
        ::shutdown(this->fd, SHUT_RDWR);
        ::close(this->fd);
    }
}

Socket &Socket::operator=(Socket &&other) {
    if (this != &other) {
        this->fd = other.fd;
        other.fd = -1;
    }
    return *this;
}
