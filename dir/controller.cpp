#include "controller.h"

UserController::~UserController()
{
}

UserController * UserController::getInstance()
{
    if(instance == nullptr) {
        instance = new UserController();
    }
	return instance;
}

bool UserController::login(String & username, String & password)
{
	User * u = service->getUserByName(username);
	if (u!= nullptr && u->getPassword() == password) {
		loginUser = u;
		return true;
	}
	return false;
}

bool UserController::logout()
{
	if (loginUser->getUsername().empty()) {
		return false;
	}
	service->updateUser(loginUser);
	return true;
}

bool UserController::signUp(String & username, String & password, bool isplayer)
{
    User * user;
	if (service->getUserByName(username)== nullptr) {
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

User* UserController::findByName(String & name)
{
	return service->getUserByName(name);
}

std::set<String> UserController::findByCondition(Condition & con)
{
	return service->getOrder(con.level,con.nums,con.type);
}

bool UserController::hasLogin()
{
	return !loginUser.getUsername().empty();
}

UserController::Condition::Condition()
{
	level = -1;
	nums = -1;
	type = "";
}
