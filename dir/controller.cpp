#include "controller.h"

UserController::UserController()
{
}

UserController::~UserController()
{
}

UserController * UserController::getInstance()
{
	return nullptr;
}

bool UserController::login(String & username, String & password)
{
	User u = service->getUserByName(username);
	if (u.getPassword() == password) {
		loginUser = u;
		return true;
	}
	return false;
}

bool UserController::logout()
{
	if (loginUser.getUsername().empty()) {
		return false;
	}
	service->updateUser(loginUser);
	loginUser.setUsername("");
	return true;
	
	
}

bool UserController::signUp(String & username, String & password, bool isplayer)
{
	if (service->getUserByName().getUsername().empty()) {
		if (isplayer) {
			Player p;
			p.setUsername(username);
			p.setPassword(password);
			service->updateUser(p);
		}
		else {
			Master p;
			p.setUsername(username);
			p.setPassword(password);
			service->updateUser(p);
		}
		return true;
	}
	return false;
}

User UserController::findByName(String & name)
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
