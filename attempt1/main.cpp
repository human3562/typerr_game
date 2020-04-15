#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "mainMenuScene.h"
#include "playScene.h"
#include "gameState.h"
#include "soundMaster.h"
#include "profileScene.h"
#include "networkManager.h"

int main() {
	srand(unsigned(time(0)));

	float fElapsedTime = 0.001f;
	e_gameState currentGameState = MENU;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(1024, 768), "jeesus", sf::Style::Default, settings);

	//window.setFramerateLimit(70);

	window.setKeyRepeatEnabled(false); //no spam   >:(

	NetworkManager nM;
	SoundMaster sm;

	GameScene* scenes[4];
	ProfileScene s_profile;
	MainMenuScene s_mainmenu;
	ResultScene s_result;

	PlayScene s_play;
	s_play.loadText();
	s_play.setResultScenePointer(&s_result); //to pass stats n shit to the result scene

	scenes[MENU] =	  &s_mainmenu;
	scenes[PLAY] =    &s_play;
	scenes[PROFILE] = &s_profile;
	scenes[RESULT] =  &s_result;

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

		if (!scenes[currentGameState]->isStarted) {
			scenes[currentGameState]->Start(&window, &nM);
		}
		else {
			if (scenes[currentGameState]->switchScene)
				currentGameState = scenes[currentGameState]->switchSceneEvent();
			else
				scenes[currentGameState]->Update(&window, &nM, fElapsedTime);
			//if (scenes[currentGameState]->switchScene) currentGameState = scenes[currentGameState]->switchSceneEvent();
		}

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		fElapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0f;
		window.setTitle("holy fuck the fps is " + std::to_string(1.0f / fElapsedTime));

	}

	return 0;
}