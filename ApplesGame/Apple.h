#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Math.h"

namespace AppleGame
{
	struct Apple
	{
		//Aplles data
		int numApples = MAX_APPLES;
		Position2D* applesPositions = new Position2D[numApples];
		sf::Sprite* sprite = new sf::Sprite[numApples];
		bool* isAppleEaten = new bool[numApples];
	};

	struct Game;

	void InitApples(Apple& apple, const Game& game);
	void RegenerateApple(Apple& apple, int i);
	void FindAppleCollisionWithRocks(Apple& apple, Game& game);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}
