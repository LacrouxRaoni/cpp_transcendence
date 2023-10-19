#include "UserDto.hpp"

UserDto::UserDto()
{
}

UserDto::UserDto(std::string token)
{
	this->token = token;
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
		this->token = rsc.token;
	}
	return *this;
}

std::string	UserDto::getToken() const
{
	return this->token;
}

UserDto *UserDto::loginDto(const std::string &body)
{
	if (body.find("\"token\"") != body.npos)
	{
		rapidjson::Document document;
		document.Parse(body.c_str());
		return (new UserDto(document["key2"].GetString()));
	}
	throw ExceptionController("ERROR: Invalid data\n");
}
