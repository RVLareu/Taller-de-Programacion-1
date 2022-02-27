#include "socket.h"
#include <vector>
#include <string>

class Protocol
{
private:
public:
    Protocol();
    uint16_t recv_msg_len(std::vector<char> msg_lenght_buffer, Socket& socket);

    std::vector<char> receive_name_lenght(Socket& client_socket);
    void send_pop_result(Socket& client_socket, std::string msg);
    int send_command(const char* c, const std::string& splited_line, Socket& client_socket);
    int send_msg(Socket& client_socket, std::string msg); 
    ~Protocol();
};

