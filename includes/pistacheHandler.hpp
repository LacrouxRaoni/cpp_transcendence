#ifndef PISTACHEHANDLER_HPP
#define PISTACHEHANDLER_HPP

#include <pistache/endpoint.h>
#include <iostream>

using namespace Pistache;

class HelloHandler : public Http::Handler 
{
	public:
    	HTTP_PROTOTYPE(HelloHandler)
    	void onRequest(const Http::Request& request, Http::ResponseWriter response);

};

class PistacheHandler 
{
	public:
		void run();
};

#endif