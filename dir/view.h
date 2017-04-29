#include "controller.h"

#ifndef VIEW_H
#define VIEW_H

class MainView {
private:
    static UserController *controller;
public:
    static void showMain();
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

    static void showSearch();
};

class GameView {
private:
    static GameController *controller;

    static void showQuestion();

    static void getQuestion();

public:
    static void showGame();
};

#endif