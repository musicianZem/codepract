#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

int main() {
    int portNO = 8000;

    size_t bufferSize = 256;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if( sockfd < 0 ) {
        cout << "Create Socket Problem" << endl;
        return 0;
    }

    server = gethostbyname("localhost");
    if( server == NULL ) {
        cout << "NO SUCH HOST" << endl;
        return 0;
    }

    // bzero((char *)serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portNO);
    if( connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ) {
        cout << "Connecting Error" << endl;
        return 0;
    }
    while( true ) {
        bzero(buffer, 256);
        cout << "Enter Message : ";
        scanf("%s", buffer);
        if( buffer[0] == '!' ) break;

        int N = write(sockfd, buffer, strlen(buffer));
        if( N < 0 ) { 
            cout << "Writing to Socket Problem" << endl;
            cout << sockfd << " " << buffer << " " << strlen(buffer) << endl;
            return 0;
        }
        bzero(buffer, 256);
        N = read(sockfd, buffer, 255);
        if( N < 0 ) {
            cout << "Reading from Socket Problem" << endl;
            return 0;
        }
        if( buffer[0] == '!' ) {
            cout << "Server quit Chat" << endl;
            break;
        }
        cout << "Server : " << buffer << endl;
        close(sockfd);
    }

    return 0;
}
