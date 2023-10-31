#ifndef USERSERVICE_HPP
# define USERSERVICE_HPP

#include "UserDto.hpp"
#include "UserEntity.hpp"
#include "ApiSetup.hpp"

#include <jwt-cpp/jwt.h>


#include <fstream>
#include <vector>
#include <curl/curl.h>


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
		std::string		treatTokenRequest(std::string dtoChecker);
		static void		buildRequestData(std::string &requestData, std::string &apiUrl, std::string &apiUserInfo, std::string &token);
		std::string		requestTo42Api(const char *param, const char *requestData, int method);
		static size_t	WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
		std::string		parse42Json(std::string responseBody, std::string param);

		//GETTERS
		std::string getDtoChecker() const;
		
};
#endif