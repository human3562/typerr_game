#include "resultScene.h"

void ResultScene::Start(sf::RenderWindow* window, NetworkManager* nM){
	switchScene = false;
	isStarted = true;
	back = false;
	restart = false;

	if (!font.loadFromFile("resources/font2.ttf")) {
		//bad
	}
	if (!font2.loadFromFile("resources/font.ttf")) {
		//bad
	}

	mainText.setFont(font);
	optText.setFont(font);
	mainText.setStyle(sf::Text::Regular);

	options[0].typedText = L"";
	options[0].centered = false;
	options[0].positionX = 20.0f;
	options[0].positionY = window->getSize().y - 180.0f;

	options[1].typedText = L"";
	options[1].centered = false;
	options[1].positionX = 20.0f;
	options[1].positionY = window->getSize().y - 100.0f;

	if (nM->isLoggedIn()) {
		nM->uploadResult(WPM, accuracy);
	}

}

std::wstring ResultScene::nf(float time) {
	int seconds = (int)time % 60;
	int minutes = time / 60;
	int milliseconds = (int)((time - (int)time) * 100);
	std::wstring result = (minutes < 10 ? L"0" + std::to_wstring(minutes) : std::to_wstring(minutes)) + L":"
						+ (seconds < 10 ? L"0" + std::to_wstring(seconds) : std::to_wstring(seconds)) + L":"
						+ (milliseconds < 10 ? L"0" + std::to_wstring(milliseconds) : std::to_wstring(milliseconds));
	return result;
}

void ResultScene::Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime){
	window->clear(sf::Color(50, 50, 50));

	mainText.setFont(font);
	mainText.setCharacterSize(100);
	mainText.setFillColor(sf::Color(200, 200, 200));
	mainText.setString(L"Победа!");
	mainText.setPosition(20.0f, 5.0f);
	mainText.setRotation(-4.0f);
	window->draw(mainText);

	mainText.setRotation(-1.0f);
	mainText.setCharacterSize(50);
	mainText.setPosition(20.0f, 120.0f);
	mainText.setString(L"Время: " + nf(time));
	window->draw(mainText);

	mainText.setPosition(20.0f, 170.0f);
	mainText.setString(L"Финальный счет: " + std::to_wstring(totalScore));
	window->draw(mainText);

	mainText.setPosition(20.0f, 220.0f);
	mainText.setString(L"WPM (слов в минуту): " + std::to_wstring(WPM));
	window->draw(mainText);

	mainText.setPosition(20.0f, 270.0f);
	mainText.setString(L"Точность: " + std::to_wstring(accuracy) + L"%");
	window->draw(mainText);

	for (int i = 0; i < 2; i++) {
		options[i].show(window, &optText, fElapsedTime);
	}

	/*mainText.setRotation(-4.0f);
	mainText.setCharacterSize(70);
	mainText.setPosition(20.0f, window->getSize().y - 180.0f);
	mainText.setString(L"Ещё раз!");
	window->draw(mainText);

	mainText.setPosition(20.0f, window->getSize().y - 100.0f);
	mainText.setString(L"Назад");
	window->draw(mainText);*/

	mainText.setFont(font2);
	mainText.setPosition(window->getSize().x - 400.0f, (window->getSize().y/2.0f)-320.0f);
	mainText.setCharacterSize(500);
	mainText.setRotation(-10.0f);

	std::string grade = "";
	if (WPM >= 100) grade = "S++";
	else if (accuracy == 100) grade = "S+";
	else if (accuracy >= 90 && WPM >= 60) grade = "S";
	else if (accuracy >= 90 && WPM >= 40) grade = "A";
	else if (accuracy >= 60 && WPM >= 40) grade = "B";
	else if (WPM >= 30) grade = "C";
	else grade = "D";

	mainText.setString(grade);
	window->draw(mainText);

	window->display();
}

void ResultScene::EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm){
	if (event->type == sf::Event::KeyPressed) {
		if (event->key.code == sf::Keyboard::Escape) {
			switchScene = true;
			back = true;
		}
		if (event->key.code == sf::Keyboard::Enter) {
			for (int i = 0; i < 2; i++) {
				if (options[i].typedText != L"") options[i].typedText = options[i].text;
			}
		}
	}
	if (event->type == sf::Event::TextEntered) {
		wchar_t inputChar = static_cast<wchar_t>(event->text.unicode);
		//if (event->text.unicode == 13) inputChar = '\n';
		int atleastone = false;
		for (int i = 0; i < 2; i++) {
			if (options[i].inputEvent(inputChar, sm)) {
				atleastone = true;
				for (int j = 0; j < 2; j++) {
					options[j].isSelected = false;
				}
				options[i].isSelected = true;
			}
		}
		if (!atleastone) sm->playError();

		if (options[0].typedText == options[0].text) {
			switchScene = true;
			restart = true;
		}
		
		if (options[1].typedText == options[1].text) {
			switchScene = true;
			back = true;
		}

	}
}

e_gameState ResultScene::switchSceneEvent(){
	isStarted = false;
	if (restart) return PLAY;
	if (back)    return MENU;
}

void ResultScene::setupInfo(float time, int charAmt, float accuracy, int score){
	WPM = (int)((charAmt / 5) / (time / 60.0f));
	//accuracy = (((charAmt - mistakes) / charAmt) * 100);
	totalScore = (int)(score * (WPM / 30.0f));
	this->accuracy = (int)(accuracy * 100.0f);
	this->time = time;
}
