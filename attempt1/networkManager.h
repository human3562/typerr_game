#pragma once
#include <string>
//#include <mysql.h>
#include <iostream>

#include "jdbc/cppconn/connection.h"
#include "jdbc/cppconn/driver.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/exception.h"
#include "jdbc/cppconn/prepared_statement.h"

class NetworkManager
{
public:
	NetworkManager() {}
	~NetworkManager() {}

public:
	int login(std::wstring uid, std::wstring pwd);

public:
	bool isLoggedIn();
	std::wstring getAccountName();

private:
	bool loggedIn = false;
	int id = -1;
	std::string accountName = "Guest";
};

