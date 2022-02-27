#include "client.h"


/*main app from clients side*/
int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }
    const char *hostname = argv[1];
    const char *servicename = argv[2];

    Client client(hostname, servicename);
    client.start();
    return 0;
}    
