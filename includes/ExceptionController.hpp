#ifndef EXCEPTIONCONTROLLER_HPP
# define EXCEPTIONCONTROLLER_HPP

#include <iostream>

class ExceptionController : public std::exception
{
	private:
		std::string msg;
	public:
		ExceptionController(const std::string msg);
		virtual ~ExceptionController();
		virtual const char* what() const throw();
};

#endif