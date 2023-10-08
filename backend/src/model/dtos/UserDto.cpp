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
	std::cout << body.c_str() << std::endl;
	if (body.find("\"token\"") != body.npos)
	{
		/*size_t	start = body.find(":");
		std::string tmpLogin = body.substr(body.find_first_of("\"", start) + 1, body.find_last_of(",") - (start + 4));
		start = body.find(":", start + 1);
		std::string tmpEmail = body.substr(body.find_first_of("\"", start) + 1, body.find_last_of("\n") - (start + 4));
		*/
		rapidjson::Document document;
		document.Parse(body.c_str());
		return (new UserDto(document["key2"].GetString()));
	}
	throw ExceptionController("ERROR: Invalid data\n");
}
