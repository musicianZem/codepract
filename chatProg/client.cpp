#include <unistd.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>

const int PORT = 8080;

/*
    1. Create Socket
    2. Connect Server
    3. Chat

*/

int main() {
    struct sockaddr_in address, server_addr;
    int sock = 0, valread;
    char *msg = "This message is from client.....!!!!!!";
    char buffer[1024];
    
    /* 1. Create Socket */
    if( (sock = socket(AF_INET, SOCK_STREAM, 0) ) < 0) {
        printf("socket error\n");
        return 0;
    }
    
    memset(&server_addr, '0', sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if( inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        printf("Address Not supported\n");
        return 0;
    }

    printf(" Socket Create And Setting end. \n");

    /* 2. Connect Server */
    // connect(int socket, sockaddr addr, socklen_t socklen);
    if( connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0 ) {
        printf("Cannot Connect to Server...\n");
        return 0;
    }

    printf(" Connected! \n");

    /* 3. Chat */
    send(sock, msg, strlen(msg), 0);
    printf("I Send a msg, %s\n", msg);

    valread = read( sock, buffer, 1024 );
    printf("I received A Message From Server\n>>%s\n", buffer);

    printf("End of main... client exit\n");
    return 0;
}
