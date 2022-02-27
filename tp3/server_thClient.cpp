#include <map>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>

#include "protectedQueue.h"
#include "thClient.h"


ThClient::ThClient(Socket socket,
                 std::map<std::string,
                 ProtectedQueue>& msgs_queue) :
                     peer(std::move(socket)), 
                        msgs_queue(msgs_queue), 
                            is_running(true), keep_talking(true) {
}

bool ThClient::is_dead() {
    return is_running;
}

void ThClient::run() {
        while (keep_talking) {
            std::vector<char> command(1);
            if (this->peer.receive_msg(command, 1) == 1) {
                break;
            } else {
                this->execute_command(command[0], std::ref(this->peer));
            }  
        }
        is_running = false;
}

ThClient::~ThClient() {
    this->peer.close();
    this->join();
}


void  ThClient::process_define_command(Socket& client_socket) {
    std::vector<char> queue_name = 
        this->protocol.receive_name_lenght(client_socket);
    msgs_queue[queue_name.data()];
}

void ThClient::process_push_command(Socket& client_socket) {
    std::vector<char> queue_name = 
        this->protocol.receive_name_lenght(client_socket);
    std::vector<char> msg = this->protocol.receive_name_lenght(client_socket);
    std::lock_guard<std::mutex> lock(mutex);
    msgs_queue[queue_name.data()].push(msg.data());
}


void ThClient::process_pop_command(Socket& client_socket) {
    std::vector<char> queue_name = 
        this->protocol.receive_name_lenght(client_socket);
    std::lock_guard<std::mutex> lock(mutex);
    std::string msg = msgs_queue.at(queue_name.data()).get_front_if_posibble();
    this->protocol.send_pop_result(client_socket, msg);
}


void ThClient::execute_command(char command, Socket& client_socket) {
    if (command == 'd') {
        process_define_command(client_socket);
    } else if (command == 'u') {
        process_push_command(client_socket);
    } else if (command == 'o') {  
        process_pop_command(client_socket);
    }
}
