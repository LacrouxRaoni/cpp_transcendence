#include "UserRepository.hpp"

UserRepository::UserRepository()
{
}

UserRepository::~UserRepository()
{
}

void UserRepository::setDbParam(std::string &param)
{
	param += ApiSetup::getDbName() + " ";
	param += ApiSetup::getDbUserName() + " ";
	param += ApiSetup::getDbPassWd() + " ";
	param += ApiSetup::getDbHost() + " ";
	param += ApiSetup::getDbPort();

	size_t found = param.find("\"");
    while (found != std::string::npos) 
	{
        param.erase(found, 1);
        found = param.find("\"", found);
    }
}

PGconn *UserRepository::connectWithDb()
{
	PGconn *conn;
	std::string param;
	
	setDbParam(param);
	conn = PQconnectdb(param.c_str());
	if (PQstatus(conn) == CONNECTION_BAD)
		throw ExceptionController(PQerrorMessage(conn));
	return conn;
}

std::string	UserRepository::involveValueWithQuote(const std::string value)
{
	std::string newValue;
	
	newValue.append("\'");
	newValue.append(value);
	newValue.append("\'");
	return (newValue);
}

bool UserRepository::selectUserByUserLogin(std::string value)
{
	int			numRows;
	std::string	query;
	PGresult 	*res;
	PGconn		*conn = connectWithDb();

	query.append("SELECT user_login FROM users WHERE user_login = ");
	query.append(involveValueWithQuote(value));

	res = PQexec(conn, query.c_str());
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		std::string msg = PQresultErrorMessage(res);
		PQclear(res);
		PQfinish(conn);
		throw ExceptionController(msg);
	}
	numRows = PQntuples(res);
	PQclear(res);
	PQfinish(conn);
	if (numRows > 0)
		return true;
	return false;
}

void UserRepository::addNewUserInDb(const UserEntity user)
{
	std::string	query;
	PGresult	*res;
	PGconn		*conn = connectWithDb();

	query.append("INSERT INTO users (user_login, first_name, last_name, nickname) VALUES (");
	query.append(involveValueWithQuote(user.getLogin()));
	query.append(",");
	query.append(involveValueWithQuote(user.getFNname()));
	query.append(",");
	query.append(involveValueWithQuote(user.getLName()));
	query.append(",");
	query.append(involveValueWithQuote(user.getNickname()));
	query.append(")");

	res = PQexec(conn, query.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		std::string msg = PQresultErrorMessage(res);
		PQclear(res);
		PQfinish(conn);
		throw ExceptionController(msg);
	}
	PQclear(res);
	PQfinish(conn);	
}

