#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>

const int PORT = 8080;

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
    int addLen = sizeof(address);
    int opt = 1;
    int server_fd, new_socket, valread;
    char buffer[1024]; 
    char *msg = "Some Message...!!!@@@AAA";
    /* 1. Create Socket */
    // socket(domain, type, protocol)
    // server_fd = socket(AF_INET, SOCK_STREAM, 0)
    if( (server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 ) {
        printf("make socket error\n");
        return 0;
    }

    /* 2. set Socket */
    // int setsocket(int sockfd, int level, int optName, optval, optlen)
    // setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if( setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) ) {
        printf("socket setting error\n");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    /* 3. Binding */
    // int bind(int sockfd, sockaddr* addr, addrlen);
    // bind(server_fd, address, addLen);
    if( bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0 ) {
        printf("binding error\n");
        return 0;
    }

    /* 4. Listen */
    // int listen(int sockfd, int backlog);
    // listen(server_fd, over 3 integer);
    if( listen(server_fd, 3) < 0 ) {
        printf("listen...\n");
        return 0;
    }
    
    /* 5. Accept */
    // int = accept(int sockfd, sockaddr* addr, addlen);
    if( new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*) &addLen) < 0) {
        printf("Accept.........\n");
        return 0;
    }
    
    /* 6. Chat */ 

    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, msg, strlen(msg), 0);

    printf("exit main without ERROR\n");

    return 0;
}
