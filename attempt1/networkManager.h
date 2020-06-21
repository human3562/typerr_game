#pragma once
#include <string>
//#include <mysql.h>
#include <iostream>
#include <vector>
#include <future>
#include <mutex>
#include "SFML/Graphics.hpp"
#include "msgBox.h"
//#include "jdbc/cppconn/connection.h"
//#include "jdbc/cppconn/driver.h"
//#include "jdbc/cppconn/resultset.h"
//#include "jdbc/cppconn/statement.h"
//#include "jdbc/cppconn/exception.h"
//#include "jdbc/cppconn/prepared_statement.h"


struct player {
	int id;
	std::string name;
};


class NetworkManager
{
public:
	NetworkManager() {}
	~NetworkManager() {}

public:
	int login(std::wstring uid, std::wstring pwd);
	void uploadResult(int wpm, int acc);
	void updateStats();
	void whosonline();
	void duelRequest(int id);
	bool acceptRequest(int id);
	bool getWords(int id1, int id2);
	void sendReady(int from, int to);
	bool sendDuelResult(int from, int to, float time, int wpm, int acc, int score);
	//void longPollServer();
	void startPolling();
	void stop();

public:
	bool isLoggedIn();
	int getWPM();
	int getACC();
	std::wstring getAccountName();
	std::vector<std::string> serverEvents;
	void drawServerMessages(sf::RenderWindow* window, float fElapsedTime);
	bool polling = false;
	sf::Text mainText;
	std::vector<player> onlinePlayers;
	int id = -1;
	bool cancelPoll = false;
	std::vector<MsgBox> messages;
	std::vector<std::wstring> dueltext;
	bool activeRequest = false;
	int who = -1;
	bool gotoduel = false;
	std::string opponentname = "";
	std::wstring TEST = L"";
	bool opponentReady = false;

	bool opponentResult = false;
	float os_time = 0;
	int os_WPM = 0;
	int os_ACC = 0;
	int os_score = 0;

private:
	std::vector<std::future<void>> m_Futures;
	//static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	int lastModifyTime = 0;
	bool loggedIn = false;
	//int id = -1;
	int averageWPM = 0;
	int averageACC = 0;
	std::string accountName = "Guest";
	std::string APIkey = "";

};

