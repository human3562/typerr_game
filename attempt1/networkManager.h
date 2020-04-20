#pragma once
#include <string>
//#include <mysql.h>
#include <iostream>

//#include "jdbc/cppconn/connection.h"
//#include "jdbc/cppconn/driver.h"
//#include "jdbc/cppconn/resultset.h"
//#include "jdbc/cppconn/statement.h"
//#include "jdbc/cppconn/exception.h"
//#include "jdbc/cppconn/prepared_statement.h"

class NetworkManager
{
public:
	NetworkManager() {}
	~NetworkManager() {}

public:
	int login(std::wstring uid, std::wstring pwd);
	void uploadResult(int wpm, int acc);
	void updateStats();

public:
	bool isLoggedIn();
	int getWPM();
	int getACC();
	std::wstring getAccountName();

private:
	//static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	bool loggedIn = false;
	int id = -1;
	int averageWPM = 0;
	int averageACC = 0;
	std::string accountName = "Guest";
};

