#include "UIStuff.h"

void UIStuff::Show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime){
	if (!settings.empty()) {
		for (Setting* s : settings) s->isSelected = false;
		settings[selected]->isSelected = true;
		for (Setting* s : settings) s->Show(window, sfText, fElapsedTime);
	}
}

void UIStuff::EventHandle(sf::RenderWindow* window, sf::Event* event, SoundMaster* sm){
	if (event->type == sf::Event::Closed) window->close();

	if (event->type == sf::Event::KeyPressed) {
		if (!settings.empty()) {
			if (event->key.code == sf::Keyboard::Up && selected > 0) {
				selected--;
			}
			else if ((event->key.code == sf::Keyboard::Down) && selected < settings.size() - 1) {
				selected++;
			}
			else {
				settings[selected]->EventHandle(window, event, sm);
			}
		}
	}else if (event->type == sf::Event::TextEntered) {
		if (!settings.empty()) {
			settings[selected]->EventHandle(window, event, sm);
		}
	}


}

TextSetting::TextSetting(float positionX, float positionY, std::wstring placeholder, bool isPassword){
	this->positionX = positionX; this->positionY = positionY;
	this->placeholder = placeholder;
	this->isPassword = isPassword;
	if (!t_selection.loadFromFile("resources/textures/settingSelection.png")) {
		//bad...
	}
}

void TextSetting::Show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime){
	if (isSelected) {
		timer += fElapsedTime;
		sf::Sprite outline;
		outline.setTexture(t_selection);
		outline.setColor(sf::Color(180, 0, 0));
		//outline.setTextureRect(sf::IntRect(positionX, positionY, 400, 40));
		//outline.setOutlineColor(sf::Color(200, 10, 10));
		//outline.setFillColor(sf::Color(40, 40, 40));
		//outline.setOutlineThickness(3);
		outline.setPosition(positionX-3.0f, positionY);
		window->draw(outline);
	}
	else timer = 0;
	if (input.empty()) {
		sfText->setPosition(positionX + 3.f, positionY);
		sfText->setString(placeholder);
		sfText->setFillColor(sf::Color(100,100,100));
		window->draw(*sfText);
	}
	else {
		sfText->setPosition(positionX + 3.f, positionY);
		if (isPassword) {
			std::wstring str = L"";
			for (int i = 0; i < input.size(); i++) {
				str += L"•";
			}
			sfText->setString(str + ((int)timer % 2 == 1 ? L"|" : L""));
		}
		else {
			sfText->setString(input + ((int)timer % 2 == 1 ? L"|" : L""));
		}
		sfText->setFillColor(sf::Color(200, 200, 200));
		window->draw(*sfText);
	}
}

void TextSetting::EventHandle(sf::RenderWindow* window, sf::Event* event, SoundMaster* sm){
	if (event->type == sf::Event::TextEntered) {
		wchar_t inputChar = static_cast<wchar_t>(event->text.unicode);
		std::wstring reg = L"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
		if (event->text.unicode == 13 || event->text.unicode == 27) return;
		if (inputChar == L'\b') {
			if (!input.empty()) {
				input.erase(input.size() - 1, 1);
				sm->playBackspace();
			}
		}
		else {
			if (reg.find(inputChar) != std::wstring::npos) {
				input += inputChar;
				sm->playKey();
			}else sm->playError();
		}
	}
}

ButtonSetting::ButtonSetting(float positionX, float positionY, std::wstring title){
	this->positionX = positionX; this->positionY = positionY;
	this->title = title;
}

ButtonSetting::ButtonSetting(float positionX, float positionY, std::wstring title, float rotation) {
	this->positionX = positionX; this->positionY = positionY;
	this->title = title;
	this->rotation = rotation;
}

void ButtonSetting::Show(sf::RenderWindow* window, sf::Text* sfText, float fElapsedTime)
{
	sfText->setPosition(positionX, positionY);
	sfText->setRotation(rotation);
	sfText->setString(title);
	sfText->setFillColor(sf::Color(200, 200, 200));
	sfText->setCharacterSize(100);

	if (!isSelected) {
		sfText->setStyle(sf::Text::Regular);
	}
	else {
		sfText->setStyle(sf::Text::Underlined);
	}

	window->draw(*sfText);
}

void ButtonSetting::EventHandle(sf::RenderWindow* window, sf::Event* event, SoundMaster* sm)
{
	if (event->text.unicode == 13) {
		act = true;
	}
}
