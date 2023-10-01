#include "UserController.hpp"

void UserController::loginController(const Rest::Request& request, Http::ResponseWriter response)
{
	UserDto userDto;

	userDto.loginDto(request.body());

	response.send(Http::Code::Ok, "Hello, World\n");

}