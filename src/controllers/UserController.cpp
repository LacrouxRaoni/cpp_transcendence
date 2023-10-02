#include "UserController.hpp"

void UserController::loginController(const Rest::Request& request, Http::ResponseWriter response)
{
	try
	{
		UserDto userDto;

		UserDto *teste = userDto.loginDto(request.body());
		response.send(Http::Code::Ok, (teste->getLogin().c_str() + teste->getEmail()));
		delete teste;	
	}
	catch(const ExceptionController &e)
	{
		response.send(Http::Code::Bad_Request ,e.what());
	}
}