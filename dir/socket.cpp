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
using std::cout;
using std::endl;

ClientSocket::ClientSocket() {
    myId = socket(AF_INET, SOCK_STREAM, 0);
}

bool ClientSocket::Connect(string ip, int port) {
    hostent *server = gethostbyname(ip.c_str());
    if (server == NULL) {
        cerr << "wrong address" << endl;
        return false;
    }
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
          (char *) &addr.sin_addr.s_addr,
          server->h_length);
    return connect(myId, (sockaddr *) &addr, sizeof(addr)) > 0;
}

string ClientSocket::Read() {
    char buffer[1024];
    read(myId, buffer, sizeof(buffer));
    string data = buffer;
    data = data.substr(0,data.find('\n')+1);
    data.pop_back();
    cout << "from id:" << myId << " read data-->" << data << endl;
    return data;
}

bool ClientSocket::Send(string meg) {
    if (myId < 0)
        return -1;
    string data = meg + "\n";
    last = data;
    cout << "from id:" << myId << " send data-->" << data;
    return send(myId, data.c_str(), data.size(), 0) > 0;
}

void ClientSocket::Close() {
    if (myId > 0) {
        close(myId);
        cout << "close socket " << myId << endl;
    }
}

ClientSocket::ClientSocket(int id) {
    myId = id;
    cout << "create client socket " << id << endl;
}

void ClientSocket::Repeat() {
    cout << "repeat message" << endl;
    Send(last);
}


ServerSocket::ServerSocket() {
    myId = socket(AF_INET, SOCK_STREAM, 0);
    cout << "create server socket " << myId << endl;
}

bool ServerSocket::Bind(int port) {
    if (myId == -1)
        return false;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    bool isok = bind(myId, (struct sockaddr *) &addr, sizeof(addr)) >= 0;
    cout << "server bind port:" << port << " is " << isok << endl;
    return isok;
}

void ServerSocket::Listen(int max) {
    listen(myId, max);
    cout << "server listen num is " << max << endl;
}

ClientSocket *ServerSocket::Accept() {
    sockaddr_in clientaddr;
    socklen_t n = sizeof(clientaddr);
    int client = accept(myId, (sockaddr *) &clientaddr, &n);
    if (client > 0) {
        return new ClientSocket(client);
    }
    cerr << "connect error" << endl;
    return nullptr;
}

void ServerSocket::Close() {
    if (myId != -1)
        close(myId);
}

using std::to_string;

WordService *NetHelper::wordService = nullptr;
UserService *NetHelper::userService = nullptr;
std::map<string, ClientSocket *> NetHelper::sockMap;
std::map<string, NetHelper::gameData> NetHelper::gameDataMap;

NetHelper::~NetHelper() {

}

NetHelper::NetHelper(ClientSocket *clientSocket) {
    socket = clientSocket;
    wordService = WordService::getInstance();
    userService = UserService::getInstance();
    loginUser = nullptr;
}

void NetHelper::exit() {
    socket->Close();
    if(loginUser != nullptr){
        sockMap.erase(loginUser->getUsername());
        userService->removeOnlineUser(loginUser);
        loginUser = nullptr;
    }
}

void NetHelper::getWord(int level) {
    string word = wordService->getWord(level);
    socket->Send(word);
}

void NetHelper::login(string name, string passwd) {
    User *user = userService->getUserByName(name);
    if (user != nullptr && user->getPassword() == passwd) {
        loginUser = user;
        int num;
        if (user->getType() == "player") {
            num = dynamic_cast<Player *>(user)->getPlayedNum();
        } else {
            num = dynamic_cast<Master *>(user)->getOutNum();
        }
        string data = "OK " + user->getType() + " " + name + " " + passwd + " " +
                      to_string(user->getLevel()) + " "
                      + to_string(user->getExpr()) + " "
                      + to_string(num);
        socket->Send(data);
        userService->addOnlineUser(user);
        sockMap[name] = socket;

    } else
        socket->Send("ERROR");
}

void NetHelper::signUp(string name, string passwd, string type) {
    User *user = userService->getUserByName(name);
    if (user == nullptr) {
        if (type == "player") {
            user = new Player(name, passwd, 0, 0, 0);
        } else {
            user = new Master(name, passwd, 0, 0, 0);
        }
        userService->saveUser(user);
        socket->Send("OK");
    } else {
        socket->Send("ERROR");
    }
}

void NetHelper::getUserByName(string name) {
    User *user = userService->getUserByName(name);
    if (user == nullptr) {
        socket->Send("ERROR");
    } else {
        int num;
        if (user->getType() == "player") {
            num = dynamic_cast<Player *>(user)->getPlayedNum();
        } else {
            num = dynamic_cast<Master *>(user)->getOutNum();
        }
        string data = "OK " + user->getType()
                      + " " + user->getUsername()
                      + " " + user->getPassword()
                      + " " + to_string(user->getLevel())
                      + " " + to_string(user->getExpr())
                      + " " + to_string(num);
        socket->Send(data);
    }
}

void NetHelper::update(const string &type, const string &username, const string &password, unsigned int level,
                       unsigned int expr, unsigned int num) {
    User *user = userService->getUserByName(username);
    userService->removeUser(user);
    if (type == "player") {
        user = new Player(username, password, level, expr, num);
    } else {
        user = new Master(username, password, level, expr, num);
    }
    userService->saveUser(user);
}

void NetHelper::getOrder(int kind, string type) {
    std::vector<string> buffer = userService->getOrder(kind, type);
    string data;
    for (int i = 0; i < buffer.size(); ++i) {
        data.append(buffer[i] + " ");
    }
    socket->Send(data);

}

void NetHelper::getByCondition(int level, int nums, string type) {
    std::set<string> buffer =
            userService->getUserNameByCondition(level, nums, type);
    string data;
    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
        data.append(*it + " ");
    }
    socket->Send(data);
}

void NetHelper::saveWord(string word) {
    wordService->saveWord(word);
}

void NetHelper::contain(string word) {
    bool contain = wordService->contain(word);
    if (contain)
        socket->Send("YES");
    else
        socket->Send("NO");
}

/**
 * get online players
 */
void NetHelper::getOnlineUser() {
    std::set<string> buffer = userService->getOnlineUsers();
    string data;
    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
        data.append(*it + " ");
    }
    socket->Send(data);

}

void NetHelper::setChallengable(string name, bool can) {
    Player *player = (Player *) userService->getUserByName(name);
    player->setCanChallenge(can);
}

void NetHelper::repeat() {
    socket->Repeat();
}

void NetHelper::challenge(string name, string senderName) {
    Player *bechall = (Player *) userService->getUserByName(name);
    Player *chall = (Player *) userService->getUserByName(senderName);
    chall->setCanChallenge(false);
    if (bechall->ifcanChallenge()) { //可以被挑战
        bechall->setCanChallenge(false);
        ClientSocket *besock = sockMap[name];
        besock->Send("receiveChallenge " + senderName);
        //besock->Read();
    } else { //不能被挑战
        socket->Send("ERROR");
        chall->setCanChallenge(true);
    }

}

void NetHelper::reply(bool agree, string name) {
    if (agree) {
        sockMap[name]->Send("OK");
    }
}

void NetHelper::finishWord(bool isRight, long period, string oppoName) {
    if(gameDataMap.find(oppoName)!=gameDataMap.end()){
        gameData data = gameDataMap[oppoName];
        if(data.isRight&&data.period<period){
            socket->Send("LOSE");
            sockMap[oppoName]->Send("WIN");
            gameDataMap.erase(oppoName);
        } else {
            socket->Send("WIN");
            sockMap[oppoName]->Send("LOSE");
        }
        Player* player1 = (Player *) userService->getUserByName(oppoName);
        Player* player2 = (Player *) loginUser;
        player1->setCanChallenge(true);
        player2->setCanChallenge(true);
    } else{
        gameData data;
        data.period = period;
        data.isRight = isRight;
        gameDataMap[loginUser->getUsername()] = data;
    }
}