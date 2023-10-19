#ifndef USERCONTROLLER_HPP
#define USERCONTROLLER_HPP

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <rapidjson/document.h>

#include "ExceptionController.hpp"
#include "UserDto.hpp"
#include "UserService.hpp"



using namespace Pistache;

class UserController
{
	public:
    	void loginController(const Rest::Request& request, Http::ResponseWriter response);
};

#endif