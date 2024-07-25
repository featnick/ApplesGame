#include "Player.h"
#include "Game.h"


namespace AppleGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		//Init player state
		player.playerPosition = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };//player's starting coordinates
		player.playerSpeed = INITIAL_SPEED;
		player.playerDirection = PlayerDirection::Right;


		//Init player sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void UpdatePlayer(Player& player, float deltaTime, Game& game)
	{
		switch (player.playerDirection)
		{
		case PlayerDirection::Right:
		{
			player.playerPosition.x += player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			player.playerPosition.y -= player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			player.playerPosition.x -= player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			player.playerPosition.y += player.playerSpeed * deltaTime;
			break;
		}
		}
	}

	void FindPlayerCollisionWithObstacles(Player& player, Game& game)
	{
		for (int i = 0;i < NUM_ROCKS;++i)
		{
			//Check collisions for squares
			if (IsRectanglesCollide(player.playerPosition, { PLAYER_SIZE,PLAYER_SIZE },
				game.rock.rocksPosition[i], { ROCK_SIZE,ROCK_SIZE }) ||
				IsWallCollide(game.player.playerPosition, { PLAYER_SIZE, PLAYER_SIZE }, SCREEN_WIDTH, SCREEN_HEIGHT))
			{
				game.isGameOver = true;
				game.sound.deathSound.play();
			}
		}
	}

	void FindPlayerCollisionWithApples(Player& player, Game& game)
	{
		for (int i = 0;i < game.apple.numApples;++i)
		{
			//Check collisions for circles
			if (!game.apple.isAppleEaten[i])
			{
				if (IsCircleCollide(player.playerPosition, { PLAYER_SIZE,PLAYER_SIZE },
					game.apple.applesPositions[i], { APPLE_SIZE,APPLE_SIZE }))
				{
					game.apple.isAppleEaten[i] = true;
					++game.numEatenApples;

					if (ModeActive(game, GameSettingsBits::acceleratePlayer)) //ACCELERATION MODE
					{
						player.playerSpeed += PLAYER_ACCELERATION; //acceleration with eaten apple
					}

					if (ModeActive(game, GameSettingsBits::endlessApples)) //ENDLESS APLLES MODE
					{
						// new apple generation
						RegenerateApple(game.apple, i);
					}
					else
					{
						IsVictory(game); //checking the number of apples 
					}

					game.sound.eatSound.play();
				}
			}
		}
	}


	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.playerPosition.x, player.playerPosition.y);
		window.draw(player.sprite);

		Vector2D spriteScale = (SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE));

		switch (player.playerDirection)
		{
		case PlayerDirection::Right:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0);
			break;
		}
		case PlayerDirection::Up:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(-90);
			break;
		}
		case PlayerDirection::Left:
		{
			player.sprite.setScale(-spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0);
			break;
		}
		case PlayerDirection::Down:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(90);
			break;
		}
		}
	}
}
