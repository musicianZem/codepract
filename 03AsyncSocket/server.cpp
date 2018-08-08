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
#include <fcntl.h>
#include <sys/stat.h>
#include <netinet/in.h>

using namespace std;

typedef struct {
    uint32_t msgLength;
    uint8_t msg[0];
}__attribute__((packed)) mPacket;

void exitWithError(const char* errMsg) {
    printf("%s\n", errMsg);
    exit(-1);
}

int main() {
    const int LENGTH = 1024;
    int portNO = 8000;
    char buffer[LENGTH];
    struct sockaddr_in serv_addr, cli_addr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    int flag = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flag | O_NONBLOCK);
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
    /*
    int new_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clientLen);
    if( new_sockfd < 0 ) {
        cout << "Accept Problem" << endl;
        return 0;
    }*/
    int new_sockfd = -1;
    while( (new_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clientLen)) <
        0 );
    fcntl(new_sockfd, F_SETFL, O_NONBLOCK);

    cout << "Client join this PORT for chat..\n";
    cout << "Client will Send some Message. Answer the Question.\n";
    int pSize = 0;

    mPacket *packet;

    memset(buffer, 0, sizeof(buffer));
    FILE *fp = fopen("SaveData.txt", "w");
    bool endFlag = true;
    while(true) {
        int n = read(new_sockfd, (void *) buffer, sizeof(char)*LENGTH);
        if( n > 0 ) {
            endFlag = false;
            fprintf(fp, "%s\n", buffer);
            cout << n << " " << buffer << " writed\n";
        } else {
            if( !endFlag ) break;
        }
    }
    cout << "end of file" << endl;

    close(new_sockfd);
    close(sockfd);
    return 0;
}
