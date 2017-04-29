#include"module.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class UserController {
    typedef std::string String;
private:
    User *loginUser;
    UserService *service;
    static UserController *instance;

    UserController();

    ~UserController();

public:
    struct Condition {
        int level;
        int nums;
        String type;  //player or master
        Condition();
    };

    static UserController *getInstance();

    bool login(String &username, String &password);

    bool logout();

    bool signUp(String &username, String &password, bool isplayer);

    User *findByName(String &name);

    std::set<String> findByCondition(Condition &con);

    bool hasLogin();

    User *getLoginUser();
};


class GameController {
    typedef std::string String;
private:
    WordService *service;
    UserController *userInstance;
    static GameController *gameInstance;

    GameController();

public:
    static GameController *getInstance();

    void addWord(String word);

    String getWord(int level = -1);

    void addExpr(int amout);

    User *getLoginUser();

    bool hasLogin();

    bool isPlayer();

    bool saveWord(String word);
};

#endif