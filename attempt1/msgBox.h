#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
class MsgBox
{
public:
	MsgBox(std::string content, float showtime);
	~MsgBox() {}

public:
	void update(float fElapsedTime);
	void show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime);
	bool finished = false;

private:
	float SmoothApproach(float pastPosition, float pastTargetPosition, float targetPosition, float speed, float deltaTime);
	float time = 0;
	float showtime = 0;
	float textWidth = 100;
	std::string content;
	float positionX = -200;
	float targetPosX = 0;
};

