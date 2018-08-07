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
    string msg;
    int msgID;
} SendStruct;

void exitWithError(const char* errMsg) {
    printf("%s\n", errMsg);
    exit(-1);
}

int getSocketDescriptor() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

string getMsg() {
    cout << "Enter Msg for send : ";
    string str;
    getline(cin, str);
    return str;
}

void makeMsgStruct(SendStruct &msgStruct) {
    static int id = 0;
    msgStruct.msg = getMsg();
    msgStruct.msgID = id++;
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
    SendStruct *msg = new SendStruct;
    getchar();
    while( true ) {
        makeMsgStruct(*msg);

        cout << msg->msg << endl;
        send(sockfd, msg, sizeof(*msg), 0);
        int N = 0;
        if( N < 0 ) { 
            exitWithError("Writing to Socket Problem");
        }

        cout << ">>";

        char buf[1000];
        recv(sockfd, &buf, sizeof(buf), 0);
        msg = (SendStruct *)buf;
//        N = read(sockfd, buffer, 255);
        if( N < 0 ) {
            exitWithError("Reading from Socket Problem");
        }
        cout << "receive : " << msg->msg << endl;
    }

    close(sockfd);
    return 0;
}
