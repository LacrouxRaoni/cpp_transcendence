#ifndef USERENTITY_HPP
# define USERENTITY_HPP

#include <iostream>
#include <postgresql/libpq-fe.h>

class UserEntity 
{
	private:
		std::string	login;
		std::string fNname;
		std::string lName;
		std::string nickname;

	public:
		UserEntity();
		UserEntity(std::string login);
		UserEntity(std::string fNname, std::string lName, std::string nickname);
		~UserEntity();
		UserEntity(const UserEntity &rsc);
		UserEntity& operator=(UserEntity const &rsc);
};

#endif