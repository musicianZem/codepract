#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main() {
    int portNO = 8000;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
   
    if( sockfd < 0 ) {
        cout << "Create Socket Problem" << endl;
        return 0;
    }

    cout << "Socket Created\n";

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNO);


    int bindStatus = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if( bindStatus < 0 ) {
        cout << "Binding Problem" << endl;
        return 0;
    }

    cout << "Binding Correctly\n";
    cout << "Waiting for Client.....\n";

    listen(sockfd, 5);
    socklen_t clientLen = sizeof(cli_addr);
    int new_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clientLen);
    if( new_sockfd < 0 ) {
        cout << "Accept Problem" << endl;
        return 0;
    }

    cout << "Client join this PORT for chat..\n";
    cout << "Client will Send some Message. Answer the Question.\n";

    while( true ) {
        bzero(buffer, 256);
        int N = read(new_sockfd, buffer, 255);
        if( N < 0 ) {
            cout << "Reading from Socket Problem" << endl;
            return 0;
        }

        if( buffer[0] == '!' ) {
            cout << "Client quit Chat" << endl;
            break;
        }

        cout << "Client >> " << buffer << endl;

        cout << "Enter Message to Client : ";
        bzero(buffer, 256);
        scanf("%s", buffer);

        N = write(new_sockfd, buffer, strlen(buffer));
        
        if( buffer[0] == '!' ) break;
    }
    close(new_sockfd);
    close(sockfd);
    return 0;
}
