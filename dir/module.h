#include<string>
#include<map>
#include<set>
#include<vector>

#ifndef MODULE_H
#define MODULE_H

typedef std::string String;

class User {
protected:
    String username;
    String password;
    unsigned level;
    unsigned expr;
public:
    String getUsername();

    void setUsername(String name);

    String getPassword();

    void setPassword(String pw);

    unsigned getLevel();

    void levelIncrease(int n = 1);

    unsigned getExpr();

    void exprIncrease(int n);

    virtual String getType() = 0;

    friend bool operator==(User &a, User &b);

    friend bool operator<(User &a, User &b);
};

class Player : public User {
private:
    unsigned playedNum;
public:
    Player();

    Player(String username, String passwd, unsigned level,
           unsigned expr, unsigned num);

    String getType() override;

    unsigned getPlayedNum();

    void playedNumIncrease(int n = 1);
};


class Master : public User {
private:
    unsigned outNum;
public:
    Master();

    Master(String username, String passwd, unsigned level,
           unsigned expr, unsigned num);

    String getType() override;

    unsigned getOutNum();

    void outNumIncrease(int n = 1);
};

class UserService {
private:
    UserService();

    ~UserService();

    static UserService *instance;
    const static String PATH;
    std::set<User *> users;
    std::map<String, User *> nameMap;
    std::map<int, std::set<User *>> levellistMap;
    std::map<int, std::set<User *>> numlistMap;
    std::map<int, std::set<User *>> exprlistMap;

    void readUserFromDisk();

public:
    static UserService *getInstance();

    void updateUser(User *user);

    void saveUser(User *user);

    User *getUserByName(String name);

    std::vector<String> getOrder(int kind, String type);

    void writeToDisk();
};

class WordService {
private:
    const static String PATH;
    static WordService *instance;

    WordService();

    ~WordService();

    std::map<unsigned ,std::vector<String>> wordsmap;

    void readWordsFromDisk();

public:
    static WordService *getInstance();

    String getWord(int level = -1);

    void saveWord(String word);

    void writeToDisk();

    bool contain(String word);
};

const int EXPR_FOR_USER = 10;

#endif