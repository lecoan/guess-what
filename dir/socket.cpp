//
// Created by lecoan on 4/30/17.
//

#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "socket.h"
#include <iostream>
using std::cerr;
using std::endl;

ClientSocket::ClientSocket() {
    myId = socket(AF_INET,SOCK_STREAM,NULL);
}

bool ClientSocket::Connect(string ip, int port) {
    hostent *server = gethostbyname(ip.c_str());
    if(server == NULL){
        cerr<<"wrong address"<<endl;
        return false;
    }
    sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&addr.sin_addr.s_addr,
          server->h_length);

    return connect(myId,(sockaddr*)&addr,sizeof(addr))>0;
}

string ClientSocket::Read() {
    char buffer[1024];
    read(myId,buffer,sizeof(buffer));
    string data = buffer;
    return data;
}

bool ClientSocket::Send(string meg) {
    if(myId <0)
        return -1;
    string data = meg+"\n";
    last = data;
    return send(myId,data.c_str(),data.size(),NULL)>0;
}

void ClientSocket::Close() {
    if(myId>0){
        close(myId);
    }
}

ClientSocket::ClientSocket(int id) {
    myId = id;
}

void ClientSocket::Repeat() {
    Send(last);
}


ServerSocket::ServerSocket() {
    myId = socket(AF_INET, SOCK_STREAM, 0);
}

bool ServerSocket::Bind(int port) {
    if (myId == -1)
        return false;
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(8080);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    return bind(myId, (sockaddr *) &addr, sizeof(addr)) > 0;
}

bool ServerSocket::Listen(int max) {
    return listen(myId, max) == -1;
}

ClientSocket* ServerSocket::Accept() {
    sockaddr_in clientaddr;
    socklen_t n = sizeof(clientaddr);
    int client = accept(myId, (sockaddr *) &clientaddr, &n);
    if(client > 0){
        return new ClientSocket(client);
    }
    cerr<<"connect error"<<endl;
    return nullptr;
}

void ServerSocket::Close() {
    if (myId != -1)
        close(myId);
}

