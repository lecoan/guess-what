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
    Player("", "", 0, 0, 0);
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
}

unsigned Master::getOutNum() {
    return this->outNum;
}

void Master::outNumIncrease(int n) {
    this->outNum += n;
}

Master::Master() {
    Master("", "", 0, 0, 0);
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

    for (auto it = levellistMap.begin(); it != levellistMap.end(); ++it) {
        if (it->first == user->getLevel())
            it->second.insert(user);
        else if (it->second.find(user) != it->second.end()) {
            it->second.erase(user);
        }
    }

    int num;
    if (user->getType() == "player") {
        num = dynamic_cast<Player *>(user)->getPlayedNum();
    } else {
        num = dynamic_cast<Master *>(user)->getOutNum();
    }
    for (auto it = numlistMap.begin(); it != numlistMap.end(); ++it) {
        if (it->first == num)
            it->second.insert(user);
        else if (it->second.find(user) != it->second.end()) {
            it->second.erase(user);
        }
    }
}


std::set<String> UserService::getOrder(int level, int nums, String type) {
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


const String WordService::PATH = "words.txt";
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
    return words[random() % words.size()];
}

void WordService::saveWord(String word) {
    this->words.push_back(word);
}


void WordService::readWordsFromDisk() {
    ifstream in(PATH, std::ios::in);
    String word;
    while (in >> word)
        words.push_back(word);
    in.close();
}

void WordService::writeToDisk() {
    ofstream out(PATH, std::ios::out);
    for (auto it = words.begin(); it != words.end(); ++it) {
        out << *it << " ";
    }
    out.close();
}

bool WordService::contain(String word) {
    for(int i = 0;i<words.size();++i)
        if(word == words[i])
            return true;
    return false;
}

bool operator==(User &a, User &b) {
    return a.username == b.username;
}

bool operator<(User &a, User &b) {
    return a.username < b.username;
}
