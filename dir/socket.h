//
// Created by lecoan on 4/30/17.
//

#ifndef GUESS_WHAT_SOCKET_H
#define GUESS_WHAT_SOCKET_H

#include <string>
#include <map>
#include "module.h"

const int PORT = 8080;
const int MAX_NUM = 10;

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

    void Repeat();

    string last;
};


class ServerSocket {
private:
    int myId;
public:
    ServerSocket();

    bool Bind(int port);

    void Listen(int max = 10);

    ClientSocket *Accept();

    void Close();
};

class NetHelper {
private:
    static WordService *wordService;
    static UserService *userService;
    static std::map<string, ClientSocket *> sockMap;
    ClientSocket *socket;
    User *loginUser;
public:
    NetHelper(ClientSocket *clientSocket);

    ~NetHelper();

    void exit();

    void getWord(int level);

    void login(string name, string passwd);

    void signUp(string name, string passwd, string type);

    void getUserByName(string name);

    void update(const string &type, const string &username,
                const string &password, unsigned int level,
                unsigned int expr, unsigned int num);

    void getOrder(int kind, string type);

    void getByCondition(int level, int nums, string type);

    void saveWord(string word);

    void contain(string word);

    void getOnlineUser();

    void setChallengable(string name, bool can);

    void repeat();

    void challenge(string name, string senderName);

    void reply(bool agree, string name);
};

#endif //GUESS_WHAT_SOCKET_H
