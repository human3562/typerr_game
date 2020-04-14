#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "gameState.h"
#include "soundMaster.h"
#include "networkManager.h"

class GameScene{
public:
	GameScene() {}

public:
	virtual void Start(sf::RenderWindow* window, NetworkManager* nM) {}
	virtual void Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime) {}
	virtual void EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm) {}
	virtual e_gameState switchSceneEvent() { return MENU; }

public:
	bool isStarted = false;
	bool switchScene = false;
};


