#include "soundMaster.h"

SoundMaster::SoundMaster() {
	for (int i = 0; i < 4; i++) {
		if (!keySounds[i].loadFromFile("resources/sounds/key" + std::to_string(i + 1) + ".ogg")) {
			exit(1);
		}
	}
	if (!success.loadFromFile("resources/sounds/success.ogg")) {
		exit(1);
	}
	if (!backspace.loadFromFile("resources/sounds/backspace.ogg")) {
		exit(1);
	}
	if (!error.loadFromFile("resources/sounds/error.ogg")) {
		exit(1);
	}
	if (!typeMusic.openFromFile("resources/sounds/music.ogg"))
		exit(1);// error
	typeMusic.setVolume(10);
	typeMusic.setLoop(true);
	keySound.setVolume(20);
	successSound.setVolume(20);
}

void SoundMaster::playKey()
{
	keySound.setBuffer(keySounds[rand() % 4]);
	keySound.play();
}

void SoundMaster::playBackspace()
{
	keySound.setBuffer(backspace);
	keySound.play();
}

void SoundMaster::playSuccess()
{
	successSound.setBuffer(success);
	successSound.play();
}

void SoundMaster::playError()
{
	keySound.setBuffer(error);
	keySound.play();
}

void SoundMaster::playTypeMusic() {
	typeMusic.play();
	typeMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(7.68f), sf::seconds(15.36f)));
}

void SoundMaster::stopTypeMusic() {
	typeMusic.stop();
}
