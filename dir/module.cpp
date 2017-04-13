#include "module.h"

String User::getUsername()
{
	return this->username;
}

void User::setUsername(String name)
{
	this->username = name;
}

String User::getPassword()
{
	return this->password;
}

void User::setPassword(String pw)
{
	this->password = pw;
}

unsigned User::getLevel()
{
	return this->level;
}

void User::levelIncrease(int n)
{
	this->level += n;
}

unsigned User::getExpr()
{
	return this->expr;
}

void User::exprIncrease(int n)
{
	//TODO add level
	this->expr += n;
}

String User::getType()
{
	return this->type;
}

unsigned Player::getPlayedNum()
{
	return this->playedNum;
}

void Player::playedNumIncrease(int n)
{
	this->playedNum++;
}

unsigned Master::getOutNum()
{
	return this->outNum;
}

void Master::outNumIncrease(int n)
{
	this->outNum += n;
}

const String UserService::PATH = "./data/users";

UserService::UserService()
{
	//TODO
}

UserService::~UserService()
{
	//TODO
}

UserService * UserService::getInstance()
{
	if (instance == nullptr) {
		instance = new UserService();
	}
	return nullptr;
}

void UserService::updateUser(User & user)
{
	this->userSet.insert(user);
}


void UserService::addExpr(String name)
{
}

std::set<String> UserService::getOrder(unsigned level, unsigned nums, String type)
{
	std::set<String> ans;
	for (auto it = this->userSet.begin(); it != userSet.end(); ++it) {
		if (it->getLevel == level || level == -1) {
			if (type.empty() || type == it->getType) {
				if (nums == -1) {
					ans.insert(it->getUsername);
				}
				if (type == "Player") {
					
				}
				else {

				}
			}
		}
	}
}


const String WordService::PATH = "./data/words";

WordService::WordService()
{
	//TODO ¶ÁÈ¡´Ê¿â
}

WordService::~WordService()
{
	delete instance;
}

WordService * WordService::getInstance()
{
	if (instance == nullptr) {
		instance = new WordService();
	}
	return instance;
}

String WordService::getWord(int level)
{
	
}

void WordService::saveWord(String word)
{
	this->wordSet.insert(word);
}

bool operator==(User & a, User & b)
{
	return a.username == b.username;
}

bool operator<(User & a, User & b)
{
	return a.username < b.username;
}
