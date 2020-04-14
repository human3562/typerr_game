#include "inputText.h"

InputText::InputText(float x, float y, std::wstring textVal, float size) {
	positionX = x; positionY = y;
	text = textVal;
	fontSize = size;
}

InputText::InputText(float x, float y, std::wstring textVal, float size, float rot) {
	positionX = x; positionY = y;
	text = textVal;
	fontSize = size;
	rotation = rot;
}

InputText::InputText(float x, float y, std::wstring textVal, float size, bool anim) {
	positionX = x; positionY = y;
	text = textVal;
	fontSize = size;
	animate = anim;
}

bool InputText::inputEvent(wchar_t input, SoundMaster* sm) {
	if (input == L'\b') {
		if (!typedText.empty()) {
			typedText.erase(typedText.size() - 1, 1);
			sm->playBackspace();
			return true;
		}
	}else if (typedText + input == text.substr(0,typedText.size()+1)) {
		typedText += input;
		/*sound.setBuffer(keySounds[rand() % 4]);
		sound.setVolume(30);
		sound.play();*/
		sm->playKey();
		return true;
	}
	return false;
}

void InputText::show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime) {
	if (!isSelected) typedText = L"";
	float currentFontSize = fontSize;
	float currentRotation = rotation;
	if (animate) {
		if (!typedText.empty()) {
			if (animatedFontSize < maxAddSize)
				animatedFontSize += animSpeed * fElapsedTime;
			else if (animatedFontSize > maxAddSize) animatedFontSize = maxAddSize;
		}
		else {
			if (animatedFontSize > 0) animatedFontSize -= animSpeed * fElapsedTime;
			else if (animatedFontSize < 0) animatedFontSize = 0;
		}
		currentFontSize += animatedFontSize;

		if (!typedText.empty()) {
			if (animatedRotation < maxAddRot)
				animatedRotation += animSpeed / 2.0f * fElapsedTime;
			else if (animatedRotation > maxAddRot) animatedRotation = maxAddRot;
		}
		else {
			if (animatedRotation > 0) animatedRotation -= animSpeed / 2.0f * fElapsedTime;
			else if (animatedRotation < 0) animatedRotation = 0;
		}
		currentRotation += animatedRotation;
	}

	sfText->setStyle(sf::Text::Regular);
	sfText->setFillColor(sf::Color(200, 200, 200));
	sfText->setString(text);
	sfText->setCharacterSize(currentFontSize);
	sfText->setRotation(currentRotation);
	if (centered) {
		float centeredX = positionX - sfText->getLocalBounds().width / 2.0f;
		sfText->setPosition(centeredX, positionY);
	}
	else {
		sfText->setPosition(positionX, positionY);
	}
	window->draw(*sfText);
	sfText->setFillColor(sf::Color(0, 150, 0));
	sfText->setStyle(sf::Text::Underlined);
	sfText->setString(typedText);
	window->draw(*sfText);
}