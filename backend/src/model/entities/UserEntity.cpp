#include "UserEntity.hpp"

UserEntity::UserEntity()
{
}

UserEntity::UserEntity(std::string login)
{
	this->login = login;
}

UserEntity::UserEntity(std::string fNname, std::string lName, std::string nickname)
{
	this->fNname = fNname;
	this->lName = lName;
	this->nickname = nickname;
}

UserEntity::~UserEntity()
{
}

UserEntity::UserEntity(const UserEntity &rsc)
{
	*this = rsc;
}

UserEntity& UserEntity::operator=(UserEntity const &rsc)
{
	if (this != &rsc)
	{
		this->fNname = rsc.fNname;
		this->lName = rsc.lName;
		this->nickname = rsc.nickname;
	}
	return *this;
}

int	UserEntity::selectUserInDb()
{
	//OPEN CONNECTION WITH DB
	PGconn *conn;

	conn = PQconnectdb("dbname=pongdb dbname=pongdb user=raoni password= host=localhost port=5432");
	if (PQstatus(conn) == CONNECTION_BAD)
	{
		std::cout << "erro" << PQerrorMessage(conn) << std::endl;
		PQfinish(conn);
	}
	std::cout << "conectado "<< PQstatus(conn) << std::endl;

	PGresult *res;

	std::string value;
	//const char *query = "SELECT * FROM employees WHERE first_name = 'John' AND last_name = 'Doe'";
	value.append("SELECT * FROM users WHERE user_login = ");
	value.append("\'");
	value.append(this->login);
	value.append("\'");

	res = PQexec(conn, value.c_str());
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		std::cout << value << std::endl;
		std::cout << "erro" << PQerrorMessage(conn) << std::endl;
		PQclear(res);
	}
	int numRows = PQntuples(res);
    if (numRows > 0) {
        std::cout << "Record exists in the table." << std::endl;
    } else {
        std::cout << "Record does not exist in the table." << std::endl;
    }
	PQclear(res);
	PQfinish(conn);
	return 0;
}

void UserEntity::saveInDb()
{
	//OPEN CONNECTION WITH DB
	PGconn *conn;

	conn = PQconnectdb("dbname=pongdb dbname=pongdb user=raoni password= host=localhost port=5432");
	if (PQstatus(conn) == CONNECTION_BAD)
	{
		std::cout << "erro" << PQerrorMessage(conn) << std::endl;
		PQfinish(conn);
	}
	std::cout << "conectado "<< PQstatus(conn) << std::endl;


	//EXECUTE SQL INSERT STATMENT
	PGresult *res;

	std::string value;
	value.append("INSERT INTO users (user_login, first_name, last_name, nickname) VALUES (");
	value.append("\'");
	value.append(this->nickname);
	value.append("\'");
	value.append(",");
	value.append("\'");
	value.append(this->fNname);
	value.append("\'");
	value.append(",");
	value.append("\'");
	value.append(this->lName);
	value.append("\'");
	value.append(",");
	value.append("\'");
	value.append(this->nickname);
	value.append("\'");
	value.append(")");


	res = PQexec(conn, value.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		std::cout << value << std::endl;
		std::cout << "erro" << PQerrorMessage(conn) << std::endl;
		PQclear(res);
	}
	PQfinish(conn);
}