#ifndef USERENTITY_HPP
# define USERENTITY_HPP

#include <iostream>
#include "UserRepository.hpp"

class UserEntity 
{
	private:
		std::string	login;
		std::string fNname;
		std::string lName;
		std::string nickname;

	public:
		UserEntity();
		UserEntity(std::string login, std::string fNname, std::string lName, std::string nickname);
		~UserEntity();
		UserEntity(const UserEntity &rsc);
		UserEntity& operator=(UserEntity const &rsc);

		bool	checkIfUserIsinDb();
		void	saveNewUser(const UserEntity user);

		//GETTERS
		std::string	GetLogin() const;
		std::string GetFNname() const;
		std::string GetLName() const;
		std::string GetNickname() const;
};

#endif