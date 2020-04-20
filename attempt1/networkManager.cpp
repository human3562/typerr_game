#include "networkManager.h"

#include "curl/curl.h"
#include <nlohmann/json.hpp>
//int qstate;

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}


int NetworkManager::login(std::wstring uid, std::wstring pwd) {

	CURL* curl;
	CURLcode res;

	std::string str1 = std::string(uid.begin(), uid.end());
	std::string str2 = std::string(pwd.begin(), pwd.end());
	std::string str = "uid="+str1+"&pwd="+str2;
	int returnval = 0;
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	std::string readBuffer;
	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */
		
		

		curl_easy_setopt(curl, CURLOPT_URL, "https://typerrgame.000webhostapp.com/login.inc.php");
		/* Now specify the POST data */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);


		//std::cout << readBuffer << std::endl;

		try {
			json result = json::parse(readBuffer);
			//std::cout << result.dump() << std::endl;
			id = std::stoi(result["userId"].get<std::string>());
			accountName = result["username"].get<std::string>();
			averageWPM = std::stoi(result["userWPM"].get<std::string>());
			averageACC = std::stoi(result["userACC"].get<std::string>());
			loggedIn = true;
			returnval = 1;

		}
		catch (json::exception & e)
		{
			// output exception information
			std::cout << "message: " << e.what() << '\n'
				<< "exception id: " << e.id << std::endl;
		}


		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	return returnval;



	//int returnval = 0; //0 - no user, 1 - success, 2 - connection error, 3 - sql error
	//try {
	//	sql::Driver* driver;
	//	sql::Connection* con;
	//	sql::Statement* stmt;
	//	sql::ResultSet* res;
	//	sql::PreparedStatement* prep_stmt;

	//	driver = get_driver_instance();
	//	con = driver->connect("typerrgame.000webhostapp.com", "id13359092_human3562", "+Q<d2n0QSb54\z+R");

	//	if (con->isValid()) {
	//		std::cout << "connection good" << std::endl;
	//	}
	//	else {
	//		std::cout << "uh-oh" << std::endl;
	//		returnval = 2;
	//	}

	//	con->setSchema("id13359092_typerdb");
	//	

	//	prep_stmt = con->prepareStatement("SELECT * FROM users WHERE uidUsers = ? AND pwdUsers = ?");
	//	std::string str1 = std::string(uid.begin(), uid.end());
	//	std::string str2 = std::string(pwd.begin(), pwd.end());
	//	prep_stmt->setString(1, str1);
	//	prep_stmt->setString(2, str2);
	//	prep_stmt->execute();

	//	res = prep_stmt->executeQuery();
	//	
	//	while (res->next()) {
	//		std::cout << "ID: " << res->getString("idUsers") << "; UID: " << res->getString("uidUsers") << std::endl;
	//		id = std::stoi(res->getString("idUsers"));
	//		accountName = res->getString("uidUsers");
	//		loggedIn = true;
	//		returnval = 1;
	//	}

	//	stmt = con->createStatement();
	//	res = stmt->executeQuery("SELECT * FROM users WHERE idUsers = '" + std::to_string(id) + "';");

	//	while (res->next()) {
	//		std::cout << "ID: " << res->getString("idUsers") << "; UID: " << res->getString("uidUsers") << std::endl;
	//		averageWPM = std::stoi(res->getString("avgWPM"));
	//		averageACC = std::stoi(res->getString("avgACC"));
	//	}
	//	
	//	/*stmt = con->createStatement();

	//	res = stmt->executeQuery("SELECT * FROM users");
	//	while (res->next()){
	//		std::cout << "ID: " << res->getString("idUsers") << "; UID: " << res->getString("uidUsers") << "; Email: " << res->getString("emailUsers") << std::endl;
	//	}*/

	//	delete res;
	//	delete stmt;
	//	delete prep_stmt;
	//	delete con;
	//}
	//catch (sql::SQLException &e) {
	//	/*
	//	  MySQL Connector/C++ throws three different exceptions:

	//	  - sql::MethodNotImplementedException (derived from sql::SQLException)
	//	  - sql::InvalidArgumentException (derived from sql::SQLException)
	//	  - sql::SQLException (derived from std::runtime_error)
	//	*/
	//	std::cout << "# ERR: SQLException in " << __FILE__;
	//	std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
	//	/* what() (derived from std::runtime_error) fetches error message */
	//	std::cout << "# ERR: " << e.what();
	//	std::cout << " (MySQL error code: " << e.getErrorCode();
	//	std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	//	returnval = 3;

	//}
	//return returnval;
}

void NetworkManager::uploadResult(int wpm, int acc)
{

	CURL* curl;
	CURLcode res;

	std::string str = "id=" + std::to_string(id) + "&wpm=" + std::to_string(wpm) + "&acc="+ std::to_string(acc);
	int returnval = 0;
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	//std::string readBuffer;
	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */



		curl_easy_setopt(curl, CURLOPT_URL, "https://typerrgame.000webhostapp.com/uploadResult.php");
		/* Now specify the POST data */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str.c_str());
		//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);

		


		//std::cout << &readBuffer << std::endl;

		//try {
		//	json result = json::parse(readBuffer);
		//	std::cout << result.dump() << std::endl;
		//	id = std::stoi(result["userId"].get<std::string>());
		//	accountName = result["username"].get<std::string>();
		//	averageWPM = std::stoi(result["userWPM"].get<std::string>());
		//	averageACC = std::stoi(result["userACC"].get<std::string>());
		//	loggedIn = true;
		//	returnval = 1;

		//}
		//catch (json::exception & e)
		//{
		//	// output exception information
		//	std::cout << "message: " << e.what() << '\n'
		//		<< "exception id: " << e.id << std::endl;
		//}


		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);

	}
	curl_global_cleanup();

	updateStats();

	//try {
	//	sql::Driver* driver;
	//	sql::Connection* con;
	//	//sql::Statement* stmt;
	//	sql::ResultSet* res;
	//	sql::Statement* stmt;

	//	driver = get_driver_instance();
	//	con = driver->connect("typerrgame.000webhostapp.com", "id13359092_human3562", "+Q<d2n0QSb54\z+R");

	//	if (con->isValid()) {
	//		std::cout << "connection good" << std::endl;
	//	}
	//	else {
	//		std::cout << "uh-oh" << std::endl;
	//		//returnval = 2;
	//	}

	//	con->setSchema("typerDB");

	//	stmt = con->createStatement();
	//	if (stmt->execute("INSERT INTO `results` (`userid`, `wpm`, `acc`, `created_at`) VALUES ('" + std::to_string(id) + "', '" + std::to_string(wpm) + "', '" + std::to_string(acc) + "', CURRENT_TIMESTAMP);")) {
	//		std::cout << "i guess it worked" << std::endl;
	//	}
	//	else std::cout << "did something go wrong?" << std::endl;

	//	res = stmt->executeQuery("SELECT * FROM users WHERE idUsers = '"+std::to_string(id)+"';");

	//	while (res->next()) {
	//		std::cout << "ID: " << res->getString("idUsers") << "; UID: " << res->getString("uidUsers") << std::endl;
	//		averageWPM = std::stoi(res->getString("avgWPM"));
	//		averageACC = std::stoi(res->getString("avgACC"));
	//	}

	//	delete res;
	//	delete stmt;
	//	delete con;
	//}
	//catch (sql::SQLException & e) {
	//	/*
	//	  MySQL Connector/C++ throws three different exceptions:

	//	  - sql::MethodNotImplementedException (derived from sql::SQLException)
	//	  - sql::InvalidArgumentException (derived from sql::SQLException)
	//	  - sql::SQLException (derived from std::runtime_error)
	//	*/
	//	std::cout << "# ERR: SQLException in " << __FILE__;
	//	std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
	//	/* what() (derived from std::runtime_error) fetches error message */
	//	std::cout << "# ERR: " << e.what();
	//	std::cout << " (MySQL error code: " << e.getErrorCode();
	//	std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	//}

	////return 0;
}

void NetworkManager::updateStats()
{
	CURL* curl;
	CURLcode res;

	std::string str = "id="+std::to_string(id);
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	std::string readBuffer;
	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */



		curl_easy_setopt(curl, CURLOPT_URL, "https://typerrgame.000webhostapp.com/getStats.php");
		/* Now specify the POST data */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);


		std::cout << readBuffer << std::endl;

		try {
			json result = json::parse(readBuffer);
			std::cout << result.dump() << std::endl;
			averageWPM = std::stoi(result["WPM"].get<std::string>());
			averageACC = std::stoi(result["ACC"].get<std::string>());

		}
		catch (json::exception & e)
		{
			// output exception information
			std::cout << "message: " << e.what() << '\n'
				<< "exception id: " << e.id << std::endl;
		}


		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

int NetworkManager::getWPM()
{
	return averageWPM;
}

int NetworkManager::getACC()
{
	return averageACC;
}



std::wstring NetworkManager::getAccountName() {
	std::wstring wstr(accountName.begin(), accountName.end());
	return wstr;
}

bool NetworkManager::isLoggedIn() {
	return loggedIn;
}