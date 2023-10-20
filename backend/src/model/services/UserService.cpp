#include "UserService.hpp"

UserService::UserService()
{
}

UserService::UserService(std::string dto)
{
	dtoChecker = dto;	
}

UserService::~UserService()
{
}

UserService::UserService(const UserService &rsc)
{
	*this = rsc;
}

UserService& UserService::operator=(UserService const &rsc)
{
	if (this != &rsc)
	{
		this->dtoChecker = rsc.dtoChecker;
	}
	return *this;
}

void UserService::getEnvData(std::vector<std::string> &env)
{
	std::string filename = ".env";
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open())
		throw ExceptionController("ERROR: Unable to open the file");
	while (std::getline(file, line))
		env.push_back(line);
	file.close();
}

void UserService::buildRequestData(std::vector<std::string> &env, std::string &requestData, std::string &apiUrl, std::string &apiUserInfo, std::string &token)
{
	for (size_t i = 0; i < env.size(); i++)
	{
		if (i == 3)
			requestData += "code=" + token + "&" + env.at(i);
		else if (i > 3)
		{
			apiUrl = env.at(i).substr(env.at(i).find("=") + 2, env.at(i).find_last_of("\"") - env.at(i).find("=") - 2);
			apiUserInfo = env.at(i + 1).substr(env.at(i + 1).find("=") + 2, env.at(i + 1).find_last_of("\"") - env.at(i + 1).find("=") - 2);
			break ;
		}
		else
			requestData += env.at(i) + "&";
	}

	size_t found = requestData.find("\"");
    while (found != std::string::npos) {
        requestData.erase(found, 1);
        found = requestData.find("\"", found);
    }
}

size_t UserService::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) 
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

std::string UserService::requestTo42Api(const char *param, const char *requestData, int method)
{
	CURL		*curl;
	CURLcode	res;
    std::string	responseBody;

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, param);
		if (method == 1)
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestData);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, requestData));

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBody);
	}
	res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
	curl_easy_cleanup(curl);
	return responseBody;
}

std::string UserService::parse42Json(std::string responseBody, std::string param)
{
	std::string line;
	std::string word;

	size_t pos = responseBody.find(param);
	line = responseBody.substr(pos, responseBody.find_first_of(',', pos) - pos);
	word = line.substr(line.find(":") + 2, line.find_last_of("\"") - line.find(":") - 2);
	return word;
}

std::string UserService::treatTokenRequest(std::string token)
{
	std::vector<std::string>	env;
    std::string 				requestData;
	std::string					apiUrl;
	std::string					apiUserInfo;
	std::string					auth_bearer;
    std::string					responseBody;

	//PARTE 1
	getEnvData(env);

	//PARTE 2
	buildRequestData(env, requestData, apiUrl, apiUserInfo, token);

	//PARTE 3
	responseBody = requestTo42Api(apiUrl.c_str(), requestData.c_str(),1);
	size_t start = responseBody.find(":");
	auth_bearer += "Authorization: Bearer " + responseBody.substr(start + 2, responseBody.find("\"", start + 2) - (start + 2));
    responseBody.clear();

	//PARTE 4
	responseBody = requestTo42Api(apiUserInfo.c_str(), auth_bearer.c_str(),0);
	std::string fName = parse42Json(responseBody, "\"first_name\"");
	std::string	lName = parse42Json(responseBody, "\"last_name\"");
	std::string nickname = parse42Json(responseBody, "\"login\"");
	std::string hrefImg = parse42Json(responseBody, "\"small\"");
    responseBody.clear();


	//PARTE5
	std::cout << fName << std::endl;
	std::cout << lName << std::endl;
	std::cout << nickname << std::endl;
	std::cout << hrefImg << std::endl;

	/*
	oq tem no json para pegar
	fName = "first_name"
	lName = "last_name"
	nickname = "login"
	avatar = "image"

	projects = ["name":, "status":]
	achievments = "achievements[]"
	*/
	
	return responseBody;
}

//GETTERS
std::string UserService::getDtoChecker() const
{
	return dtoChecker;
}