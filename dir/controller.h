#pragma once
#include"module.h"

class UserController {
	typedef std::string String;
private:
	User * loginUser;
	UserService* service;
	static UserController * instance;
	UserController();
	~UserController();
public:
	struct Condition {
		unsigned level;
		unsigned nums;
		String type;	//player or master
		Condition();
	};

	static UserController* getInstance();
	bool login(String& username, String& password);
	bool logout();
	bool signUp(String& username, String& password, bool isplayer);
	User * findByName(String& name);
	std::set<String> findByCondition(Condition& con);
	bool hasLogin();
};


class GameController {
	typedef std::string String;
private:
	WordService * service;
	static GameController* instance;
public:
	static GameController* getInstance();
    void addWord(String word);
	String getWord(int level = -1);
	int handleInput(String in);
	void addExpr(int amout);
};