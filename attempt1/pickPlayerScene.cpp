#include "pickPlayerScene.h"

void PickPlayerScene::Start(sf::RenderWindow* window, NetworkManager* nM){
	isStarted = true;
	back = false;
	switchScene = false;

	if (!font.loadFromFile("resources/font2.ttf")) {
		//bad
	}

	mainText.setFont(font);
	mainText.setStyle(sf::Text::Regular);

	nM->whosonline();
	players = nM->onlinePlayers;
}

void PickPlayerScene::Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime){
	if (!nM->onlinePlayers.empty()) {
		int count = 0;
		selectedPlayer = -1;
		for (int i = 0; i < players.size(); i++) {
			mainText.setCharacterSize(40);
			if (players[i].id == nM->id) continue;

			mainText.setString(players[i].name);
			mainText.setPosition(10, 40 + 40 * count);
			
			sf::CircleShape shape;
			shape.setPosition(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
			shape.setFillColor(sf::Color::White);
			shape.setRadius(10);

			window->draw(shape);

			if (mainText.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)) {
				mainText.setCharacterSize(50);
				selectedPlayer = players[i].id;
				selectedname = players[i].name;
			}

			window->draw(mainText);
			count++;
		}
	}
	else {
		mainText.setCharacterSize(60);
		mainText.setString(L"Как здесь пусто...");
		mainText.setPosition((window->getSize().x / 2.f) - mainText.getLocalBounds().width/2.f, window->getSize().y / 2.f);
		window->draw(mainText);
	}
}

void PickPlayerScene::EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm){
	if (event->type == sf::Event::KeyPressed) {
		if (event->key.code == sf::Keyboard::Escape) {
			switchScene = true;
			back = true;
		}
	}
	if (event->type == sf::Event::MouseButtonPressed) {
		if (event->mouseButton.button == sf::Mouse::Left && selectedPlayer >= 0) {
			std::cout << selectedPlayer << std::endl;
			nM->duelRequest(selectedPlayer);
			nM->opponentname = selectedname;
			nM->who = selectedPlayer;
			switchScene = true;
			back = true;
		}
	}
}

e_gameState PickPlayerScene::switchSceneEvent(){
	isStarted = false;
	if (back) {
		return MENU;
	}
	//return e_gameState();
}
