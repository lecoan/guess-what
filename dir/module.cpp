#include "module.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::ofstream;

String User::getUsername() {
    return this->username;
}

void User::setUsername(String name) {
    this->username = name;
}

String User::getPassword() {
    return this->password;
}

void User::setPassword(String pw) {
    this->password = pw;
}

unsigned User::getLevel() {
    return this->level;
}

void User::levelIncrease(int n) {
    this->level += n;
}

unsigned User::getExpr() {
    return this->expr;
}

void User::exprIncrease(int n) {
    int LEVLE_NEED_EXPR = level * EXPR_FOR_USER;
    int t = this->expr + n;
    this->expr = expr % LEVLE_NEED_EXPR;
    this->level += t / LEVLE_NEED_EXPR;
}


unsigned Player::getPlayedNum() {
    return this->playedNum;
}

void Player::playedNumIncrease(int n) {
    this->playedNum++;
}

Player::Player() {
    Player("", "", 1, 0, 0);
    canChallenge = false;
}

String Player::getType() {
    return "player";
}

Player::Player(String username, String passwd, unsigned level,
               unsigned expr, unsigned num) {
    this->username = username;
    this->password = passwd;
    this->level = level;
    this->expr = expr;
    this->playedNum = num;
    canChallenge = false;
}

bool Player::ifcanChallenge() {
    return canChallenge;
}

void Player::setCanChallenge(bool can) {
    canChallenge = can;
}

unsigned Master::getOutNum() {
    return this->outNum;
}

void Master::outNumIncrease(int n) {
    this->outNum += n;
}

Master::Master() {
    Master("", "", 1, 0, 0);
}

String Master::getType() {
    return "master";
}

Master::Master(String username, String passwd, unsigned int level,
               unsigned int expr, unsigned int num) {
    this->username = username;
    this->password = passwd;
    this->level = level;
    this->expr = expr;
    this->outNum = num;
}

const String UserService::PATH = "users.txt";
UserService *UserService::instance = nullptr;

UserService::UserService() {
    readUserFromDisk();
}

UserService::~UserService() {
    for (auto it = users.begin(); it != users.end(); ++it)
        delete (*it);
    delete instance;
}

UserService *UserService::getInstance() {
    if (instance == nullptr) {
        instance = new UserService();
    }
    return instance;
}

void UserService::updateUser(User *user) {

    levellistMap[user->getLevel()].insert(user);
    for (auto it = levellistMap.begin(); it != levellistMap.end(); ++it) {
        if (it->second.find(user) != it->second.end()) {
            it->second.erase(user);
        }
    }
    exprlistMap[user->getExpr()].insert(user);
    for (auto it = exprlistMap.begin(); it != exprlistMap.end(); ++it) {
        if (it->second.find(user) != it->second.end()) {
            it->second.erase(user);
        }
    }
    int num;
    if (user->getType() == "player") {
        num = dynamic_cast<Player *>(user)->getPlayedNum();
    } else {
        num = dynamic_cast<Master *>(user)->getOutNum();
    }
    numlistMap[num].insert(user);
    for (auto it = numlistMap.begin(); it != numlistMap.end(); ++it) {
        if (it->second.find(user) != it->second.end()) {
            it->second.erase(user);
        }
    }
}


std::vector<String> UserService::getOrder(int kind, String type) {
    std::vector<String> ans;
    switch (kind) {
        case 1:
            for (auto it = levellistMap.rbegin(); it != levellistMap.rend(); ++it)
                for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
                    if ((*jt)->getType() == type)
                        ans.push_back((*jt)->getUsername()
                                      + " level:" + std::to_string((*jt)->getLevel()));
            break;
        case 2:
            for (auto it = numlistMap.rbegin(); it != numlistMap.rend(); ++it)
                for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
                    if ((*jt)->getType() == type) {
                        if (type == "player")
                            ans.push_back((*jt)->getUsername()
                                          + " nums:" + std::to_string(dynamic_cast<Player *>(*jt)->getPlayedNum()));
                        else {
                            ans.push_back((*jt)->getUsername()
                                          + " nums:" + std::to_string(dynamic_cast<Master *>(*jt)->getOutNum()));
                        }
                    }

            break;
        case 3:
            for (auto it = exprlistMap.rbegin(); it != exprlistMap.rend(); ++it)
                for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
                    ans.push_back((*jt)->getUsername()
                                  + " expr:" + std::to_string((*jt)->getExpr()));
            break;
        default:
            break;
    }
    return ans;
}


void UserService::readUserFromDisk() {
    ifstream in(PATH, std::ios::in);
    String line;
    User *user;
    String type, name, passwd;
    unsigned level, expr, num;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        ss >> type >> name >> passwd >> level >> expr >> num;
        if (type == "player") {
            user = new Player(name, passwd, level, expr, num);
        } else {
            user = new Master(name, passwd, level, expr, num);
        }
        numlistMap[user->getLevel()].insert(user);
        levellistMap[num].insert(user);
        exprlistMap[expr].insert(user);
        nameMap[user->getUsername()] = user;
        users.insert(user);
    }
    in.close();
}

void UserService::saveUser(User *user) {
    users.insert(user);
    nameMap[user->getUsername()] = user;
    //after push, the num will be +
    levellistMap[user->getLevel()].insert(user);
    exprlistMap[user->getExpr()].insert(user);
    int num;
    if (user->getType() == "player") {
        num = dynamic_cast<Player *>(user)->getPlayedNum();
    } else {
        num = dynamic_cast<Master *>(user)->getOutNum();
    }
    numlistMap[num].insert(user);
}

User *UserService::getUserByName(String name) {
    if (nameMap.find(name) != nameMap.end())
        return nameMap[name];
    return nullptr;
}

void UserService::writeToDisk() {
    ofstream out(PATH, std::ios::out);
    for (auto it = users.begin(); it != users.end(); ++it) {
        User *user = (*it);
        out << user->getType() << " "
            << user->getUsername() << " "
            << user->getPassword() << " "
            << user->getLevel() << " "
            << user->getExpr() << " ";
        if (user->getType() == "player")
            out << dynamic_cast<Player *>(user)->getPlayedNum();
        else
            out << dynamic_cast<Master *>(user)->getOutNum();
        out << std::endl;
    }
    out.close();
}

std::set<String> UserService::getUserNameByCondition(int level, int nums, String type) {
    std::set<String> ans;
    bool needlevel = level != -1;
    bool neednums = nums != -1;
    bool needType = type != "";
    for (auto it = users.begin(); it != users.end(); ++it) {
        User *user = *it;
        if (!needlevel || (level == user->getLevel())) {
            if (!needType || type == user->getType()) {
                if (!neednums) {
                    ans.insert(user->getUsername());
                } else {
                    if (user->getType() == "player") {
                        if (dynamic_cast<Player *>(user)->getPlayedNum() == nums)
                            ans.insert(user->getUsername());
                    } else {
                        if (dynamic_cast<Master *>(user)->getOutNum() == nums)
                            ans.insert(user->getUsername());
                    }
                }
                if (ans.size() > 50)
                    break;
            }
        }
    }
    return ans;
}

void UserService::removeUser(User *user) {
    for (auto it = levellistMap.begin(); it != levellistMap.end(); ++it) {
        if (it->second.find(user) != it->second.end()) {
            it->second.erase(user);
        }
    }
    for (auto it = exprlistMap.begin(); it != exprlistMap.end(); ++it) {
        if (it->second.find(user) != it->second.end()) {
            it->second.erase(user);
        }
    }
    for (auto it = numlistMap.begin(); it != numlistMap.end(); ++it) {
        if (it->second.find(user) != it->second.end()) {
            it->second.erase(user);
        }
    }
    delete user;
}

std::set<std::string> UserService::getOnlineUsers() {
    std::set<std::string> data;
    for (auto it = onlineUsers.begin(); it != onlineUsers.end(); ++it) {
        if ((*it)->getType() == "player")
            data.insert((*it)->getUsername());
    }
}

void UserService::addOnlineUser(User *user) {
    onlineUsers.insert(user);
}

void UserService::removeOnlineUser(User *pUser) {
    onlineUsers.erase(pUser);
}


const String WordService::PATH = "wordsmap.txt";
WordService *WordService::instance = nullptr;

WordService::WordService() {
    readWordsFromDisk();
}

WordService::~WordService() {
    delete instance;
}

WordService *WordService::getInstance() {
    if (instance == nullptr) {
        instance = new WordService();
    }
    return instance;
}

String WordService::getWord(int level) {
    srand(0);
    int ran = rand() % 5 + 1;
    return wordsmap[level + ran][rand() % wordsmap[level + ran].size()];

}

void WordService::saveWord(String word) {
    this->wordsmap[word.size()].push_back(word);
}


void WordService::readWordsFromDisk() {
    ifstream in(PATH, std::ios::in);
    String word;
    while (in >> word)
        wordsmap[word.size()].push_back(word);
    in.close();
}

void WordService::writeToDisk() {
    ofstream out(PATH, std::ios::out);
    for (auto it = wordsmap.begin(); it != wordsmap.end(); ++it) {
        for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
            out << *jt << " ";
    }
    out.close();
}

bool WordService::contain(String word) {
    if (wordsmap.find(word.size()) == wordsmap.end())
        return false;
    for (auto it = wordsmap[word.size()].begin(); it != wordsmap[word.size()].end(); ++it)
        if (*it == word)
            return true;
    return false;
}

bool operator==(User &a, User &b) {
    return a.username == b.username;
}

bool operator<(User &a, User &b) {
    return a.username < b.username;
}
