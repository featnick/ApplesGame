#pragma once
#include <SFML/Graphics.hpp>



namespace AppleGame
{
	struct Vector2D
	{
		float x = 0;
		float y = 0;
	};

	typedef Vector2D Position2D;

	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight, float rectSize);

	int GetRandomInt(int minInt, int maxInt);

	//Find ractangles collide
	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
		Position2D rect2Position, Vector2D rect2Size);

	//Find circles collide
	bool IsCircleCollide(Position2D circ1Position, Vector2D circ1Size,
		Position2D circ2Position, Vector2D circ2Size);

	//Find wall collide
	bool IsWallCollide(Position2D playerPosition, Vector2D playerSize, int screenWidth, int screenHeight);

	Vector2D SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);

}
