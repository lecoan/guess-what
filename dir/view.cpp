#include <iostream>
#include <regex>
#include <unistd.h>
#include "view.h"

using std::cout;
using std::cin;
using std::endl;
using std::regex_match;
using std::regex;
using std::getline;

static regex matchText("^[a-zA-Z][a-zA-Z0-9_]{4,15}$");
static regex matchWord("^([a-z]+){1,10}$");

UserController *LoginView::controller = nullptr;

void LoginView::showLogin() {
    if (controller == nullptr) {
        controller = UserController::getInstance();
    }
    while (true) {
        String username, passwd;
        cout << "your username:" << endl;
        cin >> username;
        if (username == "\\quit") {
            break;
        }
        while (!regex_match(username, matchText)) {
            cout << "invalid username, please retry:" << endl;
            cin >> username;
        }
        cout << "your password" << endl;
        cin >> passwd;
        while (!regex_match(passwd, matchText)) {
            cout << "invalid password, please retry:" << endl;
            cin >> passwd;
        }
        if (controller->login(username, passwd)) {
            cout << "welcome back! " + username << endl;
            break;
        } else {
            cout << "Error:username and password not match" << endl;
        }
    }
}

UserController *RegisterView::controller = nullptr;

void RegisterView::showRegister() {

    if (controller == nullptr) {
        controller = UserController::getInstance();
    }
    while (true) {
        int type;
        String username, passwd;
        cout << "which kind of user you want to be?" << endl
             << "1. Player" << endl
             << "2. Master" << endl
             << "3. I want quit" << endl;
        cin >> type;
        if (type == 3)
            break;
        cout << "your username:" << endl;
        while (cin >> username) {
            if (!regex_match(username, matchText)) {
                cout << "invalid username, please retry:" << endl;
            } else if (controller->findByName(username) != nullptr) {
                cout << "sorry, this name has been registered" << endl
                     << "please input a new username" << endl;
            } else {
                break;
            }
        }
        cout << "your password:" << endl;
        while (cin >> passwd) {
            if (regex_match(passwd, matchText))
                break;
        }
        if (controller->signUp(username, passwd, type == 1)) {
            cout << "welcome you join us! " + username << endl;
            break;
        } else {
            cout << "Error:something happened" << endl;
        }
    }
}

UserController *OrderView::controller = nullptr;

void OrderView::showOrder() {

    if (controller == nullptr)
        controller = UserController::getInstance();

    UserController::Condition condition;
    String temp;
    cout << "this is an search view, you can enter which attribute you want to search" << endl
         << "if you don't want to limit, just type ENTER" << endl
         << "type \"\\quit\" to exit" << endl;
    getchar();
    while (true) {
        cout << "which level you want to find?" << endl;
        getline(cin, temp);
        if (temp == "\\quit")
            break;
        if (temp != "") condition.level = std::atoi(temp.c_str());
        cout << "how many nums the user get you want to find?" << endl;
        getline(cin, temp);
        if (temp == "\\quit")
            break;
        if (temp != "") condition.nums = std::atoi(temp.c_str());
        cout << "which user type you want to find?" << endl;
        getline(cin, temp);
        if (temp == "\\quit")
            break;
        condition.type = temp;
        std::set<String> set = controller->findByCondition(condition);
        cout << "here comes the result" << endl;
        for (auto it = set.begin(); it != set.end(); ++it)
            cout << "username: " << *it << endl;
        cout << "total:" << set.size() << endl << endl;
    }
}

GameController *GameView::controller = nullptr;

void GameView::showGame() {
    if (controller == nullptr)
        controller = GameController::getInstance();
    if (!controller->hasLogin()) {
        cout << "please login at first!" << endl;
        return;
    } else if (controller->isPlayer()) {
        showQuestion();
    } else {
        getQuestion();
    }
    cout << "bey!" << endl;
}

//TODO
void GameView::showQuestion() {
    Player *player = dynamic_cast<Player *>(controller->getLoginUser());
    String word, ans;
    while (true) {
        ans = controller->getWord();
        cout << "word: " + ans << endl;
        sleep(2);

        cout << "please input the word if you can remember(\\quit to exit)" << endl;
        cin >> word;
        if (word == "\\quit")
            break;
        else if (word == ans) {
            player->exprIncrease(EXPR_FOR_USER);
            cout << "you are right!" << endl;
        }
        player->playedNumIncrease();
    }
}

void GameView::getQuestion() {
    Master *master = dynamic_cast<Master *>(controller->getLoginUser());
    String word;
    while (true) {
        cout << "please input a word (\\quit to exit)" << endl;
        cin >> word;
        if (word == "\\quit")
            break;
        else if (!regex_match(word, matchWord))
            cout << "please input a valid word!(lowercase)" << endl;
        else if (!controller->saveWord(word))
            cout << "this word has already in the database!" << endl;
        else {
            master->exprIncrease(EXPR_FOR_USER);
            master->outNumIncrease();
            cout << "word:" + word + " has been saved successfully!" << endl;
        }
    }
}

UserController *MainView::controller = nullptr;

void MainView::showMain() {
    controller = UserController::getInstance();
    std::string command;
    std::cout << "guest@main>";
    while (std::cin >> command) {
        if (command == "login") {
            LoginView::showLogin();
        } else if (command == "register") {
            RegisterView::showRegister();
        } else if (command == "play") {
            GameView::showGame();
        } else if (command == "order") {
            OrderView::showOrder();
        } else if (command == "logout") {
            controller->logout();
        } else if (command == "exit") {
            std::cout << "bey!" << std::endl;
            break;
        } else if (command == "help") {
            std::cout << "login" << std::endl
                      << "register" << std::endl
                      << "play" << std::endl
                      << "order" << std::endl
                      << "exit" << std::endl;
        } else {
            std::cout << "unknown command" << std::endl;
        }
        if (controller->hasLogin()) {
            cout << controller->getLoginUser()->getUsername() + "@main>";
        } else {
            std::cout << "guest@main>";
        }
    }
}
