#include "Apple.h"
#include "Game.h"

namespace AppleGame
{
	void InitApples(Apple& apple, const Game& game)
	{
		apple.numApples = GetRandomInt(MIN_APPLES, MAX_APPLES);

		//Init apples
		apple.applesPositions.resize(apple.numApples);
		apple.sprite.resize(apple.numApples);
		apple.isAppleEaten.resize(apple.numApples);

		for (int i = 0; i < apple.numApples; ++i)
		{
			apple.isAppleEaten[i] = false;
			
			apple.applesPositions[i] = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT, APPLE_SIZE);

			apple.sprite[i].setTexture(game.appleTexture);
			SetSpriteSize(apple.sprite[i], APPLE_SIZE, APPLE_SIZE);
			SetSpriteRelativeOrigin(apple.sprite[i], 0.5f, 0.5f);
			apple.sprite[i].setPosition(apple.applesPositions[i].x, apple.applesPositions[i].y);
		}
	}

	void RegenerateApple(Apple& apple, int i)
	{
		// new apple generation
		apple.isAppleEaten[i] = false;
		apple.applesPositions[i] = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT, APPLE_SIZE);
		apple.sprite[i].setPosition(apple.applesPositions[i].x, apple.applesPositions[i].y);
	}

	void FindAppleCollisionWithRocks(Apple& apple, Game& game)
	{
		for (int i = 0;i < apple.numApples;++i)
		{
			for (int j = 0; j < NUM_ROCKS;++j)
			{
				if (IsRectanglesCollide(apple.applesPositions[i], { APPLE_SIZE,APPLE_SIZE },
					game.rock.rocksPosition[j], { ROCK_SIZE,ROCK_SIZE }))
				{
					RegenerateApple(apple, i);
				}
			}
		}
	}


	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		for (int i = 0;i < apple.numApples;++i)
		{
			if (!apple.isAppleEaten[i])
			{
				window.draw(apple.sprite[i]);
			}
		}
	}
	
}
