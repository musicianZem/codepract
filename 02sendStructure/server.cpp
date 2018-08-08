/* Server */
// send a structure with socket.
// 1. Read line with string ( C++ )
// 2. Create Send Structure.
// 3. Send a Structure.
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

typedef struct {
    int msgLength;
    char msg[0];
}__attribute__((packed)) mPacket;

void exitWithError(const char* errMsg) {
    printf("%s\n", errMsg);
    exit(-1);
}

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

    cout << sizeof(mPacket) << "\n";
    listen(sockfd, 5);
    socklen_t clientLen = sizeof(cli_addr);
    int new_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clientLen);
    if( new_sockfd < 0 ) {
        cout << "Accept Problem" << endl;
        return 0;
    }

    cout << "Client join this PORT for chat..\n";
    cout << "Client will Send some Message. Answer the Question.\n";
    int pSize = 0;

    mPacket *packet;

    char buf[5];
    while(true) {
        memset(buf, 0, sizeof(buf));

        int msgLength;
        int n = read(new_sockfd, (void *) &msgLength, sizeof(int));
        packet = (mPacket *)malloc(sizeof(int) + (sizeof(char)*(msgLength+1)));
        packet->msgLength = msgLength;
        n = read(new_sockfd, (void *)packet->msg, msgLength+1);

        if( msgLength == 4 && packet->msg[0] == 'Q' && packet->msg[1] == 'U' && packet->msg[2]
            == 'I' && packet->msg[3] == 'T' ) {
            cout << "Client Exit Program" << endl;
            close(new_sockfd);
            close(sockfd);
            break;
        }
        cout << packet->msgLength << " \"" << packet->msg << "\"\n";
    
        buf[4] = '\0';

        printf(">>%s\n", buf);
        free(packet);
    }

    close(new_sockfd);
    close(sockfd);
    return 0;
}
