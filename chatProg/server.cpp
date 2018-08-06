#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/*
    1. Create Socket
    2. Set Socket
    3. Bind
    4. Listen
    5. Accept
    6. Chat
*/
int main() {
    sockaddr_in address;
    int opt = 1;
    int server_fd, new_socket;
    /* 1. Create Socket */

    if( (server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 ) {
        printf("make socket error\n");
        return 0;
    }

    /* 2. set Socket */
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));



    printf("exit main without ERROR\n");
    return 0;
}
