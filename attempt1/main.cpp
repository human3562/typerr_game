#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "mainMenuScene.h"
#include "playScene.h"
#include "gameState.h"
#include "soundMaster.h"
#include "profileScene.h"
#include "networkManager.h"
#include "pickPlayerScene.h"
#include "duelPlayScene.h"

int main() {
	//setlocale(LC_ALL, "Russian");
	srand(unsigned(time(0)));

	sf::Image icon;
	icon.loadFromFile("resources/textures/typewritericon.png");

	float fElapsedTime = 0.001f;
	e_gameState currentGameState = MENU;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(1024, 768), "jeesus", sf::Style::Default, settings);

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	//window.setFramerateLimit(300);

	window.setKeyRepeatEnabled(false); //no spam   >:(

	NetworkManager nM;
	SoundMaster sm;

	sf::Text mainText;
	sf::Font font;

	if (!font.loadFromFile("resources/font2.ttf")) {
		//bad
	}

	mainText.setFont(font);
	mainText.setStyle(sf::Text::Regular);

	nM.mainText = mainText;

	GameScene* scenes[6];
	ProfileScene s_profile;
	MainMenuScene s_mainmenu;
	ResultScene s_result;
	PickPlayerScene s_pickplayer;
	DuelPlayScene s_duelplay;

	PlayScene s_play;
	s_play.loadText();
	s_play.setResultScenePointer(&s_result); //to pass stats n shit to the result scene

	scenes[MENU] =	  &s_mainmenu;
	scenes[PLAY] =    &s_play;
	scenes[PROFILE] = &s_profile;
	scenes[RESULT] =  &s_result;
	scenes[PLAYER_PICK] = &s_pickplayer;
	scenes[DUEL_PLAY] = &s_duelplay;

	while (window.isOpen()) {

		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (scenes[currentGameState]->isStarted) scenes[currentGameState]->EventHandle(&window, &event, &nM, &sm);

			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

		}
		window.clear(sf::Color(50, 50, 50));

		if (!scenes[currentGameState]->isStarted) {
			scenes[currentGameState]->Start(&window, &nM);
		}
		else {

			if (scenes[currentGameState]->switchScene)
				currentGameState = scenes[currentGameState]->switchSceneEvent();
			else
				scenes[currentGameState]->Update(&window, &nM, fElapsedTime);
			//if (scenes[currentGameState]->switchScene) currentGameState = scenes[currentGameState]->switchSceneEvent();

			if (nM.isLoggedIn()) {
				if (!nM.polling) {
					nM.startPolling();
				}
				nM.drawServerMessages(&window, fElapsedTime);
			}

		}
		window.display();
		
		//window.setTitle("FPS: " + std::to_string(1.0f / fElapsedTime));
		
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		fElapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1e+9;

	}

	return 0;
}