#include "controller.h"

UserController *UserController::instance = nullptr;

UserController::~UserController() {
}

UserController::Condition::Condition() {
    level = -1;
    nums = -1;
    type = "";
}

UserController *UserController::getInstance() {
    if (instance == nullptr) {
        instance = new UserController();
    }
    return instance;
}

bool UserController::login(String &username, String &password) {
    User *u = service->getUserByName(username);
    if (u != nullptr && u->getPassword() == password) {
        loginUser = u;
        return true;
    }
    return false;
}

bool UserController::logout() {
    if (loginUser == nullptr) {
        return false;
    }
    service->updateUser(loginUser);
    loginUser = nullptr;
    return true;
}

bool UserController::signUp(String &username, String &password, bool isplayer) {
    User *user;
    if (service->getUserByName(username) == nullptr) {
        if (isplayer)
            user = new Player();
        else
            user = new Master();
        user->setUsername(username);
        user->setPassword(password);
        service->saveUser(user);
        return true;
    }
    return false;
}

User *UserController::findByName(String &name) {
    return service->getUserByName(name);
}


bool UserController::hasLogin() {
    return loginUser != nullptr;
}

UserController::UserController() {
    service = UserService::getInstance();
    loginUser = nullptr;
}

User *UserController::getLoginUser() {
    return loginUser;
}

std::vector<String> UserController::getOrder(int kind, String type) {
    return service->getOrder(kind, type);
}

std::set<String> UserController::findByCondition(UserController::Condition &con) {
    return service->getUserNameByCondition(con.level,con.nums,con.type);
}


GameController *GameController::gameInstance = nullptr;

GameController::GameController() {
    service = WordService::getInstance();
    userInstance = UserController::getInstance();
}

GameController *GameController::getInstance() {
    if (gameInstance == nullptr)
        gameInstance = new GameController();
    return gameInstance;
}

void GameController::addWord(String word) {
    service->saveWord(word);
}

String GameController::getWord(int level) {
    return service->getWord(level);
}


void GameController::addExpr(int amout) {
    userInstance->getLoginUser()->exprIncrease(amout);
}

bool GameController::hasLogin() {
    return userInstance->hasLogin();
}

bool GameController::isPlayer() {
    return userInstance->getLoginUser()->getType() == "player";
}

User *GameController::getLoginUser() {
    return userInstance->getLoginUser();
}

bool GameController::saveWord(String word) {
    if(service->contain(word))
        return false;
    service->saveWord(word);
    return true;

}


