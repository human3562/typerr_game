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
	startMenu[4].typedText = L"";
	startMenu[5].typedText = L"";

	if (!typewriter.loadFromFile("resources/textures/typetable.png")) {
		//bad...
	}

	if (!font.loadFromFile("resources/font2.ttf")) {
		//bad
	}

	mainText.setFont(font);
	mainText.setStyle(sf::Text::Regular);

	secondaryText.setFont(font);
	secondaryText.setStyle(sf::Text::Regular);

	uiPositions[1] = window->getSize().x - 200.0f;
	uiPositions[4] = window->getSize().x - 200.0f;
	uiPositions[5] = window->getSize().x - 130.0f;
	uiPositions[0] = 70.0f;
	uiPositions[2] = window->getSize().x + 200.0f;
	uiPositions[3] = window->getSize().x + 200.0f;


	startMenu[1].positionX = window->getSize().x + 200.0f;
	startMenu[1].positionY = (window->getSize().y / 2.0f) - 60.0f;

	startMenu[4].positionX = window->getSize().x + 200.0f;
	startMenu[4].positionY = (window->getSize().y/2.0f) + 50.0f;

	startMenu[5].positionX = window->getSize().x + 130.0f;
	startMenu[5].positionY = (window->getSize().y / 2.0f) + 140.0f;

	startMenu[0].maxAddRot = 2.0f;
	startMenu[0].maxAddSize = 3.0f;
	startMenu[0].positionX = window->getSize().x - 120.0f;
	startMenu[0].positionY = -200.0f;

	startMenu[2].positionX = window->getSize().x + 200.0f;
	startMenu[2].positionY = (window->getSize().y / 2.0f) - 90.0f;
	startMenu[2].centered = false;
	startMenu[2].maxAddSize = 3.0f;

	startMenu[3].positionX = window->getSize().x + 200.0f;
	startMenu[3].positionY = (window->getSize().y / 2.0f) - 30.0f;
	startMenu[3].centered = false;
}


void MainMenuScene::Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime) {

	window->clear(sf::Color(50, 50, 50));

	sf::Sprite outline;
	outline.setTexture(typewriter);
	//outline.setTextureRect(sf::IntRect(0, 0, 320, 180));
	//outline.setColor(sf::Color(180, 0, 0));
	//outline.setScale(0.5f, 0.5f);
	//outline.setOutlineColor(sf::Color(200, 10, 10));
	//outline.setFillColor(sf::Color(40, 40, 40));
	//outline.setOutlineThickness(3);
	outline.setPosition((window->getSize().x/2.f)-960, (window->getSize().y/2.f)-540);
	//outline.setPosition(-120, (window->getSize().y/2.f) - 170.0f);
	window->draw(outline);

	//draw (wow)
	startMenu[0].positionY = SmoothApproach(startMenu[0].positionY, uiPositions[0], uiPositions[0], 10.0f, fElapsedTime);
	startMenu[0].show(window, &mainText, fElapsedTime);

	secondaryText.setString(nM->getAccountName());
	float nameWidth = secondaryText.getLocalBounds().width;

	secondaryText.setPosition(window->getSize().x - nameWidth - 20.0f, startMenu[0].positionY - 45.0f);
	window->draw(secondaryText);

	if (nM->isLoggedIn()) {

		secondaryText.setString(L"WPM: " + std::to_wstring(nM->getWPM()));
		nameWidth = secondaryText.getLocalBounds().width;
		secondaryText.setPosition(window->getSize().x - nameWidth - 20.0f, startMenu[0].positionY - 20.0f);
		window->draw(secondaryText);
	}


	secondaryText.setString(test + L"\n" + std::to_wstring(startMenu[0].text[0]));
	secondaryText.setPosition(0, 0);
	window->draw(secondaryText);


	for (int i = 1; i < 6; i++) {
		//startMenu[i].positionX = lerp(startMenu[i].positionX, uiPositions[i], fElapsedTime * 15.0f);
		startMenu[i].positionX = SmoothApproach(startMenu[i].positionX, uiPositions[i], uiPositions[i], 10.0f, fElapsedTime);
		startMenu[i].show(window, &mainText, fElapsedTime);
	}

	window->display();
}

void MainMenuScene::EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm) {

	if (event->type == sf::Event::Resized){
		//Start(window, nM);
		uiPositions[1] = window->getSize().x - 200.0f;
		uiPositions[4] = window->getSize().x - 200.0f;
		uiPositions[5] = window->getSize().x - 130.0f;
		uiPositions[0] = 70.0f;
		uiPositions[2] = window->getSize().x + 200.0f;
		uiPositions[3] = window->getSize().x + 200.0f;

		//startMenu[1].positionX = window->getSize().x + 200.0f;
		startMenu[1].positionY = (window->getSize().y / 2.0f) - 60.0f;

		//startMenu[4].positionX = window->getSize().x + 200.0f;
		startMenu[4].positionY = (window->getSize().y / 2.0f) + 50.0f;

		//startMenu[5].positionX = window->getSize().x + 130.0f;
		startMenu[5].positionY = (window->getSize().y / 2.0f) + 140.0f;

		//startMenu[0].maxAddRot = 2.0f;
		//startMenu[0].maxAddSize = 3.0f;
		startMenu[0].positionX = window->getSize().x - 120.0f;
		//startMenu[0].positionY = -200.0f;

		//startMenu[2].positionX = window->getSize().x + 200.0f;
		startMenu[2].positionY = (window->getSize().y / 2.0f) - 90.0f;
		//startMenu[2].centered = false;
		//startMenu[2].maxAddSize = 3.0f;

		//startMenu[3].positionX = window->getSize().x + 200.0f;
		startMenu[3].positionY = (window->getSize().y / 2.0f) - 30.0f;
		//startMenu[3].centered = false;

		return;
	}


	if (event->type == sf::Event::KeyPressed) {
		if (event->key.code == sf::Keyboard::Enter) {
			for (int i = 0; i < 6; i++) {
				if (startMenu[i].typedText != L"") startMenu[i].typedText = startMenu[i].text;
			}
		}
	}

	if (event->type == sf::Event::TextEntered) {
		wchar_t inputChar = static_cast<wchar_t>(event->text.unicode);
		//if (event->text.unicode == 13) inputChar = '\n';
		int atleastone = false;
		for (int i = 0; i < 6; i++) {
			if ((i == 2 || i == 3) && startMenu[1].typedText != startMenu[1].text) continue;
			if (startMenu[i].inputEvent(inputChar, sm)) {
				atleastone = true;
				for (int j = 0; j < 6; j++) {
					if (i == 2 || i == 3) {
						if (j == 1) continue;
					}
					startMenu[j].isSelected = false;
				}
				startMenu[i].isSelected = true;
				break;
			}
		}
		if (!atleastone) sm->playError();
		/*if (startMenu[0].typedText == startMenu[0].text) {
			startSelected = true;
			switchScene = true;
			sm->playSuccess();
			sm->playTypeMusic();
		}*/
		if (startMenu[1].typedText == startMenu[1].text) {
			uiPositions[1] = window->getSize().x - 500.0f;
			uiPositions[2] = window->getSize().x - 320.0f;
			uiPositions[3] = window->getSize().x - 320.0f;
		}
		else {
			uiPositions[1] = window->getSize().x - 200.0f;
			uiPositions[2] = window->getSize().x + 200.0f;
			uiPositions[3] = window->getSize().x + 200.0f;
		}
		if (startMenu[5].typedText == startMenu[5].text) window->close();
		if (startMenu[0].typedText == startMenu[0].text) {
			switchScene = true;
			profileSelected = true;
		}
		if (startMenu[2].typedText == startMenu[2].text) {
			startSelected = true;
			switchScene = true;
			sm->playSuccess();
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

