#include "UserEntity.hpp"


UserEntity::UserEntity()
{
}

UserEntity::UserEntity(std::string login, std::string fNname, std::string lName, std::string nickname)
{
	this->login = login;
	this->fNname = fNname;
	this->lName = lName;
	this->nickname = nickname;
}

UserEntity::~UserEntity()
{
}

UserEntity::UserEntity(const UserEntity &rsc)
{
	*this = rsc;
}

UserEntity& UserEntity::operator=(UserEntity const &rsc)
{
	if (this != &rsc)
	{
		this->login = rsc.nickname;
		this->fNname = rsc.fNname;
		this->lName = rsc.lName;
		this->nickname = rsc.nickname;
	}
	return *this;
}

bool	UserEntity::checkIfUserIsinDb()
{
	if (UserRepository::selectUserByUserLogin(this->login))
		return true;
	return false;
}

void UserEntity::saveNewUser(const UserEntity user)
{
	UserRepository::addNewUserInDb(user);
}

//GETTERS
std::string	UserEntity::getLogin() const
{
	return(this->login);
}

std::string UserEntity::getFNname() const
{
	return(this->fNname);
}

std::string UserEntity::getLName() const
{
	return(this->lName);
}

std::string UserEntity::getNickname() const
{
	return(this->nickname);
}
