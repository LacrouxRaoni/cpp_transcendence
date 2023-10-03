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
	if (body.find("\"login\"") != body.npos && body.find("\"email\"") != body.npos)
	{
		/*size_t	start = body.find(":");
		std::string tmpLogin = body.substr(body.find_first_of("\"", start) + 1, body.find_last_of(",") - (start + 4));
		start = body.find(":", start + 1);
		std::string tmpEmail = body.substr(body.find_first_of("\"", start) + 1, body.find_last_of("\n") - (start + 4));
		*/
		rapidjson::Document document;
		document.Parse(body.c_str());
		return (new UserDto(document["login"].GetString(), document["email"].GetString()));
	}
	throw ExceptionController("ERROR: Invalid data\n");
}
