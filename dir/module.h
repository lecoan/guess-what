#pragma once
#include<string>
#include<map>
#include<set>
#include<vector>
typedef std::string String;
/*
 *�����û��Ļ���ģ��
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
 *��ҵĻ���ģ��
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
 *�����ߵĻ���ģ��
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
 *���û�������һ�η�װ
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
 *������һ�η�װ
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
	String getWord(int level = -1);		//���ݴ������Ŀ�ѶȻ�ȡ���ʣ�Ĭ��Ϊ���
	void saveWord(String word);
};