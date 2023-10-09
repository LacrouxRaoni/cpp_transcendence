#include "UserController.hpp"

void UserController::loginController(const Rest::Request& request, Http::ResponseWriter response)
{
	try
	{
		UserDto userDto;

		UserDto *tokenDto = userDto.loginDto(request.body());
		UserService userService(tokenDto->getToken());
		userService.treatTokenRequest(userService.getDtoChecker());	
		delete tokenDto;
		response.send(Http::Code::Ok, ("request well received"));
		
	}
	catch(const ExceptionController &e)
	{
		response.send(Http::Code::Bad_Request ,e.what());
	}
}