#pragma once
#include <SFML/Audio.hpp>

namespace AppleGame
{
	struct Sound
	{
		sf::SoundBuffer eatBuffer;
		sf::Sound eatSound;

		sf::SoundBuffer deathBuffer;
		sf::Sound deathSound;
	};

	//struct Game;

	void InitSound(Sound& sound);
}