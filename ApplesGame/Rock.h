#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Math.h"
#include <vector>
#include <iostream>
#include <algorithm>

namespace AppleGame
{
	struct Rock
	{
		//Rocks data
		/*Position2D rocksPosition[NUM_ROCKS];
		sf::Sprite sprite[NUM_ROCKS];*/

		std::vector<Position2D> rocksPosition;
		std::vector<sf::Sprite> sprite;
	};

	struct Game;

	void InitRocks(Rock& rock, const Game& game);
	void DrawRock(Rock& rock, sf::RenderWindow& window);
}
