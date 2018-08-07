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
    string msg;
    int msgID;
} SendStruct;

void exitWithError(const char* errMsg) {
    printf("%s\n", errMsg);
    exit(-1);
}

string getMsg() {
    cout << "Enter Msg :";
    string str;
    getline(cin, str);
    return str;
}

void makeMsgStruct(SendStruct &msgStruct) {
    static int id = 0;
    msgStruct.msgID = id++;
    msgStruct.msg = getMsg();
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

    SendStruct *msg = new SendStruct;
    while( true ) {
        char buf[1000];
        recv(sockfd, &buf, sizeof(buf), 0);
        msg = (SendStruct* )buf;
            //exitWithError("Reading from Socket Problem");
        cout << "Client >> " << msg->msg << endl;

        makeMsgStruct(*msg);
        cout << "send msg - " << msg->msg << endl;
        sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
    }
    close(new_sockfd);
    close(sockfd);
    return 0;
}