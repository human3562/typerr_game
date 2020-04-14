#pragma once
#include "gameScene.h"
#include "inputText.h"
class ResultScene : public GameScene
{
public:
	ResultScene() {}
	~ResultScene() {}

public:
	void Start(sf::RenderWindow* window, NetworkManager* nM) override;
	void Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime) override;
	void EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm) override;
	e_gameState switchSceneEvent() override;

	void setupInfo(float time, int charAmt, float accuracy, int score);

private:
	std::wstring nf(float time); //formatting a float storing time in seconds into a Minute:Second:Millisecond format string

	//stats
	int WPM = 0;
	int accuracy = 0;
	float time = 0.0f;
	int totalScore = 0;
	
	//scene switch flags
	bool back = false;
	bool restart = false;

	sf::Text optText;
	sf::Text mainText;
	sf::Font font;
	sf::Font font2;

	InputText options[2] = {
		{0.0f, 240.0f, L"Ещё раз!\n", 70.0f, -7.0f},
		{0.0f, 350.0f, L"Назад\n", 50.0f, -6.0f},
	};
};

