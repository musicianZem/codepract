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

typedef struct {
    int msgLength;
    char *msg;
}__attribute__((packed)) mPacket;

void exitWithError(const char* errMsg) {
    printf("%s\n", errMsg);
    exit(-1);
}

int getSocketDescriptor() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

int main() {
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
    mPacket packet;

    char *arr = new char[101];

    while( true ) {
        string s; getline(cin, s);
        int L = s.length();

        char *arr = new char[L+1];
        for(int i=0; i<L; i++) {
            arr[i] = s[i];
        }
        arr[L] = '\0';

        // input    // pass for practice
        // change to char *
        // write( sockfd, (void *) arr , len ); // len : sizeof( char* ) * count is right
        printf("%s is inserted\n", arr);

        write( sockfd, (void *) arr, L);
    }

    close(sockfd);
    return 0;
}






