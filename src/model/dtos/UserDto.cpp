#include "UserDto.hpp"

UserDto::UserDto() : login(NULL), email(NULL){}

UserDto::UserDto(std::string login, std::string email)
{
	this->login = login;
	this->email = email;
}

UserDto::~UserDto()
{
}

UserDto::UserDto(const UserDto& rsc)
{
	*this = rsc;
}

UserDto& UserDto::operator=(UserDto const &rsc)
{
	if (this != &rsc)
	{
		this->login = rsc.login;
		this->email = rsc.email;
	}
	return *this;
}

void UserDto::loginDto(const std::string &body)
{
	std::cout << body << std::endl;
}

std::string	UserDto::getLogin() const
{
	return this->login;
}

std::string	UserDto::getEmail() const
{
	return this->email;
}
