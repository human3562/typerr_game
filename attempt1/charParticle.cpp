#include "charParticle.h"
#include <random>
const float part_lifetime = 2.0f;
CharParticle::CharParticle(float xpos, float ypos, wchar_t c) {
	x = xpos; y = ypos; character = c;
	float a = (rand() % 314) * 0.01f;
	speedX = cosf(a) * (rand() % 355) + 5;
	speedY = sinf(a) * (rand() % 355) + 5;
	aspeed = ((rand() % 628) - 314) * 0.01f;
}

void CharParticle::update(float fElapsedTime) {
	timer += fElapsedTime;
	speedY += 500.0f * fElapsedTime;
	x += speedX * fElapsedTime;
	y += speedY * fElapsedTime;
	angle += aspeed * fElapsedTime;
	if (timer > part_lifetime) finished = true;
}

void CharParticle::show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime) {
	sfText->setStyle(sf::Text::Regular);
	sfText->setFillColor(sf::Color(0, 150, 0));
	sfText->setString(character);
	sfText->setCharacterSize(32);
	sfText->setPosition(x, y);
	sfText->setRotation(angle * (180.0f / 3.1415926535f));
	window->draw(*sfText);
}



/*
INSERT INTO `wordtable`(`content`) VALUES (" ");
INSERT INTO `wordtable`(`content`) VALUES (" ");
INSERT INTO `wordtable`(`content`) VALUES (" ");
INSERT INTO `wordtable`(`content`) VALUES (" ");
*/