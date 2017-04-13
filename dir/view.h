#pragma once
#include "controller.h"

/*������ͼ*/
class View {
protected:
	bool dispose(String info); //������Ϣ�رյ�ǰ����
};

/*��½��ͼ*/
class LoginView : public View {
private:
	UserController* controller;
public:
	void showLogin();
};

/*ע����ͼ*/
class RegisterView :public View {
private:
	UserController* controller;
public:
	void showRegister();
};

/*��ѯ��ͼ*/
class OrderView :public View {
private:
	UserController* controller;
public:
	void showOrder();
};

/*��Ϸ��ͼ*/
class GameView :public View {
private:
	GameController* controller;
public:
	void showGame();
};