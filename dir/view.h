#include "controller.h"

#ifndef VIEW_H
#define VIEW_H

class MainView {

};

class LoginView {
private:
    static UserController *controller;
public:
    static void showLogin();
};

class RegisterView {
private:
    static UserController *controller;
public:
    static void showRegister();
};

class OrderView {
private:
    static UserController *controller;
public:
    static void showOrder();
};

class GameView {
private:
    static GameController *controller;
public:
    static void showGame();

    static void showQuestion();

    static void getQuestion();
};

#endif