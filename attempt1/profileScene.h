#pragma once
#include "gameScene.h"
#include "UIStuff.h"
class ProfileScene : public GameScene
{
public:
	ProfileScene() {}

public:
	void Start(sf::RenderWindow* window, NetworkManager* nM) override;
	void Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime) override;
	void EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm) override;
	e_gameState switchSceneEvent() override;

private:
	sf::Text mainText;
	sf::Font font;
	std::wstring errormessage = L"";
	bool back = false;
	bool loggedIn = false;
	UIStuff loginForm;
	TextSetting t1 = { 0.0f, 0.0f, L"Ваш логин", false };
	TextSetting t2 = { 0.0f, 0.0f, L"Ваш пароль", true };
	ButtonSetting t3 = { 0.0f, 0.0f, L"Подтвердить", -10.0f };
};

