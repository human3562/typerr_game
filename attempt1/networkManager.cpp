#include "networkManager.h"
//int qstate;
int NetworkManager::login(std::wstring uid, std::wstring pwd) {
	int returnval = 0; //0 - no user, 1 - success, 2 - connection error, 3 - sql error
	try {
		sql::Driver* driver;
		sql::Connection* con;
		//sql::Statement* stmt;
		sql::ResultSet* res;
		sql::PreparedStatement* prep_stmt;

		driver = get_driver_instance();
		con = driver->connect("127.0.0.1:3306", "root", "");

		if (con->isValid()) {
			std::cout << "dick" << std::endl;
		}
		else {
			std::cout << "uh-oh" << std::endl;
			returnval = 2;
		}

		con->setSchema("typerDB");
		

		prep_stmt = con->prepareStatement("SELECT * FROM users WHERE uidUsers = ? AND pwdUsers = ?");
		std::string str1 = std::string(uid.begin(), uid.end());
		std::string str2 = std::string(pwd.begin(), pwd.end());
		prep_stmt->setString(1, str1);
		prep_stmt->setString(2, str2);
		prep_stmt->execute();

		res = prep_stmt->executeQuery();
		
		while (res->next()) {
			std::cout << "ID: " << res->getString("idUsers") << "; UID: " << res->getString("uidUsers") << "; Email: " << res->getString("emailUsers") << std::endl;
			id = std::stoi(res->getString("idUsers"));
			accountName = res->getString("uidUsers");
			loggedIn = true;
			returnval = 1;
		}
		
		/*stmt = con->createStatement();

		res = stmt->executeQuery("SELECT * FROM users");
		while (res->next()){
			std::cout << "ID: " << res->getString("idUsers") << "; UID: " << res->getString("uidUsers") << "; Email: " << res->getString("emailUsers") << std::endl;
		}*/
		
		delete res;
		//delete stmt;
		delete prep_stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		/*
		  MySQL Connector/C++ throws three different exceptions:

		  - sql::MethodNotImplementedException (derived from sql::SQLException)
		  - sql::InvalidArgumentException (derived from sql::SQLException)
		  - sql::SQLException (derived from std::runtime_error)
		*/
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		/* what() (derived from std::runtime_error) fetches error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		returnval = 3;

	}
	return returnval;
}

std::wstring NetworkManager::getAccountName() {
	std::wstring wstr(accountName.begin(), accountName.end());
	return wstr;
}

bool NetworkManager::isLoggedIn() {
	return loggedIn;
}