#ifndef USERSERVICE_HPP
# define USERSERVICE_HPP

#include "UserDto.hpp"

class UserService {
	private:
		std::string dtoChecker;
	public:
		UserService();
		UserService(std::string dto);
		~UserService();
		UserService(const UserService &rsc);
		UserService& operator=(UserService const &rsc);

		//METHODS
		void treatTokenRequest(std::string dtoChecker);

		//GETTERS
		std::string getDtoChecker() const;
		
};
#endif