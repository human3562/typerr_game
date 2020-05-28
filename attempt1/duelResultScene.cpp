#include "duelResultScene.h"

void DuelResultScene::Start(sf::RenderWindow* window, NetworkManager* nM) {
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

	mainText.setFillColor(sf::Color(200, 200, 200));

	options[0].typedText = L"";
	options[0].centered = false;
	options[0].positionX = 20.0f;
	options[0].positionY = window->getSize().y - 180.0f;

	options[1].typedText = L"";
	options[1].centered = false;
	options[1].positionX = 20.0f;
	options[1].positionY = window->getSize().y - 100.0f;

	if (nM->isLoggedIn()) {
		nM->uploadResult(my_WPM, my_accuracy);
		while (!nM->sendDuelResult(nM->id, nM->who, my_time, my_WPM, my_accuracy, my_totalScore));  // because 000webhost is trash
	}

}

std::wstring DuelResultScene::nf(float time) {
	int seconds = (int)time % 60;
	int minutes = time / 60;
	int milliseconds = (int)((time - (int)time) * 100);
	std::wstring result = (minutes < 10 ? L"0" + std::to_wstring(minutes) : std::to_wstring(minutes)) + L":"
		+ (seconds < 10 ? L"0" + std::to_wstring(seconds) : std::to_wstring(seconds)) + L":"
		+ (milliseconds < 10 ? L"0" + std::to_wstring(milliseconds) : std::to_wstring(milliseconds));
	return result;
}

void DuelResultScene::Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime) {

	if (nM->opponentResult) {
		/*mainText.setCharacterSize(100);
		mainText.setPosition(20.0f, 5.0f);
		mainText.setRotation(-4.0f);
		mainText.setString(std::to_string(my_time) + " " + std::to_string(nM->os_time));
		window->draw(mainText);*/
		mainText.setCharacterSize(100);
		mainText.setPosition(20.f, 5.f);
		mainText.setRotation(-4.f);
		mainText.setString((my_time < nM->os_time)?L"Победа!":L"Поражение!");
		window->draw(mainText);

		mainText.setRotation(-1.0f);
		mainText.setCharacterSize(50);
		mainText.setPosition(20.0f, 120.0f);
		mainText.setString(L"Время: " + nf(my_time));
		window->draw(mainText);

		/*mainText.setPosition(20.0f, 170.0f);
		mainText.setString(L"Финальный счет: " + std::to_wstring(my_totalScore));
		window->draw(mainText);*/

		mainText.setPosition(20.0f, 170.0f);
		mainText.setString(L"WPM: " + std::to_wstring(my_WPM));
		window->draw(mainText);

		mainText.setPosition(20.0f, 220.0f);
		mainText.setString(L"Точность: " + std::to_wstring(my_accuracy) + L"%");
		window->draw(mainText);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		mainText.setString(L"Время: " + nf(nM->os_time));
		mainText.setPosition(window->getSize().x/2.f, 120.0f);
		window->draw(mainText);

		/*mainText.setString(L"Финальный счет: " + std::to_wstring(nM->os_score));
		mainText.setPosition(window->getSize().x - mainText.getLocalBounds().width - 20.f, 170.0f);
		window->draw(mainText);*/

		mainText.setString(L"WPM: " + std::to_wstring(nM->os_WPM));
		mainText.setPosition(window->getSize().x / 2.f, 170.0f);
		window->draw(mainText);

		mainText.setString(L"Точность: " + std::to_wstring(nM->os_ACC) + L"%");
		mainText.setPosition(window->getSize().x / 2.f, 220.0f);
		window->draw(mainText);



	}
	else {
		mainText.setCharacterSize(100);
		mainText.setString("Ждем результаты...");
		mainText.setPosition(20.0f, 5.0f);
		mainText.setRotation(-2.0f);
		window->draw(mainText);
	}



	//window->clear(sf::Color(50, 50, 50));

	//mainText.setFont(font);
	//mainText.setCharacterSize(100);
	//mainText.setFillColor(sf::Color(200, 200, 200));
	//mainText.setString(L"Победа!");
	//mainText.setPosition(20.0f, 5.0f);
	//mainText.setRotation(-4.0f);
	//window->draw(mainText);

	//mainText.setRotation(-1.0f);
	//mainText.setCharacterSize(50);
	//mainText.setPosition(20.0f, 120.0f);
	//mainText.setString(L"Время: " + nf(my_time));
	//window->draw(mainText);

	//mainText.setPosition(20.0f, 170.0f);
	//mainText.setString(L"Финальный счет: " + std::to_wstring(my_totalScore));
	//window->draw(mainText);

	//mainText.setPosition(20.0f, 220.0f);
	//mainText.setString(L"WPM (слов в минуту): " + std::to_wstring(my_WPM));
	//window->draw(mainText);

	//mainText.setPosition(20.0f, 270.0f);
	//mainText.setString(L"Точность: " + std::to_wstring(my_accuracy) + L"%");
	//window->draw(mainText);

	//for (int i = 1; i < 2; i++) {
	//	options[i].show(window, &optText, fElapsedTime);
	//}

	/*mainText.setRotation(-4.0f);
	mainText.setCharacterSize(70);
	mainText.setPosition(20.0f, window->getSize().y - 180.0f);
	mainText.setString(L"Ещё раз!");
	window->draw(mainText);

	mainText.setPosition(20.0f, window->getSize().y - 100.0f);
	mainText.setString(L"Назад");
	window->draw(mainText);*/

	//mainText.setFont(font2);
	//mainText.setPosition(window->getSize().x - 400.0f, (window->getSize().y / 2.0f) - 320.0f);
	//mainText.setCharacterSize(500);
	//mainText.setRotation(-10.0f);

	///*std::string grade = "";
	//if (my_WPM >= 100) grade = "S++";
	//else if (my_accuracy == 100) grade = "S+";
	//else if (my_accuracy >= 90 && my_WPM >= 60) grade = "S";
	//else if (my_accuracy >= 90 && my_WPM >= 40) grade = "A";
	//else if (my_accuracy >= 60 && my_WPM >= 40) grade = "B";
	//else if (my_WPM >= 30) grade = "C";
	//else grade = "D";

	//mainText.setString(grade);
	//window->draw(mainText);*/

	//window->display();
}

void DuelResultScene::EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm) {
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
		for (int i = 1; i < 2; i++) {
			if (options[i].inputEvent(inputChar, sm)) {
				atleastone = true;
				for (int j = 0; j < 2; j++) {
					options[j].isSelected = false;
				}
				options[i].isSelected = true;
			}
		}
		if (!atleastone) sm->playError();

		//if (options[0].typedText == options[0].text) {
		//	switchScene = true;
		//	restart = true;
		//}

		if (options[1].typedText == options[1].text) {
			switchScene = true;
			back = true;
		}

	}
}

e_gameState DuelResultScene::switchSceneEvent() {
	isStarted = false;
	//if (restart) return PLAY;
	if (back)    return MENU;
}

void DuelResultScene::setupInfo(float time, int charAmt, float accuracy, int score) {
	my_WPM = (int)((charAmt / 5) / (time / 60.0f));
	//accuracy = (((charAmt - mistakes) / charAmt) * 100);
	my_totalScore = (int)(score * (my_WPM / 30.0f));
	this->my_accuracy = (int)(accuracy * 100.0f);
	this->my_time = time;
}
