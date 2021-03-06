#pragma once
#include "gameScene.h"
#include "inputText.h"

class MainMenuScene : public GameScene
{
public:
	MainMenuScene() {}

public:
    void Start(sf::RenderWindow* window, NetworkManager* nM) override;
	void Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime) override;
	void EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm) override;
	e_gameState switchSceneEvent() override;
	float lerp(float a, float b, float f);
	float SmoothApproach(float pastPosition, float pastTargetPosition, float targetPosition, float speed, float deltaTime); //alternative for lerp

//private:
//	std::string login(std::string uid, std::string pwd);

private:
	InputText startMenu[8] = {
		{0.0f, -200.0f,L"�������\n", 50.0f, -0.7f },
		{0.0f, 240.0f, L"������\n", 70.0f, -7.0f},
		{0.0f, -200.0f,L"� ��������\n", 50.0f, -0.6f },
		{0.0f, -200.0f,L"������\n", 50.0f, -0.6f },
		{0.0f, 350.0f, L"���������\n", 50.0f, -6.0f},
		{0.0f, 440.0f, L"�����\n", 45.0f, -4.0f},
		{0.0f, 380.0f, L"�������\n", 45.0f, -4.0f},
		{0.0f, 410.0f, L"���������\n", 45.0f, 0.6f}
	};
	sf::Text mainText = {};
	sf::Text secondaryText;
	sf::Font font;
	sf::Font font2;
	std::wstring test = L"";
	bool startSelected = false;
	bool profileSelected = false;
	bool optionsSelected = false;
	bool onlineSelected = false;
	bool duelintent = false;
	float uiPositions[8] = {};

	bool loaded = false;

	sf::Texture typewriter;
	sf::Texture paper;

};

