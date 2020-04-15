#include "playScene.h"
#include "fstream"
#include <codecvt>
#include <string.h>
//#include <wchar.h>
#include <cstring> 

void PlayScene::Start(sf::RenderWindow* window, NetworkManager* nM)
{

	wordAmt = 10;
	charAmt = 0;
	time = 0.0f;
	multiplier = 0;
	score = 0;
	mistakes = 0;
	keyPresses = 0;

	part.clear();

	isStarted = true;
	back = false;
	switchScene = false;
	errorWhenLoading = false;

	time = 0;

	fScreenRotation = (rand() % 11) - 5.0f;

	playtext.clear();
	if (!font.loadFromFile("resources/font2.ttf")) {
		//bad
	}

	mainText.setFont(font);
	mainText.setStyle(sf::Text::Regular);

	/*for (int i = 0; i < 4; i++) {
		if (!keySounds[i].loadFromFile("resources/sounds/key" + std::to_string(i+1) + ".ogg")) {
			exit(1);
		}
	}*/
	charAmt = 0;
	if (!loaded) loadText();
	for (int i = 0; i < wordAmt; i++) {
		std::wstring line = text[rand() % text.size()];
		charAmt += line.length() + 1; //+1 for enter
		playtext.push_back({ 0.0f, -300.0f, line, 36, false });
	}
	playtext.push_back({ 0.0f, -300.0f, L"Начать!", 36, false });
}

void PlayScene::Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime)
{
	
	//window->clear(sf::Color(150, 150, 150));

	////draw

	//for (int i = 0; i < 3; i++) {
	//	startMenu[i].show(window, &mainText, fElapsedTime);
	//}

	//mainText.setString(test + L"\n" + std::to_wstring(startMenu[0].text[0]));
	//mainText.setPosition(0, 0);
	//window->draw(mainText);

	//window->display();
	window->clear(sf::Color(50, 50, 50));

	sf::RectangleShape rect(sf::Vector2f(window->getSize().x+100, 40));
	rect.setPosition(sf::Vector2f(-50, (window->getSize().y / 2.0f) + 5));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color(255, 255, 255));
	rect.setOutlineThickness(1.0f);

	sf::View view(sf::FloatRect(0.f, 0.f, window->getSize().x, window->getSize().y));
	view.setRotation(fScreenRotation);
	window->setView(view);
	window->draw(rect);

	for (int i = 0; i < playtext.size(); i++) {
		InputText* current = &playtext[playtext.size() - 1 - i];
		current->positionX = (window->getSize().x / 2.0f);
		float targetPos = (window->getSize().y / 2.0f) - 40.0f * i;
		//current->positionY = lerp(current->positionY, targetPos, fElapsedTime * 20.0f);
		current->positionY = SmoothApproach(current->positionY, targetPos, targetPos, 20.f, fElapsedTime);
		current->show(window, &mainText, fElapsedTime);
		//playtext[playtext.size() - 1 - i].show(window, &mainText, fElapsedTime);
		//std::wstring current = playtext[playtext.size() - 1 - i];

	}

	if (!part.empty()) {
		for (int i = 0; i < part.size(); i++) {
			part[i].update(fElapsedTime);
			part[i].show(window, &mainText, fElapsedTime);
		}
		for (int i = part.size() - 1; i >= 0; i--) {
			if (part[i].finished) part.erase(part.begin() + i);
		}
	}
	//view.setRotation(0.f);
	//window->setView(view);

	view.setRotation(-2.f);
	window->setView(view);

	sf::Text timerText;
	timerText.setFont(font);
	timerText.setCharacterSize(40);
	timerText.setString(nf(time));
	timerText.setPosition(window->getSize().x - 202, -18);
	window->draw(timerText);

	sf::RectangleShape progressBarBG(sf::Vector2f(window->getSize().x / 4, 12));
	progressBarBG.setFillColor(sf::Color(20, 20, 20));
	progressBarBG.setOutlineColor(sf::Color(20, 20, 20));
	progressBarBG.setPosition(window->getSize().x - (window->getSize().x/4)-20, 30);
	progressBarBG.setOutlineThickness(1);
	window->draw(progressBarBG);

	if (playtext.size() <= wordAmt) {
		sf::RectangleShape progressBar(sf::Vector2f((window->getSize().x / 4.0f) * ((wordAmt - playtext.size()) / (float)wordAmt), 12));
		progressBar.setFillColor(sf::Color(200, 200, 200));
		progressBar.setOutlineColor(sf::Color(20, 20, 20));
		progressBar.setPosition(window->getSize().x - (window->getSize().x / 4) - 20, 30);
		window->draw(progressBar);
	}

	sf::Text accuracyText;
	accuracyText.setFont(font);
	accuracyText.setCharacterSize(30);

	if (keyPresses == 0) accuracyText.setString("0%");
	else accuracyText.setString(std::to_string((int)(((keyPresses - mistakes) / (float)keyPresses)*100.f)) + "%");

	accuracyText.setPosition(window->getSize().x - accuracyText.getLocalBounds().width - 10, 44);
	window->draw(accuracyText);

	view.setRotation(0.f);
	window->setView(view);


	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(90);
	scoreText.setFillColor(sf::Color(200, 200, 200));
	scoreText.setString(std::to_string(score));
	scoreText.setPosition(window->getSize().x - scoreText.getLocalBounds().width - 10, window->getSize().y - 100);
	window->draw(scoreText);

	scoreText.setCharacterSize(60);
	scoreText.setString(std::to_string(multiplier) + "X");
	scoreText.setPosition(window->getSize().x - scoreText.getLocalBounds().width - 10, window->getSize().y - 130);
	window->draw(scoreText);
	
	sf::Text particleSize;
	particleSize.setFont(font);
	particleSize.setCharacterSize(15);
	particleSize.setPosition(0, 20);
	particleSize.setString(std::to_string(part.size()));

	window->draw(particleSize);

	window->display();
	if (playtext.size() <= wordAmt) {
		time += fElapsedTime;
	}
}

void PlayScene::EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm)
{
	if (event->type == sf::Event::Closed) window->close();

	if (event->type == sf::Event::KeyPressed) {
		if (event->key.code == sf::Keyboard::Escape) {
			switchScene = true;
			back = true;
			sm->stopTypeMusic();
		}
	}


	if (event->type == sf::Event::TextEntered && !playtext.empty()) {
		wchar_t inputChar = static_cast<wchar_t>(event->text.unicode);

		if (event->text.unicode == 13) {
			if (playtext[playtext.size() - 1].typedText == playtext[playtext.size() - 1].text) {

				if (playtext.size() <= wordAmt) score += playtext[playtext.size() - 1].text.length() * multiplier;
				else {
					sm->playTypeMusic();
				}

				pop(&playtext[playtext.size() - 1]);
				playtext.pop_back();
				sm->playSuccess();
				if (playtext.empty()) {
					finished = true;
					switchScene = true;
					sm->stopTypeMusic();
				}
			}
		}
		else {
			playtext[playtext.size() - 1].isSelected = true;
			if (!playtext[playtext.size() - 1].inputEvent(inputChar, sm)) {
				sm->playError();
				if (playtext.size() <= wordAmt) {
					mistakes++;
					keyPresses++;
					multiplier = 1;
				}
			}
			else {
				if (playtext.size() <= wordAmt) {
					keyPresses++;
					multiplier++;
				}
			}
		}
		/*sound.setBuffer(keySounds[rand() % 4]);
		sound.setVolume(30);
		sound.play();*/

		/*for (int i = 0; i < 3; i++) {
			if (startMenu[i].inputEvent(inputChar)) {
				for (int j = 0; j < 3; j++) {
					startMenu[j].isSelected = false;
				}
				startMenu[i].isSelected = true;
			}
		}
		if (startMenu[0].typedText == startMenu[0].text) {
			startSelected = true;
			switchScene = true;
		}
		if (startMenu[2].typedText == startMenu[2].text) window->close();*/
	}


}

e_gameState PlayScene::switchSceneEvent() {
	isStarted = false;
	if (errorWhenLoading) {
		return MENU;
	}
	if (back) {
		return MENU;
	}
	if (finished) {
		ResultScenePointer->setupInfo(time, charAmt, ((keyPresses-mistakes) / (float)keyPresses), score);  //float time, int charAmt, int mistakes, int score
		return RESULT;
	}
}

void PlayScene::loadText()
{
	std::vector<std::wstring> result;
	//in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wifstream in("resources/zdb-win8.txt", std::ifstream::in);
	in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	if (in.is_open()) {
		std::wstring line;
		while (in.good()) {
			std::getline(in, line);
			int to = 0;
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == ' ') {
					to = i;
				}
			}
			line = line.substr(to + 1);
			result.push_back(line);
		}
		in.close();
	}
	loaded = true;
	text = result;
}

void PlayScene::setResultScenePointer(ResultScene* ptr){
	ResultScenePointer = ptr;
}

float PlayScene::lerp(float a, float b, float f) {
	return a + f * (b - a);
}

float PlayScene::SmoothApproach(float pastPosition, float pastTargetPosition, float targetPosition, float speed, float deltaTime)
{
	float t = deltaTime * speed;
	float v = (targetPosition - pastTargetPosition) / t;
	float f = pastPosition - pastTargetPosition + v;
	return targetPosition - v + f * expf(-t);
}

std::string PlayScene::nf(float time) {
	int seconds = (int)time % 60;
	int minutes = time / 60;
	int milliseconds = (int)((time - (int)time) * 100);
	std::string result = (minutes      <10 ? "0"+std::to_string(minutes)      : std::to_string(minutes)) + ":"
		               + (seconds      <10 ? "0"+std::to_string(seconds)      : std::to_string(seconds)) + ":"
		               + (milliseconds <10 ? "0"+std::to_string(milliseconds) : std::to_string(milliseconds));
	return result;
}

void PlayScene::pop(InputText* t) {
	sf::Text word;
	word.setFont(font);
	word.setStyle(sf::Text::Regular);
	word.setString(t->text);
	word.setCharacterSize(t->fontSize);
	word.setPosition(t->positionX - word.getLocalBounds().width / 2.0f, t->positionY);
	for (int i = 0; i < t->text.size(); i++) {
		float a = word.findCharacterPos(i).x;
		part.push_back({ a, t->positionY, t->text[i]});
	}
}