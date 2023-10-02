#ifndef  USERDTO_HPP
# define USERDTO_HPP

#include <iostream>

class UserDto
{
	private:
		std::string login;
		std::string	email;

	public:
		UserDto();
		UserDto(std::string login, std::string email);
		~UserDto();
		UserDto(const UserDto &rsc);
		UserDto& operator=(UserDto const &rsc);

		//GETTERS
		std::string	getLogin() const;
		std::string	getEmail() const;

		//METHODS
		UserDto*	loginDto(const std::string &body);
};

#endif