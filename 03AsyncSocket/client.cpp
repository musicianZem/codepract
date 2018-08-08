/* Client */
// send a structure with socket.
// 1. Read line with string ( C++ )
// 2. Create Send Structure.
// 3. Send a Structure.
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

typedef struct { // Used before send mData
    uint8_t cmdType; // f:file another:error
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

int getSocketDescriptor() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

int main() {
    const int LENGTH = 1024;
    int sockfd;
    int portNO = 8000;
    const char* iaddress = "localhost"; 

    size_t bufferSize = 256;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if( (sockfd = getSocketDescriptor()) < 0 ) {
        exitWithError("Create Socket Problem");
    }

    server = gethostbyname(iaddress);
    if( server == NULL ) {
        exitWithError("NO SUCH HOST");
    }

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portNO);
    if( connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ) {
        exitWithError("Connecting Error"); 
    }

    cout << "Connected Server. Welcome\n";

    int msgID = 0;
    mPacket *packet;

    char arr[256];

    // Transfer File
    const char *filePath = "./sendTextFile.txt";
    FILE *fp = fopen(filePath, "r");
    int fileBlockSize;
    char fbuf[LENGTH];
    memset(fbuf, 0, sizeof(fbuf));

    if( fp == NULL ) {
        exitWithError("FILE NOT FOUND");
    }

    while( !feof(fp) ) {
        fscanf(fp, "%s", fbuf);
        cout << strlen(fbuf) << endl;
        write( sockfd, fbuf, strlen(fbuf) );
        printf("send \"%s\"\n", fbuf);
        memset(fbuf, 0, sizeof(fbuf));
    }

    close(sockfd);

    sleep(5);
    return 0;
}
