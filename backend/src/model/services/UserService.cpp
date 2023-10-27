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

void UserService::buildRequestData(std::string &requestData, std::string &apiUrl, std::string &apiUserInfo, std::string &token)
{
	for (size_t i = 0; i < ApiSetup::env.size(); i++)
	{
		if (i == 3)
			requestData += "code=" + token + "&" + ApiSetup::env.at(i);
		else if (i > 3)
		{
			apiUrl = ApiSetup::env.at(i).substr(ApiSetup::env.at(i).find("=") + 2, ApiSetup::env.at(i).find_last_of("\"") - ApiSetup::env.at(i).find("=") - 2);
			apiUserInfo = ApiSetup::env.at(i + 1).substr(ApiSetup::env.at(i + 1).find("=") + 2, ApiSetup::env.at(i + 1).find_last_of("\"") - ApiSetup::env.at(i + 1).find("=") - 2);
			break ;
		}
		else
			requestData += ApiSetup::env.at(i) + "&";
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
    std::string 				requestData;
	std::string					apiUrl;
	std::string					apiUserInfo;
	std::string					auth_bearer;
    std::string					responseBody;

	//PARTE 2
	buildRequestData(requestData, apiUrl, apiUserInfo, token);

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


	UserEntity user(nickname, fName, lName, nickname);
	std::cout << user.GetLogin() << std::endl;
	if (user.checkIfUserIsinDb() == true)
		std::cout << "existe" << std::endl;
	else
	{
		user.saveNewUser(user);
		std::cout << "salvo, meu bom!" << std::endl;
	}

	
	
	
	
	
	
	
	
	
	std::string tokenJwt = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJpc3MiOiJhdXRoMCJ9.AbIJTDMFc7yUa5MhvcP03nJPyCPzZtQcGEp-zWfOkEE";
    auto decoded = jwt::decode(tokenJwt);

    for(auto& e : decoded.get_payload_json())
	{
        std::cout << e.first << " = " << e.second << std::endl;
	}
		
	auto verifier = jwt::verify()
	    .allow_algorithm(jwt::algorithm::hs256{ "secret" })
	    .with_issuer("auth0");

	verifier.verify(decoded);

	auto new_token = jwt::create()
    .set_issuer("auth0")
    .set_type("JWS")
    .set_payload_claim("sample", jwt::claim(std::string("test")))
    .sign(jwt::algorithm::hs256{"secret"});

	std::cout << new_token << std::endl;


	return responseBody;
}

//GETTERS
std::string UserService::getDtoChecker() const
{
	return dtoChecker;
}