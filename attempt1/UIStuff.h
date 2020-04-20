#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "soundMaster.h"

class Setting {
public:
	Setting() {}
	~Setting() {}

public:
	virtual void Show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime) {}
	virtual void EventHandle(sf::RenderWindow* window, sf::Event* event, SoundMaster* sm) {}

public:
	float positionX = 0.0f, positionY = 0.0f;
	bool active = true;
	bool act = false;
	int value = 0;
	std::wstring input = L"";
	bool isSelected = false;
	//std::wstring name =
	//bool mOver = false;
};

class ButtonSetting : public Setting {
public:
	ButtonSetting(float positionX, float positionY, std::wstring title);
	ButtonSetting(float positionX, float positionY, std::wstring title, float rotation);
	~ButtonSetting() {}

public:
	void Show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime) override;
	void EventHandle(sf::RenderWindow* window, sf::Event* event, SoundMaster* sm) override;

private:
	float rotation = 0.0f;
	std::wstring title = L"";
};

class TextSetting : public Setting {
public:
	TextSetting(float positionX, float positionY, std::wstring placeholder, bool isPassword);
	~TextSetting() {}

public:
	void Show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime) override;
	void EventHandle(sf::RenderWindow* window, sf::Event* event, SoundMaster* sm) override;
	bool isPassword = false;

private:
	float timer = 0.f;
	std::wstring placeholder = L"";
	sf::Texture t_selection;
};

class UIStuff
{
public:
	UIStuff() {}
	~UIStuff() {}

public:
	std::vector<Setting*> settings;
	int selected = 0;

public:
	void Show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime);
	void EventHandle(sf::RenderWindow* window, sf::Event* event, SoundMaster* sm);
};