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
		else
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


	//BUILD REQUEST TO 42 API
	buildRequestData(requestData, apiUrl, apiUserInfo, token);

	//GET BEARER TOKEN
	responseBody = requestTo42Api(apiUrl.c_str(), requestData.c_str(),1);
	if (responseBody.find("error:") != responseBody.npos)
		throw ExceptionController("ERROR: Invalid user");
	size_t start = responseBody.find(":");
	auth_bearer += "Authorization: Bearer " + responseBody.substr(start + 2, responseBody.find("\"", start + 2) - (start + 2));
    responseBody.clear();

	std::cout << "3" << std::endl;
	//GET USER DATA FROM API
	responseBody = requestTo42Api(apiUserInfo.c_str(), auth_bearer.c_str(), 0);
	std::string fName = parse42Json(responseBody, "\"first_name\"");
	std::string	lName = parse42Json(responseBody, "\"last_name\"");
	std::string nickname = parse42Json(responseBody, "\"login\"");
	std::string hrefImg = parse42Json(responseBody, "\"small\"");
    responseBody.clear();

	std::cout << "4" << std::endl;
	UserEntity user(nickname, fName, lName, nickname);
	std::cout << user.getLogin() << std::endl;
	if (user.checkIfUserIsinDb() == true)
		std::cout << "existe" << std::endl;
	else
	{
		user.saveNewUser(user);
		std::cout << "salvo, meu bom!" << std::endl;
	}

	
	
	

	
	//CREATE JWT
	auto newToken = jwt::create()
    .set_issuer(ApiSetup::getIssuerJwt())
    .set_type(ApiSetup::getTypeJwt())
    .set_payload_claim(ApiSetup::getClaimJwt(), jwt::claim(std::string (user.getLogin().c_str())))
    .sign(jwt::algorithm::hs256{ApiSetup::getSecretJwt()});



    auto decoded = jwt::decode(newToken);

    for(auto& e : decoded.get_payload_json())
	{
        std::cout << e.first << " = " << e.second << std::endl;
	}
		
	auto verifier = jwt::verify()
	    .allow_algorithm(jwt::algorithm::hs256{ ApiSetup::getSecretJwt() })
	    .with_issuer(ApiSetup::getIssuerJwt());

	verifier.verify(decoded);



	return newToken;
}

//GETTERS
std::string UserService::getDtoChecker() const
{
	return dtoChecker;
}
