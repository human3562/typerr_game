#pragma once
#include "gameScene.h"

class PickPlayerScene : public GameScene
{
public:
	PickPlayerScene() {}
	~PickPlayerScene() {}

public:
	void Start(sf::RenderWindow* window, NetworkManager* nM) override;
	void Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime) override;
	void EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm) override;
	e_gameState switchSceneEvent() override;

public:
	std::vector<player> players;

private:
	sf::Text mainText;
	sf::Font font;
	bool back = false;
	int selectedPlayer = -1;

};

