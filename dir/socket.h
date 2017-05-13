//
// Created by lecoan on 4/30/17.
//

#ifndef GUESS_WHAT_SOCKET_H
#define GUESS_WHAT_SOCKET_H

#include <string>

using std::string;

class ClientSocket {
    int myId;
public:
    ClientSocket();

    ClientSocket(int id);

    bool Connect(string ip, int port);

    string Read();

    bool Send(string meg);

    void Close();

};


class ServerSocket {
private:
    int myId;
public:
    ServerSocket();

    bool Bind(int port);

    bool Listen(int max = 10);

    ClientSocket* Accept();

    void Close();
};


class NetHelper {
public:

};

#endif //GUESS_WHAT_SOCKET_H
