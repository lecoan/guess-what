#pragma once
#include<string>
#include<map>
#include<set>
#include<vector>
typedef std::string String;
/*
 *所有用户的基类模型
 */
class User {
protected:
	String username;
	String password;
	unsigned level;
	unsigned expr;
	String type;
public:
	User() = delete;
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
/*
 *玩家的基类模型
 */
class Player : public User {
private:
	unsigned playedNum;
public:
	Player();
	unsigned getPlayedNum();
	void playedNumIncrease(int n = 1);
};

/*
 *出题者的基类模型
 */
class Master :public User {
private:
	unsigned outNum;
public:
	Master();
	unsigned getOutNum();
	void outNumIncrease(int n = 1);
};

/*
 *对用户操作的一次封装
 */
class UserService {
private:
	UserService();
	~UserService();
	static UserService* instance;
	const static String PATH;
	std::set<User> userSet;
	std::map<String,std::set<User>::iterator> cacheMap;

public:
	static UserService* getInstance();
	void updateUser(User& user);
	User getUserByName(String& name);
	void addExpr(String name);
	std::set<String> getOrder(unsigned level, unsigned nums, String type);
};

/*
 *对题库的一次封装
 */
class WordService {
private:
	const static String PATH;
	static WordService* instance;
	WordService();
	~WordService();
	std::set<String> wordSet;
public:
	static WordService* getInstance();
	String getWord(int level = -1);		//根据传入的题目难度获取单词，默认为随机
	void saveWord(String word);
};