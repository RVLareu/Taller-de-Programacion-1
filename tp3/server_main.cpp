#include <utility>
#include <iostream>

#include "server.h"





/*main app from server side*/
int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    const char *servicename = argv[1];
    Server server;
    server.start_accepting(servicename);
    server.run();
    return 0;
}




