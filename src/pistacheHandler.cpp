#include "pistacheHandler.hpp"

void HelloHandler::onRequest(const Http::Request& request, Http::ResponseWriter response)
{
	std::cout << request.body() << std::endl;
	response.send(Http::Code::Ok, "Hello, World\n");

}

void PistacheHandler::run()
{
	Address addr(Ipv4::any(), Port(9080));
    auto opts = Http::Endpoint::options().threads(1);
	Http::Endpoint server(addr);
	server.init(opts);
	server.setHandler(Http::make_handler<HelloHandler>()); 
	server.serve();
}