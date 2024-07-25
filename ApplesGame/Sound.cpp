#include "Sound.h"
#include "Settings.h"

namespace AppleGame
{
	void InitSound(Sound& sound)
	{
		sound.eatBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav");
		sound.eatSound.setBuffer(sound.eatBuffer);
		sound.eatSound.setVolume(20.f);

		sound.deathBuffer.loadFromFile(RESOURCES_PATH + "Death.wav");
		sound.deathSound.setBuffer(sound.deathBuffer);
		sound.deathSound.setVolume(20.f);
	};
}
