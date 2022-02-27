#include "string.h"
#include <string>
#include <arpa/inet.h>

#include "protocol.h"

Protocol::Protocol() {
}

/*
Receives 2 bytes, returns uint16_t lenght
*/
uint16_t Protocol::recv_msg_len(std::vector<char> msg_lenght_buffer, 
                                                        Socket& socket) {
    socket.receive_msg(msg_lenght_buffer, 2);
    uint16_t msg_lenght;
    memcpy(&msg_lenght, msg_lenght_buffer.data(), 2);
    msg_lenght = ntohs(msg_lenght);
    return msg_lenght;
}
/*
Recives a msg that is len + name/msg, returns name/msg
*/
std::vector<char> Protocol::receive_name_lenght(Socket& client_socket) {
    std::vector<char> name_lenght_buffer(2);
    uint16_t name_lenght = recv_msg_len(name_lenght_buffer, client_socket);
    std::vector<char> queue_name(name_lenght+1);
    client_socket.receive_msg(queue_name, name_lenght);
    return queue_name;
}
/*
sends msg. Returs 0 if OK, 1 if socket_error
*/
int Protocol::send_msg(Socket& client_socket, std::string msg) {
    int e = 0;
    uint16_t msg_lenght = msg.size();
    msg_lenght = htons(msg_lenght);
    char msg_lenght_buffer[2];
    memcpy(&msg_lenght_buffer[0], &msg_lenght, 2); 
    if (client_socket.send_msg(msg_lenght_buffer, 2)) {
        return 1;
    }
    e = client_socket.send_msg(msg.c_str(), ntohs(msg_lenght));
    return e;
}
/*
sends len + msg (pop result)
*/
void Protocol::send_pop_result(Socket& client_socket, std::string msg) {
    std::vector<char> msg_lenght_buffer(2);
    unsigned short msg_lenght = msg.size();
    msg_lenght = htons(msg_lenght);
    memcpy(&msg_lenght_buffer[0], &msg_lenght, 2);
    client_socket.send_msg(msg_lenght_buffer.data(), 2);
    client_socket.send_msg(msg.data(), ntohs(msg_lenght));
}
/*
sends command + msg. Returs 0 if OK, 1 if error
*/
int Protocol::send_command(const char* c,
                                 const std::string& splited_line,
                                     Socket& client_socket) {
    int e = 0;
    if (client_socket.send_msg(c, 1)) {
        return 1;
    }
    e = send_msg(client_socket, splited_line);
    return e;
 }

Protocol::~Protocol() {
}
