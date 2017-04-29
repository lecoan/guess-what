
#include "view.h"

int main() {
    MainView::showMain();

    UserService::getInstance()->writeToDisk();
    WordService::getInstance()->writeToDisk();
    return 0;
}