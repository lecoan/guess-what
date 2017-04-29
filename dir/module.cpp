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

Player::Player() {
	type = "player";
}

unsigned Master::getOutNum()
{
	return this->outNum;
}

void Master::outNumIncrease(int n)
{
	this->outNum += n;
}

Master::Master() {
	type = "master";

}

const String UserService::PATH = "./data/users";

UserService::UserService()
{
	readUserFromDisk();
}

//TODO auto use it
UserService::~UserService()
{
	for(auto it = users.begin();it!=users.end();++it)
		delete(*it);
	delete instance;
}

UserService * UserService::getInstance()
{
	if (instance == nullptr) {
		instance = new UserService();
	}
	return nullptr;
}

void UserService::updateUser(User * user)
{

	for(auto it = levellistMap.begin();it!=levellistMap.end();++it)
	{
		if(it->first == user->getLevel())
			it->second.insert(user);
		else if(it->second.find(user)!=it->second.end()){
			it->second.erase(user);
		}
	}

	int num;
	if(user->getType() == "player"){
		num = dynamic_cast<Player*>(user)->getPlayedNum();
	} else{
		num = dynamic_cast<Master*>(user)->getOutNum();
	}
	for(auto it = numlistMap.begin();it!=numlistMap.end();++it)
	{
		if(it->first == num)
			it->second.insert(user);
		else if(it->second.find(user)!=it->second.end()){
			it->second.erase(user);
		}
	}
}


void UserService::addExpr(User * user, int num)
{
	user->exprIncrease(num);
}

std::set<String> UserService::getOrder(unsigned level, unsigned nums, String type)
{
	std::set<String> ans;

}

//TODO
void UserService::readUserFromDisk() {

}

void UserService::saveUser(User * user) {
	users.insert(user);
	//after push, the num will be +
	levellistMap[user->getLevel()].insert(user);
	int num;
	if(user->getType() == "player"){
		num = dynamic_cast<Player*>(user)->getPlayedNum();
	} else{
		num = dynamic_cast<Master*>(user)->getOutNum();
	}
	numlistMap[num].insert(user);
}

User *UserService::getUserByName(String &name) {
	if(nameMap.find(name)!=nameMap.end())
		return nameMap[name];
	return nullptr;
}


const String WordService::PATH = "./data/words";

WordService::WordService()
{
	readWordsFromDisk();
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
	return wordSet[random()%wordSet.size()];
}

void WordService::saveWord(String word)
{
	this->wordSet.push_back(word);
}

//TODO
void WordService::readWordsFromDisk() {

}

bool operator==(User & a, User & b)
{
	return a.username == b.username;
}

bool operator<(User & a, User & b)
{
	return a.username < b.username;
}
