#include "mainMenuScene.h"
#include "SFML/Graphics.hpp"


void MainMenuScene::Start(sf::RenderWindow* window, NetworkManager* nM){

	isStarted = true;

	switchScene = false;
	startSelected = false;
	optionsSelected = false;
	profileSelected = false;

	startMenu[0].typedText = L"";
	startMenu[1].typedText = L"";
	startMenu[2].typedText = L"";
	startMenu[3].typedText = L"";

	if (!font.loadFromFile("resources/font2.ttf")) {
		//bad
	}

	mainText.setFont(font);
	mainText.setStyle(sf::Text::Regular);

	secondaryText.setFont(font);
	secondaryText.setStyle(sf::Text::Regular);

	uiPositions[0] = window->getSize().x - 200.0f;
	uiPositions[1] = window->getSize().x - 200.0f;
	uiPositions[2] = window->getSize().x - 130.0f;
	uiPositions[3] = 70.0f;

	startMenu[0].positionX = window->getSize().x + 200.0f;
	startMenu[0].positionY = (window->getSize().y / 2.0f) - 60.0f;

	startMenu[1].positionX = window->getSize().x + 200.0f;
	startMenu[1].positionY = (window->getSize().y/2.0f) + 50.0f;

	startMenu[2].positionX = window->getSize().x + 130.0f;
	startMenu[2].positionY = (window->getSize().y / 2.0f) + 140.0f;

	startMenu[3].maxAddRot = 2.0f;
	startMenu[3].maxAddSize = 3.0f;
	startMenu[3].positionX = window->getSize().x - 120.0f;
	startMenu[3].positionY = -200.0f;

}

void MainMenuScene::Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime) {
	window->clear(sf::Color(50, 50, 50));

	//draw (wow)

	for (int i = 0; i < 3; i++) {
		//startMenu[i].positionX = lerp(startMenu[i].positionX, uiPositions[i], fElapsedTime * 15.0f);
		startMenu[i].positionX = SmoothApproach(startMenu[i].positionX, uiPositions[i], uiPositions[i], 10.0f, fElapsedTime);
		startMenu[i].show(window, &mainText, fElapsedTime);
	}

	//startMenu[3].positionY = lerp(startMenu[3].positionY, uiPositions[3], fElapsedTime * 15.0f);
	startMenu[3].positionY = SmoothApproach(startMenu[3].positionY, uiPositions[3], uiPositions[3], 10.0f, fElapsedTime);
	startMenu[3].show(window, &mainText, fElapsedTime);

	secondaryText.setString(nM->getAccountName());
	float nameWidth = secondaryText.getLocalBounds().width;

	secondaryText.setPosition(window->getSize().x - nameWidth - 20.0f, startMenu[3].positionY - 30.0f);
	window->draw(secondaryText);

	secondaryText.setString(test + L"\n" + std::to_wstring(startMenu[0].text[0]));
	secondaryText.setPosition(0, 0);
	window->draw(secondaryText);

	window->display();
}

void MainMenuScene::EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm) {

	if (event->type == sf::Event::Resized){
		Start(window, nM);
	}


	if (event->type == sf::Event::KeyPressed) {
		if (event->key.code == sf::Keyboard::Enter) {
			for (int i = 0; i < 4; i++) {
				if (startMenu[i].typedText != L"") startMenu[i].typedText = startMenu[i].text;
			}
		}
	}

	if (event->type == sf::Event::TextEntered) {
		wchar_t inputChar = static_cast<wchar_t>(event->text.unicode);
		//if (event->text.unicode == 13) inputChar = '\n';
		int atleastone = false;
		for (int i = 0; i < 4; i++) {
			if (startMenu[i].inputEvent(inputChar, sm)) {
				atleastone = true;
				for (int j = 0; j < 4; j++) {
					startMenu[j].isSelected = false;
				}
				startMenu[i].isSelected = true;
			}
		}
		if (!atleastone) sm->playError();
		if (startMenu[0].typedText == startMenu[0].text) {
			startSelected = true;
			switchScene = true;
			sm->playSuccess();
			sm->playTypeMusic();
		}
		if (startMenu[2].typedText == startMenu[2].text) window->close();
		if (startMenu[3].typedText == startMenu[3].text) {
			switchScene = true;
			profileSelected = true;
		}
	}
}

e_gameState MainMenuScene::switchSceneEvent() {
	isStarted = false;
	if (startSelected) {
		return PLAY;
	}
	if (profileSelected) {
		return PROFILE;
	}
}

float MainMenuScene::lerp(float a, float b, float f) {
	return a + f * (b - a);
}

float MainMenuScene::SmoothApproach(float pastPosition, float pastTargetPosition, float targetPosition, float speed, float deltaTime)
{
	float t = deltaTime * speed;
	float v = (targetPosition - pastTargetPosition) / t;
	float f = pastPosition - pastTargetPosition + v;
	return targetPosition - v + f * expf(-t);
}

