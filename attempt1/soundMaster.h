#pragma once
#include<SFML/Audio.hpp>
class SoundMaster
{
public:
	SoundMaster();
	~SoundMaster() {}

private:
	sf::SoundBuffer keySounds[4];
	sf::SoundBuffer backspace;
	sf::SoundBuffer error;
	sf::SoundBuffer success;
	sf::Music typeMusic;
	sf::Sound keySound;
	sf::Sound successSound;

public:
	void playKey();
	void playBackspace();
	void playSuccess();
	void playError();
	void playTypeMusic();
	void stopTypeMusic();
};

