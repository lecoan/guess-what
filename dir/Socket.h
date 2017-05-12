//
// Created by lecoan on 4/30/17.
//

#ifndef GUESS_WHAT_SOCKET_H
#define GUESS_WHAT_SOCKET_H

#include <string>

using std::string;

class ServerSocket {
private:
    int myId;
public:
    ServerSocket();

    bool Bind(int port);

    bool Listen(int max = 10);

    bool Accept();

    bool Send(string msg);

    string Read();

    void Close();
};



class NetHelper {
public:

};

#endif //GUESS_WHAT_SOCKET_H
