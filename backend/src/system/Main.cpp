#include "ApiSetup.hpp"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		ApiSetup api;
		api.getEnvData(argv[1]);
		api.dbSetupEnv();
		api.runServer();
	}
	else
	{
		std::cout << "ERROR: env file is missing" << std::endl;
		return (1);
	}
	return (0);
}