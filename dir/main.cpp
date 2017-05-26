#include "socket.h"
#include <sstream>

static void *distribution(void *arg);

int main() {
    ServerSocket socket;
    socket.Bind(PORT);
    socket.Listen(MAX_NUM);
    //程序不断接受来自客户端的连接
    while (true) {
        //在ServerSocket收到新的客户端的连接请求后
        //创建一个ClientSocket对象并传入新开的线程来
        //和特定客户端进行通信
        ClientSocket *clientSocket = socket.Accept();
        pthread_t id;
        pthread_create(&id, NULL, distribution, clientSocket);
    }
}

/**
 * 对客户端发来的消息进行分发处理
 * @param cientSocket
 * @return nothing
 */
static void *distribution(void *arg) {
    pthread_detach(pthread_self());
    ClientSocket *socket = (ClientSocket *) arg;
    NetHelper netHelper(socket);
    while (true) {
        string msg = socket->Read();
        std::stringstream ss(msg);
        string command;
        ss >> command;
        if (command == "exit") {
            netHelper.exit();
            break;
        } else if (command == "getWord") { // command + level
            int level;
            ss >> level;
            netHelper.getWord(level);
        } else if (command == "login") { //command + name + passwd
            string name, passwd;
            ss >> name >> passwd;
            netHelper.login(name, passwd);
        } else if (command == "register") { // command + username + password + type
            string name, passwd, type;
            ss >> name >> passwd >> type;
            netHelper.signUp(name, passwd, type);
        } else if (command == "getUserByName") { // command + name
            string name;
            ss >> name;
            netHelper.getUserByName(name);
        } else if (command == "update") { // command + allInfo
            string type, username, password;
            unsigned int level, expr, num;
            ss >> type >> username >> password >> level >> expr >> num;
            netHelper.update(type, username, password, level, expr, num);
        } else if (command == "getOrder") { // command + kind + type
            int kind;
            string type;
            ss >> kind >> type;
            netHelper.getOrder(kind, type);
        } else if (command == "getByCondition") { // command + level + num + type
            string type;
            int level, nums;
            ss >> level >> nums >> type;
            netHelper.getByCondition(level, nums, type);
        } else if (command == "saveWord") { // command + word
            string word;
            ss >> word;
            netHelper.saveWord(word);

        } else if (command == "contain") { // command + word
            string word;
            ss >> word;
            netHelper.contain(word);

        } else if (command == "challenge") { // command + name + senderName
            string name, senderName;
            ss >> name >> senderName;
            netHelper.challenge(name, senderName);
        } else if (command == "getOnlineUser") { // command
            netHelper.getOnlineUser();
        } else if (command == "setChallengable") { // command + name + can
            bool can;
            string name;
            ss >> name >> can;
            netHelper.setChallengable(name, can);
        } else if (command == "finishWord") { // command + isRight + period + oppoName
            bool isRight;
            long period;
            string oppoName;
            ss >> isRight >> period>>oppoName;
            netHelper.finishWord(isRight,period,oppoName);
        } else if (command == "reply") { // command + agree + name
            bool agree;
            string name;
            ss >> agree >> name;
            netHelper.reply(agree, name);
        } else if (command == "repeat") { // command
            netHelper.repeat();
        }
    }
}
