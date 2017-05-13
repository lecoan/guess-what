#include "socket.h"
#include "module.h"
#include <sstream>

static WordService *wordService = WordService::getInstance();
static UserService *userService = UserService::getInstance();

static std::map<string, ClientSocket*> sockMap;

using std::to_string;

static void *distribution(void *arg) {
    pthread_detach(pthread_self());
    ClientSocket *socket = (ClientSocket *) arg;
    while (true) {
        string msg = socket->Read();
        std::stringstream stream;
        string command;
        stream >> command;
        if (command == "exit") {
            socket->Close();
            break;
        } else if (command == "getWord") { // command + level
            int level;
            stream >> level;
            string word = wordService->getWord(level);
            socket->Send(word);
        } else if (command == "login") { //command + name + passwd
            string name, passwd;
            stream >> name >> passwd;
            User *user = userService->getUserByName(name);
            if (user != nullptr && user->getPassword() == passwd) {
                int num;
                if (user->getType() == "player") {
                    num = dynamic_cast<Player *>(user)->getPlayedNum();
                } else {
                    num = dynamic_cast<Master *>(user)->getOutNum();
                }
                string data = "OK " + user->getType() + " "name + " " + passwd + " " +
                              to_string(user->getLevel()) + " "
                              + to_string(user->getExpr()) + " "
                              + to_string(num);
                socket->Send(data);
                userService->addOnlineUser(user);
                sockMap[name] = socket;
            }
            socket->Send("ERROR");
        } else if (command == "register") { // command + username + password + type
            string name, passwd, type;
            stream >> name >> passwd >> type;
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
        } else if (command == "getUserByName") { // command + name
            string name;
            stream >> name;
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
        } else if (command == "update") { // command + allInfo
            string type, username, password;
            unsigned int level, expr, num;
            stream >> type >> username >> password >> level >> expr >> num;
            User *user = userService->getUserByName(username);
            userService->removeUser(user);
            if (type == "player") {
                user = new Player(username, password, level, expr, num);
            } else {
                user = new Master(username, password, level, expr, num);
            }
            userService->saveUser(user);

        } else if (command == "getOrder") { // command + kind + type
            int kind;
            string type;
            stream >> kind >> type;
            std::vector<string> buffer = userService->getOrder(kind, type);
            string data;
            for (int i = 0; i < buffer.size(); ++i) {
                data.append(buffer[i] + " ");
            }
            socket->Send(data);
        } else if (command == "getByCondition") { // command + level + num + type
            string type;
            int level, nums;
            stream >> level >> nums >> type;
            std::set<string> buffer =
                    userService->getUserNameByCondition(level, nums, type);
            string data;
            for (auto it = buffer.begin(); it != buffer.end(); ++it) {
                data.append(*it + " ");
            }
            socket->Send(data);
        } else if (command == "saveWord") { // command + word
            string word;
            stream >> word;
            wordService->saveWord(word);

        } else if (command == "contain") { // command + word
            string word;
            stream >> word;
            bool contain = wordService->contain(word);
            if (contain)
                socket->Send("YES");
            else
                socket->Send("NO");

        } else if (command == "challenge") { // command + name + senderName

        } else if (command == "getOnlineUser") { // command
            std::set<string> buffer = userService->getOnlineUsers();
            string data;
            for (auto it = buffer.begin(); it != buffer.end(); ++it) {
                data.append(*it + " ");
            }
            socket->Send(data);
        } else if (command == "setChallengable") { // command + name + can
            bool can;
            string name;
            stream >> name >> can;
            Player *player = (Player *) userService->getUserByName(name);
            player->setCanChallenge(can);
        } else if (command == "finishWord") { // command + isRight + period
            bool isRight;
            long period;
            stream>>isRight>>period;
            //TODO
        } else if (command == "reply") { // command + agree

        } else if (command == "repeat") { // command
            socket->Repeat();
        }
    }
}

int main() {
    ServerSocket socket;
    socket.Bind(8080);
    socket.Listen(10);

    while (true) {
        ClientSocket *clientSocket = socket.Accept();
        pthread_t id;
        pthread_create(&id, NULL, distribution, clientSocket);
    }
}