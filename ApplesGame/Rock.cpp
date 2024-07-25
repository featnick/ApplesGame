#include "Rock.h"
#include "Game.h"

namespace AppleGame
{
	void InitRocks(Rock& rock, const Game& game)
	{
		rock.sprite.resize(NUM_ROCKS);
		rock.rocksPosition.resize(NUM_ROCKS);

		//Init stones
		for (int i = 0; i < NUM_ROCKS;++i)
		{
			rock.rocksPosition[i] = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT, ROCK_SIZE);

			rock.sprite[i].setTexture(game.rockTexture);
			SetSpriteSize(rock.sprite[i], ROCK_SIZE, ROCK_SIZE);
			SetSpriteRelativeOrigin(rock.sprite[i], 0.5f, 0.5f);
			rock.sprite[i].setPosition(rock.rocksPosition[i].x, rock.rocksPosition[i].y);
		}
	}

	void DrawRock(Rock& rock, sf::RenderWindow& window)
	{
		for (int i = 0;i < NUM_ROCKS;++i)
		{
			window.draw(rock.sprite[i]);
		}
	}
}
