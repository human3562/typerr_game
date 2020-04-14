#pragma once
#include "gameScene.h"
#include "inputText.h"
#include "charParticle.h"
#include "resultScene.h"
#include <list>
class PlayScene : public GameScene
{
public:
	PlayScene() {}

public:
	void Start(sf::RenderWindow* window, NetworkManager* nM) override;
	void Update(sf::RenderWindow* window, NetworkManager* nM, float fElapsedTime) override;
	void EventHandle(sf::RenderWindow* window, sf::Event* event, NetworkManager* nM, SoundMaster* sm) override;
	e_gameState switchSceneEvent() override;
	void loadText();
	void setResultScenePointer(ResultScene* ptr);

private:
	float lerp(float a, float b, float f);
	float SmoothApproach(float pastPosition, float pastTargetPosition, float targetPosition, float speed, float deltaTime);
	void pop(InputText* t);
	std::string nf(float time);


private:
	sf::Text mainText;
	sf::Font font;
	std::vector<std::wstring> text;
	std::vector<InputText> playtext;
	std::vector<CharParticle> part;
	bool errorWhenLoading = false;
	bool back = false;
	bool loaded = false;
	bool finished = false;
	float fScreenRotation = 0.0f;

	int wordAmt = 10;
	int charAmt = 0;
	float time = 0.0f;
	int multiplier = 1;
	int score = 0;
	int mistakes = 0;
	int keyPresses = 0;

	ResultScene* ResultScenePointer = nullptr;
	/*sf::SoundBuffer keySounds[4];
	sf::Sound sound;*/
};

