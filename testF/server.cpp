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
    char *msg;
    int msgID;
} mPacket;

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

    mPacket *p = new mPacket;

    while(true) {
        char *buf = new char[5];
        memset(buf, 0, sizeof(buf));
        cout << endl << endl << "wait for client..\n";
        int pSize = read(new_sockfd, (void *)buf, 4);
        cout << buf << endl;

        pSize = atoi(buf);

        cout << "pSize = " << pSize << endl;

        int packetSize = (int)buf[0];
        if( packetSize == 0 ) break;
        cout << "receive packet Size = " << packetSize << endl;
        
        free(buf);
        buf = new char[packetSize];
        pSize = read(new_sockfd, (void *)buf, packetSize);
        char const *newText = buf;

        printf("%s", (char*)buf);
        cout << "\n...\n";
        for(int i=0; i < packetSize; i++) {
            printf("%c",(char)buf[i]);
        }
        cout << "\n...\n";
        for(int i=0; i<packetSize; i++) {
            printf("%x", buf[i]);
        }


        cout << "\nend\n";

        int charSize = 1;
        free(buf);

        /*p = (mPacket *)buf;
        if( pSize > 0 ) {
            cout << p->msg << endl;
        }
        cout << " unit end\n";*/
    }

    close(new_sockfd);
    close(sockfd);
    return 0;
}
