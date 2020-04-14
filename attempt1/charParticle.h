#pragma once
#include "SFML/Graphics.hpp"
class CharParticle
{
public:
	CharParticle(float xpos, float ypos, wchar_t c);
	~CharParticle() {}

public:
	void update(float fElapsedTime);
	void show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime);

private:
	float x, y;
	float speedX, speedY;
	wchar_t character;
	float timer = 0.0f;
	float angle = 0.0f;
	float aspeed;
public:
	bool finished = false;
};

