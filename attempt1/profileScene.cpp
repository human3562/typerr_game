#include "profileScene.h"

void ProfileScene::Start(sf::RenderWindow* window, NetworkManager* nM)
{
	isStarted = true;
	back = false;
	switchScene = false;
	if (!font.loadFromFile("resources/font2.ttf")) {
		//bad
	}

	mainText.setFont(font);
	mainText.setStyle(sf::Text::Regular);

	loggedIn = nM->isLoggedIn();

	loginForm.settings.clear();
	
	loginForm.selected = 0;

	t1.input = L"";
	t1.positionX = (window->getSize().x / 2.0f) - 90.0f;
	t1.positionY = (window->getSize().y / 2.0f) - 120.0f;
	
	t2.input = L"";
	t2.positionX = (window->getSize().x / 2.0f) - 90.0f;
	t2.positionY = (window->getSize().y / 2.0f) - 70.0f;

	t3.positionX = window->getSize().x - 650.0f;
	t3.positionY = window->getSize().y - 200.0f;
	t3.act = false;

	loginForm.settings.push_back(&t1);
	loginForm.settings.push_back(&t2);
	loginForm.settings.push_back(&t3);

}

void ProfileScene::Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime)
{
	window->clear(sf::Color(50, 50, 50));

	if (nM->isLoggedIn()) {
		mainText.setString(L"Привет, "+nM->getAccountName()+L"!");
		mainText.setRotation(0);
		mainText.setPosition(10.0f, 50.0f);
		mainText.setCharacterSize(50);
		window->draw(mainText);
		mainText.setString(L"Ваш средний WPM(слов в минуту): " + std::to_wstring(nM->getWPM()) + L";");
		mainText.setPosition(10.0f, 130.0f);
		mainText.setCharacterSize(30);
		window->draw(mainText);
		mainText.setString(L"Ваша средняя точность: " + std::to_wstring(nM->getACC()) + L"%.");
		mainText.setPosition(10.0f, 160.0f);
		mainText.setCharacterSize(30);
		window->draw(mainText);
	}
	else {
		//float x, float y, std::wstring textVal, float size, bool anim
		mainText.setFillColor(sf::Color(200,200,200));
		mainText.setCharacterSize(30);
		mainText.setRotation(0);
		mainText.setString(L"Вы не авторизованы.");
		mainText.setPosition((window->getSize().x / 2.0f) - mainText.getLocalBounds().width / 2.0f, 20.0f);
		window->draw(mainText);
		mainText.setString(L"Введите свои данные, или зарегистрируйте новый аккаунт.");
		mainText.setPosition((window->getSize().x / 2.0f) - mainText.getLocalBounds().width / 2.0f, 70.0f);
		window->draw(mainText);

		mainText.setFillColor(sf::Color(255, 0, 0));
		mainText.setString(errormessage);
		mainText.setPosition((window->getSize().x / 2.0f) - mainText.getLocalBounds().width / 2.0f, 120.0f);
		window->draw(mainText);
		mainText.setFillColor(sf::Color(255, 255, 255));

		mainText.setString(L"Логин:");
		mainText.setPosition((window->getSize().x / 2.0f) - mainText.getLocalBounds().width - 100.0f, (window->getSize().y/2.0f) - 120.0f);
		window->draw(mainText);
		mainText.setString(L"Пароль:");
		mainText.setPosition((window->getSize().x / 2.0f) - mainText.getLocalBounds().width - 100.0f, (window->getSize().y/2.0f) - 70.0f);
		window->draw(mainText);
		/*sf::RectangleShape loginBG(sf::Vector2f(120, 40));
		loginBG.setPosition((window->getSize().x / 2.0f) - 90.0f, 180.0f);
		window->draw(loginBG);*/
		loginForm.Show(window, &mainText, fElapsedTime);
		/*mainText.setFillColor(sf::Color(200, 200, 200));
		mainText.setPosition(window->getSize().x - 650.0f, window->getSize().y - 200.0f);
		mainText.setString(L"Подтвердить");
		mainText.setCharacterSize(100);
		mainText.setRotation(-10.0f);
		window->draw(mainText);*/
	}

	window->display();
}

void ProfileScene::EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm)
{
	if (event->type == sf::Event::KeyPressed) {
		if (event->key.code == sf::Keyboard::Escape) {
			switchScene = true;
			back = true;
		}
	}
	loginForm.EventHandle(window, event, sm);

	

	if (t3.act == true) {
		t3.act = false;
		//login with the input data
		switch(nM->login(t1.input, t2.input) == 1){
		case 0: errormessage = L"Неправильный логин или пароль!"; break;
		case 1: switchScene = true; back = true; break;
		case 2: errormessage = L"Не можем подключиться к серверу..."; break;
		case 3: errormessage = L"Что происходит..."; break;
		};
	}

}

e_gameState ProfileScene::switchSceneEvent()
{
	isStarted = false;
	if (back) {
		return MENU;
	}
	//return e_gameState();
}
