#include "ApiSetup.hpp"

std::vector<std::string>	ApiSetup::env;
std::string 				ApiSetup::dbName;
std::string 				ApiSetup::dbUserName;
std::string 				ApiSetup::dbPassWd;
std::string 				ApiSetup::dbHost;
std::string 				ApiSetup::dbPort;

ApiSetup::ApiSetup()
{
}

ApiSetup::~ApiSetup()
{
}

void ApiSetup::getEnvData(std::string filename)
{
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open())
		throw ExceptionController("ERROR: Unable to open the file");
	while (std::getline(file, line))
	{
		if (line.find("#") == line.npos && !line.empty())
			this->env.push_back(line);
	}
	file.close();
}

void ApiSetup::dbSetupEnv()
{
	for (size_t it = 0; it < env.size(); it++)
	{
		if (env.at(it).find("dbname") != env.at(it).npos)
			this->dbName = env.at(it);
		if (env.at(it).find("user") != env.at(it).npos)
			this->dbUserName = env.at(it);
		if (env.at(it).find("password") != env.at(it).npos)
			this->dbPassWd = env.at(it);
		if (env.at(it).find("host") != env.at(it).npos)
			this->dbHost = env.at(it);
		if (env.at(it).find("port") != env.at(it).npos)
			this->dbPort = env.at(it);
	}
}

void ApiSetup::setRoutes(Pistache::Rest::Router &router)
{
	UserController userController;

	Pistache::Rest::Routes::Post(router, "/login", Pistache::Rest::Routes::bind(&UserController::loginController, &userController));
}

void ApiSetup::runServer()
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

//GETTERS
std::string ApiSetup::getDbName()
{
	return (dbName);
}

std::string ApiSetup::getDbUserName()
{
	return (dbUserName);
}

std::string ApiSetup::getDbPassWd()
{
	return (dbPassWd);
}

std::string ApiSetup::getDbHost()
{
	return (dbHost);
}

std::string ApiSetup::getDbPort()
{
	return (dbPort);
}