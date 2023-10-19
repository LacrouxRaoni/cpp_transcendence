#include "UserController.hpp"

void UserController::loginController(const Rest::Request& request, Http::ResponseWriter response)
{
	response.headers().add<Http::Header::AccessControlAllowOrigin>("*");

	try
	{
		UserDto userDto;

		UserDto *tokenDto = userDto.loginDto(request.body());
		UserService userService(tokenDto->getToken());
		std::string tmpReponse = userService.treatTokenRequest(userService.getDtoChecker());
		delete tokenDto;
		response.send(Http::Code::Ok, tmpReponse.c_str());
		
	}
	catch(const ExceptionController &e)
	{
		response.send(Http::Code::Bad_Request, e.what());
	}
}