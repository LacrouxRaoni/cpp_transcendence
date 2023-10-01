#include <pistache/endpoint.h>
#include "UserController.hpp"

#include <pistache/router.h>

void setRoutes(Pistache::Rest::Router &router)
{
	UserController userController;

	Pistache::Rest::Routes::Get(router, "/login", Pistache::Rest::Routes::bind(&UserController::loginController, &userController));
}

void runServer()
{
	//SET PORT AND INIT SERVER
	Address addr(Ipv4::any(), Port(9080));
    auto opts = Http::Endpoint::options().threads(1);
	Http::Endpoint server(addr);
	server.init(opts);


	//INSTANTIEATE CONTROLLERS CLASSES AND SET ROUTES
	Pistache::Rest::Router router;
	setRoutes(router);

	server.setHandler(router.handler()); 
	server.serve();

}

int main()
{
	runServer();
}