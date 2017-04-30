//
// Created by lecoan on 4/30/17.
//

#ifndef GUESS_WHAT_SOCKET_H
#define GUESS_WHAT_SOCKET_H

#include <sys/socket.h>
#include <string>

using std::string;

class Socket {
private:
    struct sockaddr in_adrr;

public:
    bool connect(string ip, int port);

    bool bind(int port);

    void sendBits(char *ptr, int len);

    void sendString(string &s);

    char *readBit();

    string readString();

    bool disconnect();
};

class ServerSocket {
public:
    bool bind(int port);

    bool listen();

    void accept();
};

class ClientSocket {
public:
    bool connect(string ip, int port);

};


#endif //GUESS_WHAT_SOCKET_H
