//
// Created by lecoan on 4/30/17.
//

#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Socket.h"

ServerSocket::ServerSocket() {
    myId = socket(AF_INET,SOCK_STREAM,0);
}

bool ServerSocket::bind(int port) {
    if(myId == -1)
        return false;
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(8080);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    return bind(myId,(sockaddr*)&addr,sizeof(addr))>0;
}

bool ServerSocket::Listen(int max) {
    return listen(myId,max) == -1;
}

void ServerSocket::Accept() {
    accept(myId,(sockaddr*)NULL,NULL);
}

void ServerSocket::Close() {
    if(myId != -1)
        close(myId);
}