#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "soundMaster.h"


class InputText { //this is for typing in specific words
public:
	std::wstring text;
	std::wstring typedText = L"";
	float positionX; float positionY;
	float rotation = 0.0f;
	float maxAddSize = 10.0f; float maxAddRot = 4.0f;
	float fontSize;
	bool isSelected = false;
	bool centered = true;

private:
	float animatedFontSize = 0.0f;
	float animatedRotation = 0.0f;
	float animSpeed = 300.0f;
	bool animate = true;

public:
	void show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime);
	bool inputEvent(wchar_t input, SoundMaster* sm);
	InputText(float x, float y, std::wstring text, float size);
	InputText(float x, float y, std::wstring text, float size, float rot);
	InputText(float x, float y, std::wstring text, float size, bool anim);

};

