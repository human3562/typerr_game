#include "mainMenuScene.h"
#include "SFML/Graphics.hpp"


void MainMenuScene::Start(sf::RenderWindow* window, NetworkManager* nM){

	isStarted = true;

	switchScene = false;
	startSelected = false;
	optionsSelected = false;
	profileSelected = false;
	onlineSelected = false;
	duelintent = false;

	nM->gotoduel = false;
	nM->opponentReady = false;
	nM->opponentResult = false;

	startMenu[0].typedText = L"";
	startMenu[1].typedText = L"";
	startMenu[2].typedText = L"";
	startMenu[3].typedText = L"";
	startMenu[4].typedText = L"";
	startMenu[5].typedText = L"";
	startMenu[6].typedText = L"";
	startMenu[7].typedText = L"";

	if (!loaded) {
		if (!typewriter.loadFromFile("resources/textures/typetable.png")) {
			//bad...
		}

		if (!paper.loadFromFile("resources/textures/paper.png")) {
			//bad...
		}

		if (!font.loadFromFile("resources/font2.ttf")) {
			//bad
		}
		
		if (!font2.loadFromFile("resources/font.ttf")) {
			//bad
		}
	}
	loaded = true;

	mainText.setFont(font);
	mainText.setStyle(sf::Text::Regular);

	secondaryText.setFont(font);
	secondaryText.setStyle(sf::Text::Regular);
	secondaryText.setFillColor(sf::Color(200, 200, 200));

	uiPositions[0] = 70.0f;
	uiPositions[1] = window->getSize().x - 200.0f;
	uiPositions[2] = window->getSize().x + 200.0f;
	uiPositions[3] = window->getSize().x + 200.0f;
	uiPositions[4] = window->getSize().x - 200.0f;
	uiPositions[5] = window->getSize().x - 130.0f;
	uiPositions[6] = 120.f;
	uiPositions[7] = 300.f;


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

	startMenu[6].maxAddRot = 0.6;

}


void MainMenuScene::Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime) {

	//window->clear(sf::Color(50, 50, 50));
	if (nM->gotoduel) {
		switchScene = true;
		duelintent = true;
	}
	if (!nM->messages.empty()) {
		if (nM->messages[0].request) {
			uiPositions[6] = 120.f;
			uiPositions[7] = 300.f;
		}
		else {
			uiPositions[6] = -120.f;
			uiPositions[7] = -300.f;
			nM->activeRequest = false;
		}
	}
	else {
		uiPositions[6] = -120.f;
		uiPositions[7] = -300.f;
		nM->activeRequest = false;
	}
	sf::Sprite bg;
	bg.setTexture(typewriter);
	//outline.setTextureRect(sf::IntRect(0, 0, 320, 180));
	//outline.setColor(sf::Color(180, 0, 0));
	//outline.setScale(0.5f, 0.5f);
	//outline.setOutlineColor(sf::Color(200, 10, 10));
	//outline.setFillColor(sf::Color(40, 40, 40));
	//outline.setOutlineThickness(3);
	bg.setPosition((window->getSize().x/2.f)-960, (window->getSize().y/2.f)-540);
	//outline.setPosition(-120, (window->getSize().y/2.f) - 170.0f);
	window->draw(bg);


	sf::Sprite bottom;
	bottom.setTexture(paper);
	bottom.setScale(1.f, 1.f);
	//bottom.setRotation(-3.f);
	bottom.setColor(sf::Color(220, 220, 220));
	bottom.setPosition((window->getSize().x/2.f)-paper.getSize().x/2.f, (window->getSize().y - 400));
	window->draw(bottom);

	//draw (wow)
	startMenu[0].positionY = SmoothApproach(startMenu[0].positionY, uiPositions[0], uiPositions[0], 10.0f, fElapsedTime);
	startMenu[0].show(window, &mainText, fElapsedTime);

	secondaryText.setFillColor(sf::Color(200, 200, 200));
	secondaryText.setString(nM->getAccountName());
	secondaryText.setCharacterSize(30);
	secondaryText.setRotation(0);
	float nameWidth = secondaryText.getLocalBounds().width;
	
	secondaryText.setPosition(window->getSize().x - nameWidth - 20.0f, startMenu[0].positionY - 45.0f);
	window->draw(secondaryText);

	if (nM->isLoggedIn()) {

		secondaryText.setString(L"WPM: " + std::to_wstring(nM->getWPM()));
		nameWidth = secondaryText.getLocalBounds().width;
		secondaryText.setPosition(window->getSize().x - nameWidth - 20.0f, startMenu[0].positionY - 20.0f);
		window->draw(secondaryText);
	}


	secondaryText.setString("//Typerr");
	secondaryText.setPosition(0, 150);
	secondaryText.setCharacterSize(150);
	secondaryText.setRotation(-4.f);
	window->draw(secondaryText);

	secondaryText.setString(L"Начните печатать то, куда хотите перейти. \nОбращайте внимание на слова, начинающиеся с большой буквы. \nДописывать слова до конца не обязательно.");
	secondaryText.setPosition(0, window->getSize().y - 60);
	secondaryText.setCharacterSize(20);
	secondaryText.setFillColor(sf::Color(50, 50, 50));
	secondaryText.setRotation(-1.f);
	window->draw(secondaryText);


	for (int i = 1; i < 8; i++) {
		//startMenu[i].positionX = lerp(startMenu[i].positionX, uiPositions[i], fElapsedTime * 15.0f);
		startMenu[i].positionX = SmoothApproach(startMenu[i].positionX, uiPositions[i], uiPositions[i], 10.0f, fElapsedTime);
		startMenu[i].show(window, &mainText, fElapsedTime);
	}

	//window->display();
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
			for (int i = 0; i < 8; i++) {
				if (startMenu[i].typedText != L"") startMenu[i].typedText = startMenu[i].text;
			}
		}
		//if (event->key.code == sf::Keyboard::Space) {
		//	nM->getWords(0, 0);
		//}
	}

	if (event->type == sf::Event::TextEntered) {
		wchar_t inputChar = static_cast<wchar_t>(event->text.unicode);
		//if (event->text.unicode == 13) inputChar = '\n';
		int atleastone = false;
		for (int i = 0; i < (nM->activeRequest? 8 : 6); i++) {

			if (inputChar == L'\b') {
				startMenu[i].inputEvent(inputChar, sm);
				continue;
			}
			//startMenu[i].isSelected = true;
			if ((i == 2 || i == 3) && startMenu[1].typedText != startMenu[1].text) continue;
			if (startMenu[i].belongs(inputChar, sm)) {
				atleastone = true;
				for (int j = 0; j < 8; j++) {
					//if (j == i) continue;
					if (i == 2 || i == 3) {
						if (j == 1) continue;
					}
					startMenu[j].isSelected = false;
					if (startMenu[j].belongs(inputChar, sm)) {
						if (startMenu[j].typedText.length() > startMenu[i].typedText.length()) {
							startMenu[i].isSelected = false;
							startMenu[j].isSelected = true;
							startMenu[j].inputEvent(inputChar, sm);
							//break;
						}
						else {
							startMenu[i].isSelected = true;
							startMenu[i].inputEvent(inputChar, sm);
							startMenu[j].isSelected = false;
							//break;
						}
					}
					//startMenu[j].isSelected = false;
				}
				startMenu[i].isSelected = true;
				break;
			}
		}
		if (!atleastone) {
			sm->playError();
		}
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
			sm->playSuccess();
		}
		if (startMenu[2].typedText == startMenu[2].text) {
			startSelected = true;
			switchScene = true;
			sm->playSuccess();
		}
		if (startMenu[6].typedText == startMenu[6].text) {
			if (nM->activeRequest) {
				while(!nM->acceptRequest(nM->messages[0].who));
			}
		}
		if (startMenu[7].typedText == startMenu[7].text) {
			if (nM->activeRequest) {
				if (!nM->messages.empty()) {
					nM->messages[0].finished = true;
				}
			}
		}
		if (startMenu[3].typedText == startMenu[3].text) {
			if (nM->isLoggedIn()){
				onlineSelected = true;
				switchScene = true;
				sm->playSuccess();
			}
			else {
				sm->playError();
			}
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
	if (onlineSelected) {
		return PLAYER_PICK;
	}
	if (duelintent) {
		return DUEL_PLAY;
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

