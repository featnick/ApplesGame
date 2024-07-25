#include "Math.h"
#include <cstdlib>

namespace AppleGame
{
	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight, float rectSize)
	{
		Position2D result;
		result.x = rectSize / 2.f + rand() / (float)RAND_MAX * (screenWidth - rectSize);
		result.y = rectSize / 2.f + rand() / (float)RAND_MAX * (screenHeight - rectSize);
		return result;
	}

	int GetRandomInt(int minInt, int maxInt)
	{
		int result;
		result = minInt + rand() % (maxInt - minInt + 1);
		return result;
	}

	//Find ractangles collide
	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
		Position2D rect2Position, Vector2D rect2Size)
	{
		//Check collisions for squares
		float dx = fabs(rect1Position.x - rect2Position.x);
		float dy = fabs(rect1Position.y - rect2Position.y);
		return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
			dy <= (rect1Size.y + rect2Size.y) / 2.f);
	}

	//Find circles collide
	bool IsCircleCollide(Position2D circ1Position, Vector2D circ1Size,
		Position2D circ2Position, Vector2D circ2Size)
	{
		//Check collisions for circles
		float squareDistance = (circ1Position.x - circ2Position.x) * (circ1Position.x - circ2Position.x) +
			(circ1Position.y - circ2Position.y) * (circ1Position.y - circ2Position.y);
		float squareRadiusSum = (circ2Size.x + circ1Size.x) * (circ2Size.y + circ1Size.y) / 4;
		return (squareDistance <= squareRadiusSum);
	}

	//Find wall collide
	bool IsWallCollide(Position2D playerPosition, Vector2D playerSize, int screenWidth, int screenHeight)
	{
		return (playerPosition.x - playerSize.x / 2.f < 0 || playerPosition.x + playerSize.y / 2.f > screenWidth || //Check screen borders collisions
			playerPosition.y - playerSize.x / 2.f < 0 || playerPosition.y + playerSize.y / 2.f > screenHeight);
	}

	Vector2D SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		Vector2D scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale.x,scale.y);
		return scale;
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(spriteRect.width * originX, spriteRect.height * originY);
	}
	
}