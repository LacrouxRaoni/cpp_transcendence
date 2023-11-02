#include "ApiSetup.hpp"

std::vector<std::string>	ApiSetup::env;
std::string 				ApiSetup::dbName;
std::string 				ApiSetup::dbUserName;
std::string 				ApiSetup::dbPassWd;
std::string 				ApiSetup::dbHost;
std::string 				ApiSetup::dbPort;
std::string 				ApiSetup::issuerJwt;
std::string 				ApiSetup::typeJwt;
std::string 				ApiSetup::claimJwt;
std::string 				ApiSetup::secretJwt;

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
	{
		std::cerr << "ERROR: Unable to open the file" << std::endl;
		return ;
	}
	while (std::getline(file, line))
	{
		if (line.find("#") == line.npos && !line.empty())
			this->env.push_back(line);
	}
	file.close();
}

int ApiSetup::dbSetupEnv()
{
	for (size_t it = 0; it < env.size(); it++)
	{
		if (env.at(it).find("dbname") != env.at(it).npos)
			this->dbName = env.at(it);
		else if (env.at(it).find("user") != env.at(it).npos)
			this->dbUserName = env.at(it);
		else if (env.at(it).find("password") != env.at(it).npos)
			this->dbPassWd = env.at(it);
		else if (env.at(it).find("host") != env.at(it).npos)
			this->dbHost = env.at(it);
		else if (env.at(it).find("port") != env.at(it).npos)
			this->dbPort = env.at(it);
		else if (env.at(it).find("issuerjwt") != env.at(it).npos)
			this->issuerJwt = env.at(it).substr(env.at(it).find("=") + 1);
		else if (env.at(it).find("typejwt") != env.at(it).npos)
			this->typeJwt = env.at(it).substr(env.at(it).find("=") + 1);
		else if (env.at(it).find("claimjwt") != env.at(it).npos)
			this->claimJwt = env.at(it).substr(env.at(it).find("=") + 1);
		else if (env.at(it).find("secretjwt") != env.at(it).npos)
			this->secretJwt = env.at(it).substr(env.at(it).find("=") + 1);
		else
		{
			std::cerr << "Invalid argument in env file" << std::endl;
			return 1;
		}
	}
	return 0;
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

std::string ApiSetup::getIssuerJwt()
{
	return (issuerJwt);
}
std::string ApiSetup::getTypeJwt()
{
	return (typeJwt);
}
std::string ApiSetup::getClaimJwt()
{
	return (claimJwt);
}

std::string ApiSetup::getSecretJwt()
{
	return (secretJwt);
}
