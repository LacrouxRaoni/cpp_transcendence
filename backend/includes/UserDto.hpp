#ifndef  USERDTO_HPP
# define USERDTO_HPP

#include <iostream>
#include "ExceptionController.hpp"
#include <rapidjson/document.h>

class UserDto
{
	private:
		std::string token;

	public:
		UserDto();
		UserDto(std::string token);
		~UserDto();
		UserDto(const UserDto &rsc);
		UserDto& operator=(UserDto const &rsc);

		//GETTERS
		std::string	getToken() const;

		//METHODS
		UserDto*	loginDto(const std::string &body);
};

#endif