#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Math.h"
#include <vector>

namespace AppleGame
{
	struct Apple
	{
		//Aplles data
		int numApples = MAX_APPLES;
		std::vector<Position2D> applesPositions;
		std::vector<sf::Sprite> sprite;
		std::vector<bool> isAppleEaten;
	};

	struct Game;

	void InitApples(Apple& apple, const Game& game);
	void RegenerateApple(Apple& apple, int i);
	void FindAppleCollisionWithRocks(Apple& apple, Game& game);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}
