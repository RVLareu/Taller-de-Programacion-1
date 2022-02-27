#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <vector>

#ifndef SOCKET_H
#define SOCKET_H



/* fd: file descriptor of the socket*/
class Socket {
    private:
        struct addrinfo* getAddrinfo(const char *host, const char * service, int ai_flags);
    public:
        int fd;
        Socket();
        explicit Socket(int file_desc);
        void close();
        /*binds and puts a socket to listen*/
        void bind_and_listen(const char *host, const char *service);
        /*accepts a socket*/
        Socket accept();
        /*connects a socket*/
        void connect(const char *host, const char *service);
        /*sends buffer*/
        int send_msg(const char *buffer, size_t length);
        /*receives buffer*/
        int receive_msg(std::vector<char>& buffer, size_t length);
        Socket(Socket &&other);
        Socket& operator=(Socket &&other);
        /*destroys socket*/
        ~Socket();
};
#endif


