#include <iostream>
#include "view.h"

int main() {
    std::string command;
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
            LoginView::showLogin();
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
    }
    return 0;
}