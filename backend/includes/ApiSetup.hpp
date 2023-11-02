#ifndef APISETUP_HPP
# define APISETUP_HPP

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "UserController.hpp"
#include "UserRepository.hpp"

class ApiSetup
{
	private:
		static std::string dbName;
		static std::string dbUserName;
		static std::string dbPassWd;
		static std::string dbHost;
		static std::string dbPort;
		static std::string issuerJwt;
		static std::string typeJwt;
		static std::string claimJwt;
		static std::string secretJwt;
	public:
		static std::vector<std::string>	env;
		ApiSetup();
		~ApiSetup();
		void	getEnvData(std::string filename);
		int		dbSetupEnv();
		void	runServer();
		void	setRoutes(Pistache::Rest::Router &router);

		//GETTERS
		static std::string getDbName();
		static std::string getDbUserName();
		static std::string getDbPassWd();
		static std::string getDbHost();
		static std::string getDbPort();
		static std::string getIssuerJwt();
		static std::string getTypeJwt();
		static std::string getClaimJwt();
		static std::string getSecretJwt();
};

#endif
