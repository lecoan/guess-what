#pragma once
#include "controller.h"

/*基本视图*/
class View {
protected:
	bool dispose(String info); //根据信息关闭当前窗口
};

/*登陆视图*/
class LoginView : public View {
private:
	UserController* controller;
public:
	void showLogin();
};

/*注册视图*/
class RegisterView :public View {
private:
	UserController* controller;
public:
	void showRegister();
};

/*查询视图*/
class OrderView :public View {
private:
	UserController* controller;
public:
	void showOrder();
};

/*游戏视图*/
class GameView :public View {
private:
	GameController* controller;
public:
	void showGame();
};