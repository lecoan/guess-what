#pragma once
#include"module.h"

/*���û�ʵ�������Ŀ�����*/
class UserController {
	typedef std::string String;
private:
	User loginUser;
	UserService* service;
	static UserController* instance;
	UserController();
	~UserController();
public:
	/*����Ӧ��δ�Ĭ��ȫ��ƥ��*/
	struct Condition {
		unsigned level;
		unsigned nums;	//�Ѵ��������ѳ���Ŀ��
		String type;	//player or master
		Condition();
	};

	static UserController* getInstance();
	bool login(String& username, String& password);
	bool logout();									//���û���δ��½����false
	bool signUp(String& username, String& password, bool isplayer);
	User findByName(String& name);
	std::set<String> findByCondition(Condition& con); //����������ϲ�ѯ
	bool hasLogin();
};

/*
 *��Ϸ�����еĿ�����
 */
class GameController {
	typedef std::string String;
private:
	WordService * service;
	static GameController* instance;
public:
	static GameController* getInstance();
	String getWord(int level = -1);
	int handleInput(String in); //�����û������룬\quit�źŲ��ᱻ����
	void addExpr(int amout); //����ֵ������,����UserController
};