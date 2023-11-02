#include "ApiSetup.hpp"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		ApiSetup api;

		api.getEnvData(argv[1]);
		if (api.dbSetupEnv() == 1)
			return (1);
		api.runServer();
	}
	else
	{
		std::cout << "ERROR: env file is missing" << std::endl;
		return (1);
	}
	return (0);
}