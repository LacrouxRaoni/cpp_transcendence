#ifndef USERREPOSITORY_HPP
# define USERREPOSITORY_HPP

#include <postgresql/libpq-fe.h>
#include "ExceptionController.hpp"
#include "UserEntity.hpp"
#include "ApiSetup.hpp"

class UserEntity;

class UserRepository
{
	private:
		static std::string	involveValueWithQuote(const std::string value);
		static void			setDbParam(std::string &param);

	public:
		UserRepository();
		~UserRepository();
		UserRepository(const UserRepository& rsc);
		UserRepository& operator=(UserRepository &rsc);
		static PGconn *connectWithDb();
		bool static selectUserByUserLogin(std::string value);
		void static addNewUserInDb(const UserEntity user);

		







};

#endif