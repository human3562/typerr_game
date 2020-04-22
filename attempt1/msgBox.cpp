#include "msgBox.h"

MsgBox::MsgBox(std::string content, float showtime){
	this->content = content;
	this->showtime = showtime;
}

void MsgBox::update(float fElapsedTime){
	if (time > showtime) {
		targetPosX = -textWidth;
		if (positionX < 190) finished = true;
	}
	else {
		targetPosX = 0;
	}
	positionX = SmoothApproach(positionX, targetPosX, targetPosX, 10.f, fElapsedTime);
	time += fElapsedTime;
}

void MsgBox::show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime){
	sfText->setString(content);
	sfText->setCharacterSize(20);
	sfText->setPosition(positionX, 200);
	textWidth = sfText->getLocalBounds().width;
	window->draw(*sfText);
}

float MsgBox::SmoothApproach(float pastPosition, float pastTargetPosition, float targetPosition, float speed, float deltaTime){
	float t = deltaTime * speed;
	float v = (targetPosition - pastTargetPosition) / t;
	float f = pastPosition - pastTargetPosition + v;
	return targetPosition - v + f * expf(-t);
}