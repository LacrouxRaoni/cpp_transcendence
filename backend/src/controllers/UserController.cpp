#include "UserController.hpp"

void UserController::loginController(const Rest::Request& request, Http::ResponseWriter response)
{
	try
	{
		UserDto userDto;

		UserDto *teste = userDto.loginDto(request.body());
		std::cout << teste->getToken() << std::endl;
		response.send(Http::Code::Ok, (teste->getToken().c_str()));
		delete teste;
	}
	catch(const ExceptionController &e)
	{
		response.send(Http::Code::Bad_Request ,e.what());
	}
}