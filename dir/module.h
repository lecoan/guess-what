#pragma once
#include<string>
#include<map>
#include<set>
#include <list>
#include<vector>
typedef std::string String;

class User {
protected:
	String username;
	String password;
	unsigned level;
	unsigned expr;
	String type;
public:
	virtual User() = 0;
	String getUsername();
	void setUsername(String name);
	String getPassword();
	void setPassword(String pw);
	unsigned getLevel();
	void levelIncrease(int n = 1);
	unsigned getExpr();
	void exprIncrease(int n);
	String getType();
	friend bool operator == (User& a, User& b);
	friend bool operator < (User& a, User&b);
};

class Player : public User {
private:
	unsigned playedNum;
public:
	Player();
	unsigned getPlayedNum();
	void playedNumIncrease(int n = 1);
};


class Master :public User {
private:
	unsigned outNum;
public:
	Master();
	unsigned getOutNum();
	void outNumIncrease(int n = 1);
};

class UserService {
private:
	UserService();
	~UserService();
	static UserService* instance;
	const static String PATH;
	std::set<User *> users;
	std::map<String,User *> nameMap;
	std::map<int,std::set<User *>> levellistMap;
	std::map<int,std::set<User *>> numlistMap;

	void readUserFromDisk();

public:
	static UserService* getInstance();
	void updateUser(User * user);
	void saveUser(User * user);
	User* getUserByName(String& name);
	void addExpr(User * user, int num);
	std::set<String> getOrder(unsigned level, unsigned nums, String type);
};

class WordService {
private:
	const static String PATH;
	static WordService* instance;
	WordService();
	~WordService();
	std::vector<String> wordSet;

	void readWordsFromDisk();
public:
	static WordService* getInstance();
	String getWord(int level = -1);
	void saveWord(String word);
};