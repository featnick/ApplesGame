#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Math.h"

namespace AppleGame
{
	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		//Player data
		Position2D playerPosition;//player's starting coordinates
		float playerSpeed = INITIAL_SPEED;
		PlayerDirection playerDirection = PlayerDirection::Right;

		sf::Sprite sprite;
		
	};

	struct Game;

	void InitPlayer(Player& player, const Game& game);
	void UpdatePlayer(Player& player, float deltaTime, Game& game);
	void FindPlayerCollisionWithObstacles(Player& player, Game& game);
	void FindPlayerCollisionWithApples(Player& player, Game& game);
	void DrawPlayer(Player& player, sf::RenderWindow& window);
}
