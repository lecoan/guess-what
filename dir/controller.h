#pragma once
#include"module.h"

/*对用户实例操作的控制器*/
class UserController {
	typedef std::string String;
private:
	User loginUser;
	UserService* service;
	static UserController* instance;
	UserController();
	~UserController();
public:
	/*若对应项未填，默认全部匹配*/
	struct Condition {
		unsigned level;
		unsigned nums;	//已闯关数或已出题目数
		String type;	//player or master
		Condition();
	};

	static UserController* getInstance();
	bool login(String& username, String& password);
	bool logout();									//若用户尚未登陆返回false
	bool signUp(String& username, String& password, bool isplayer);
	User findByName(String& name);
	std::set<String> findByCondition(Condition& con); //根据条件组合查询
	bool hasLogin();
};

/*
 *游戏过程中的控制器
 */
class GameController {
	typedef std::string String;
private:
	WordService * service;
	static GameController* instance;
public:
	static GameController* getInstance();
	String getWord(int level = -1);
	int handleInput(String in); //返回用户的输入，\quit信号不会被传入
	void addExpr(int amout); //经验值增加量,调用UserController
};