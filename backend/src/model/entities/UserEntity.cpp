#include "UserEntity.hpp"

UserEntity::UserEntity()
{
}

UserEntity::UserEntity(std::string login)
{
	this->login = login;
}

UserEntity::UserEntity(std::string fNname, std::string lName, std::string nickname)
{
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
		this->fNname = rsc.fNname;
		this->lName = rsc.lName;
		this->nickname = rsc.nickname;
	}
	return *this;
}