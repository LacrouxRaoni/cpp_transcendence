#include "UserDto.hpp"

UserDto::UserDto()
{
}

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

std::string	UserDto::getLogin() const
{
	return this->login;
}

std::string	UserDto::getEmail() const
{
	return this->email;
}

UserDto *UserDto::loginDto(const std::string &body)
{
	size_t		start;
	std::string tmpLogin = "";
	std::string tmpEmail = "";

	if (body.find("login") != body.npos)
	{
		start = body.find(":");
		tmpLogin = body.substr(body.find_first_of("\"", start) + 1, body.find_last_of(",") - (start + 4));
	}
	if (body.find("email") != body.npos)
	{
		start = body.find(":", start + 1);
		tmpEmail = body.substr(body.find_first_of("\"", start) + 1, body.find_last_of("\n") - (start + 4));
	}
	if (tmpLogin.empty() || tmpEmail.empty())
		throw "Error: There is no batata\n";
	else
		return (new UserDto(tmpLogin, tmpEmail));
}
