#include "networkManager.h"
#include "curl/curl.h"
#include <nlohmann/json.hpp>
//int qstate;

#include <locale>
#include <codecvt>

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp){
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


		std::cout << readBuffer << std::endl;

		try {
			json result = json::parse(readBuffer);
			//std::cout << result.dump() << std::endl;
			id = std::stoi(result["userId"].get<std::string>());
			accountName = result["username"].get<std::string>();
			averageWPM = std::stoi(result["userWPM"].get<std::string>());
			averageACC = std::stoi(result["userACC"].get<std::string>());
			APIkey = result["uniqueKey"].get<std::string>();
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
}

void NetworkManager::uploadResult(int wpm, int acc){

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

}

void NetworkManager::updateStats(){
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

static std::mutex notifMutex;

void longPollServer(bool *polling, int id, int *lastModifyTime, std::vector<std::string>* notifications){
	*polling = true;
	CURL* curl;
	CURLcode res;

	std::string str = "uniquekey=" + std::to_string(id) + "&lastupdate="+std::to_string(*lastModifyTime);
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	std::string readBuffer;
	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */



		curl_easy_setopt(curl, CURLOPT_URL, "https://typerrgame.000webhostapp.com/long_poll.php");
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

			std::lock_guard<std::mutex> lock(notifMutex);
			notifications->push_back(result["content"].get<std::string>());

			*lastModifyTime = result["time"].get<int>();
			std::cout << *lastModifyTime << std::endl;
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
	*polling = false;
}

void NetworkManager::startPolling(){
	m_Futures.push_back(std::async(std::launch::async, longPollServer, &polling, id, &lastModifyTime, &serverEvents));
}

int NetworkManager::getWPM(){
	return averageWPM;
}

int NetworkManager::getACC(){
	return averageACC;
}


void NetworkManager::whosonline(){
	CURL* curl;
	CURLcode res;

	//std::string str = "id=" + std::to_string(id);
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	std::string readBuffer;
	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */



		curl_easy_setopt(curl, CURLOPT_URL, "https://typerrgame.000webhostapp.com/whosonline.php");
		/* Now specify the POST data */
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);


		std::cout << readBuffer << std::endl;

		try {
			json result = json::parse(readBuffer);
			std::cout << result.dump() << std::endl;
			onlinePlayers.clear();
			for (int i = 0; i < result.size(); i++) {
				onlinePlayers.push_back({stoi(result[i][0].get<std::string>()), result[i][1].get<std::string>()});
			}
			std::cout << onlinePlayers.size() << std::endl;
			std::cout << onlinePlayers[0].id << " " << onlinePlayers[0].name << std::endl;

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

void NetworkManager::duelRequest(int id){

	CURL* curl;
	CURLcode res;

	std::string str = "uniqueKey="+APIkey+"&id="+std::to_string(id)+"&who="+std::to_string(this->id)+"&name="+accountName;
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

		//https://typerrgame.000webhostapp.com/requestduel.php?uniqueKey=67fa0f92f7eacc218a5257f8ec5de129&id=5&who=4&name=skamazzz

		curl_easy_setopt(curl, CURLOPT_URL, "https://typerrgame.000webhostapp.com/requestduel.php");
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

	//updateStats();

}

bool NetworkManager::acceptRequest(int from) {

	CURL* curl;
	CURLcode res;

	std::string str = "uniqueKey=" + APIkey + "&id=" + std::to_string(id) + "&from=" + std::to_string(from);
	int returnval = 0;
	bool success = true;
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	std::string readBuffer;
	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */

		   //https://typerrgame.000webhostapp.com/requestduel.php?uniqueKey=67fa0f92f7eacc218a5257f8ec5de129&id=5&who=4&name=skamazzz

		curl_easy_setopt(curl, CURLOPT_URL, "https://typerrgame.000webhostapp.com/acceptduel.php");
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
			//id = std::stoi(result["userId"].get<std::string>());
			//accountName = result["username"].get<std::string>();
			//averageWPM = std::stoi(result["userWPM"].get<std::string>());
			//averageACC = std::stoi(result["userACC"].get<std::string>());
			//loggedIn = true;
			returnval = 1;

		}
		catch (json::exception & e)
		{
			success = false;
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

	//get words
	std::cout << "should get words from gamefile testfile" << id << who << ".txt i guess" << std::endl;
	if(success)
		getWords(id, who);
	return success;
}

bool NetworkManager::getWords(int id1, int id2) {
	CURL* curl;
	CURLcode res;

	std::string str = "uniqueKey="+APIkey+"&id1=" + std::to_string(id1) + "&id2=" + std::to_string(id2);
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	std::string readBuffer;
	bool success = true;
	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */



		curl_easy_setopt(curl, CURLOPT_URL, "https://typerrgame.000webhostapp.com/getwords.php");
		/* Now specify the POST data */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);


		std::cout << readBuffer << std::endl;
		//std::wstring wreadBuffer(readBuffer.begin(), readBuffer.end());

		try {
			json result = json::parse(readBuffer);
			std::cout << result.dump() << std::endl;
			dueltext.clear();
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

			for (int i = 0; i < result.size(); i++) {
				std::wstring line = converter.from_bytes(result[i].get<std::string>());
				dueltext.push_back({line});
			}
			TEST = dueltext[1];
			//std::cout << dueltext.size() << std::endl;
			//std::wstring test = L"Привет";
			//std::wcout << test << std::endl;
			//std::cout << (int)dueltext[0][1] << std::endl;
			//std::cout << (int)test[1] << std::endl;
			//messages.push_back({ std::to_string(dueltext[0][3]) + dueltext[0], 10.f });
			/*onlinePlayers.clear();
			for (int i = 0; i < result.size(); i++) {
				onlinePlayers.push_back({ stoi(result[i][0].get<std::string>()), result[i][1].get<std::string>() });
			}
			std::cout << onlinePlayers.size() << std::endl;
			std::cout << onlinePlayers[0].id << " " << onlinePlayers[0].name << std::endl;*/

		}
		catch (json::exception & e)
		{
			success = false;
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

	activeRequest = false;
	gotoduel = true;
	return success;
}

void NetworkManager::sendReady(int from, int to) {

	CURL* curl;
	CURLcode res;

	std::string str = "from=" + std::to_string(from) + "&to=" + std::to_string(to);
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

		   //https://typerrgame.000webhostapp.com/requestduel.php?uniqueKey=67fa0f92f7eacc218a5257f8ec5de129&id=5&who=4&name=skamazzz

		curl_easy_setopt(curl, CURLOPT_URL, "https://typerrgame.000webhostapp.com/ready.php");
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

	//updateStats();

}

bool NetworkManager::sendDuelResult(int from, int to, float time, int wpm, int acc, int score) {

	CURL* curl;
	CURLcode res;

	std::string str = "from=" + std::to_string(from) + "&to=" + std::to_string(to) + "&time=" + std::to_string(time) + "&wpm=" + std::to_string(wpm) + "&acc=" + std::to_string(acc) + "&score=" + std::to_string(score);
	int returnval = 0;
	bool success = true;
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	std::string readBuffer;
	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */

		   //https://typerrgame.000webhostapp.com/requestduel.php?uniqueKey=67fa0f92f7eacc218a5257f8ec5de129&id=5&who=4&name=skamazzz

		curl_easy_setopt(curl, CURLOPT_URL, "https://typerrgame.000webhostapp.com/duelresult.php");
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
			if (result["content"] == "success") {
				std::cout << "we coo" << std::endl;
				result = true;
			}
			/*id = std::stoi(result["userId"].get<std::string>());
			accountName = result["username"].get<std::string>();
			averageWPM = std::stoi(result["userWPM"].get<std::string>());
			averageACC = std::stoi(result["userACC"].get<std::string>());
			loggedIn = true;
			returnval = 1;*/

		}
		catch (json::exception & e)
		{
			success = false;
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

	//updateStats();
	return success;
}

std::wstring NetworkManager::getAccountName() {
	std::wstring wstr(accountName.begin(), accountName.end());
	return wstr;
}

void NetworkManager::drawServerMessages(sf::RenderWindow* window, float fElapsedTime){
	if (!serverEvents.empty()) {
		std::cout << serverEvents.front() << std::endl;
		json result = json::parse(serverEvents.front());

		if (result["sendType"] == "notification") {
			std::cout << "oh wow" << std::endl;
			if (result["content"] == "login_success"){
				messages.push_back({ "Вы успешно зашли в свой аккаунт!", 4.f});
			}
		}

		if (result["sendType"] == "onlinecheck") {
			std::cout << "WE GUCCI" << std::endl;
		}

		if (result["sendType"] == "duelRequest") {
			activeRequest = true;
			who = std::stoi(result["from"].get<std::string>());
			std::cout << "ok we got a request from " << who << std::endl;
			opponentname = result["senderName"].get<std::string>();
			messages.push_back({result["senderName"].get<std::string>() + " вызывает вас на дуэль!", 10.f, true, who});
		}

		if (result["sendType"] == "requestAccepted") {
			//get words
			std::cout << "should get words from gamefile testfile" << who << id << ".txt i guess" << std::endl;
			while(!getWords(who, id));

		}

		if (result["sendType"] == "opponentReady") {
			if(gotoduel)
				opponentReady = true;
		}

		if (result["sendType"] == "opponentResult") {
			opponentResult = true;
			os_time = std::stof(result["time"].get<std::string>());
			os_WPM = std::stoi(result["WPM"].get<std::string>());
			os_ACC = std::stoi(result["ACC"].get<std::string>());
			os_score = std::stoi(result["score"].get<std::string>());
		}

		serverEvents.erase(serverEvents.begin());
	}

	//mainText.setString(TEST);
	//mainText.setCharacterSize(30);
	//mainText.setPosition(340, 340);
	////textWidth = sfText->getLocalBounds().width;
	//window->draw(mainText);

	if (!messages.empty()) {
		//for (int i = 0; i < messages.size(); i++) {
			messages[0].update(fElapsedTime);
			//std::cout << "doin it" << std::endl;
			messages[0].show(window, &mainText, fElapsedTime);
		//}
		for (int i = messages.size() - 1; i >= 0; i--) {
			if (messages[i].finished) messages.erase(messages.begin() + i);
		}
	}



}

bool NetworkManager::isLoggedIn() {
	return loggedIn;
}