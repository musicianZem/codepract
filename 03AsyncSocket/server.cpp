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

typedef struct { // Used before get mData
    uint8_t cmdType;
    uint8_t fileName[64];
}__attribute__((packed)) mCmdT;

typedef struct { // Real Data
    uint32_t dataLength;
    uint8_t data[0];
}__attribute__((packed)) mData;

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
    if( sockfd < 0 ) exitWithError("Create Socket Problem");

    cout << "Socket Created\n";

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNO);


    int bindStatus = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if( bindStatus < 0 ) exitWithError("Binding Problem");

    cout << "Binding Correctly\n";
    cout << "Waiting for Client.....\n";

    cout << sizeof(mPacket) << "\n";
    listen(sockfd, 5);
    socklen_t clientLen = sizeof(cli_addr);

    int new_sockfd = -1;
    while( (new_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clientLen)) < 0 );
    fcntl(new_sockfd, F_SETFL, O_NONBLOCK);

    cout << "Client join this PORT for chat..\n";
    cout << "Client will Send some Message. Answer the Question.\n";
    int pSize = 0;

    mCmdT *cmdData = new mCmdT;
    mData *realData;

    memset(buffer, 0, sizeof(buffer));


    while(true) { // get Command Data
        int n = read(new_sockfd, (void *) cmdData, sizeof(mCmdT));
        if( n < 0 && errno == EAGAIN ) {
            // If this condition passes, there is no data to be read
            continue;
        }
        else if( n > 0 ) {
            if( cmdData->cmdType == 'f' ) {
                // ready for get real data.
                break;

                // Otherwise, you're good to go and buffer should contain "count" bytes.
            }
        }
        else {
            break;
            // Some other error occurred during read.
        }
    }

    while( true ) { // get realData's length
        int msgLength;
        int n = read(new_sockfd, (void *) &msgLength, sizeof(uint32_t));
        if( n < 0 && errno == EAGAIN ) {
            // NO DATA. WAIT.
            continue;
        } else if( n > 0 ) {
            realData = (mData *)malloc( sizeof(uint32_t) + (sizeof(uint8_t) * (msgLength+1)) );
        } else {
            // some error occur
            break;
        }
    }

    // #SAVE
    // have to change.
    int storeOffset = 0;
    while( true ) { // get realData.
        int n = read(new_sockfd, (void *) buffer, sizeof(buffer));
        if( n < 0 && errno == EAGAIN ) {
            // NO DATA. WAIT.
            continue;
        } else if( n < 0 ) {
            for(int i = storeOffset; i < storeOffSet + n; i++) {
                realData->data[i] = buffer[i-storeOffset];
            }
        } else {
            // some error.
            break;
        }
    }

    close(new_sockfd);
    close(sockfd);
    return 0;
}
