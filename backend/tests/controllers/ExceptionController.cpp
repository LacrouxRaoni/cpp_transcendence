#include "ExceptionController.hpp"

ExceptionController::ExceptionController(const std::string msg) : msg(msg)
{
}

ExceptionController::~ExceptionController()
{
}

const char* ExceptionController::what() const throw()
{
	return msg.c_str();	
}

