#include "UserService.hpp"

UserService::UserService()
{
}

UserService::UserService(std::string dto)
{
	dtoChecker = dto;	
}

UserService::~UserService()
{
}

UserService::UserService(const UserService &rsc)
{
	*this = rsc;
}

UserService& UserService::operator=(UserService const &rsc)
{
	if (this != &rsc)
	{
		this->dtoChecker = rsc.dtoChecker;
	}
	return *this;
}

void UserService::treatTokenRequest(std::string dtoChecker)
{
	std::cout << "tknReq "<< dtoChecker << std::endl;
}

std::string UserService::getDtoChecker() const
{
	return dtoChecker;
}