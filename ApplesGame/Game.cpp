#include "Game.h"

namespace AppleGame
{
	void InitGame(Game* game)
	{
		game->playerTexture.loadFromFile(RESOURCES_PATH + "Player.png");
		game->appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png");
		game->rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png");

		//init all
		InitUI(game->ui);
		InitSound(game->sound);
	}

	void DeInitGame(Game* game)
	{
		delete[] game->apple.applesPositions;
		delete[] game->apple.sprite;
		delete[] game->apple.isAppleEaten;
	}

	void HandleInput(Game& game)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			game.player.playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			game.player.playerDirection = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			game.player.playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			game.player.playerDirection = PlayerDirection::Down;
		}
	}

	void Restart(Game* game)
	{
		//Deinitialization game
		DeInitGame(game);

		//Init player state
		InitPlayer(game->player, *game);

		//Init apples
		InitApples(game->apple, *game);

		//Init stones
		InitRocks(game->rock, *game);

		game->numEatenApples = 0;
		game->fps = 0;
		game->timeSinceStart = 0;
		game->timeSinceChoice = 0;
		game->isGameOver = false;
		game->isVictory = false;
	}


	void UpdateGame(Game* game, float deltaTime)
	{
		if (!game->isMenuActive) // menu non active
		{
			if (!game->isGameOver && !game->isVictory)
			{
				//Update game state
				HandleInput(*game);

				// Update player state
				UpdatePlayer(game->player, deltaTime, *game);

				//Find player collisions with stones and screen borders
				FindPlayerCollisionWithObstacles(game->player, *game);

				//Find player collisions with apples
				FindPlayerCollisionWithApples(game->player, *game);

				//Find apples collisions with rocks
				FindAppleCollisionWithRocks(game->apple, *game);
			
			}
			else //GAME OVER
			{
				//restart
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					//Restart game;
					game->isMenuActive = true;
				}
			}
			UpdateUI(game->ui, *game);
			FpsMax(*game);
			FpsCount(*game, deltaTime);
		}
		else // menu active
		{
			// MODES SELECTION 1 - END_APPLES mode/ENDLESS_APPLES mode, 2 - NO_ACCELERATION mode/ACCELERATION mode
			if (!game->ui.firstModeSelected)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				{
					if(ModeActive(*game, GameSettingsBits::endlessApples))
						SwitchMode(*game, GameSettingsBits::endlessApples); //END_APPLES mode
					game->ui.firstModeSelected = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					if (!ModeActive(*game, GameSettingsBits::endlessApples))
						SwitchMode(*game, GameSettingsBits::endlessApples); //ENDLESS_APPLES mode
					game->ui.firstModeSelected = true;
				}
			}
			else
			{
				game->timeSinceChoice += deltaTime;
				if (game->timeSinceChoice > 0.5f)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
					{
						if (ModeActive(*game, GameSettingsBits::acceleratePlayer))
							SwitchMode(*game, GameSettingsBits::acceleratePlayer); //NO_ACCELERATION mode
						game->ui.firstModeSelected = false;
						Restart(game);
						game->isMenuActive = false;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
					{
						if (!ModeActive(*game, GameSettingsBits::acceleratePlayer))
							SwitchMode(*game, GameSettingsBits::acceleratePlayer); //ACCELERATION mode
						game->ui.firstModeSelected = false;
						Restart(game);
						game->isMenuActive = false;
					}
				}
			}
		}		
	}

	void FpsCount(Game& game, float deltaTime)
	{
		++game.fpsCount;
		game.timeSinceStart += deltaTime;
		if (game.timeSinceStart >= 1)
		{
			game.timeSinceStart = 0;
			game.fps = game.fpsCount;
			game.fpsCount = 0;
		}
	}

	void FpsMax(Game& game)
	{
		if (FPS_MAX != 0)
		{
			int fpsMax = FPS_MAX;
			sf::sleep(sf::milliseconds(1000 / fpsMax));
		}
		else
		{
			sf::sleep(sf::milliseconds(FPS_MAX));
		}
	}


	//Draw game
	void DrawGame(Game* game, sf::RenderWindow& window)
	{
		if (!game->isMenuActive)
		{
			DrawPlayer(game->player, window);
			DrawApple(game->apple, window);
			DrawRock(game->rock, window);
			DrawGameUI(game->ui, window);

			if (game->isGameOver)
			{
				DrawGameOverUI(game->ui, window);
			}
			else if (game->isVictory)
			{
				DrawVictoryUI(game->ui, window);
			}
		}
		else
		{
			DrawMenuUI(game->ui, window);
		}
	}

	void IsVictory(Game& game)
	{
		if (game.numEatenApples == game.apple.numApples)
		{
			game.isVictory = true;
		}
	}

	void SwitchMode(Game& game, GameSettingsBits mode)
	{
		game.gameSettings ^= mode;
	}

	bool ModeActive(Game& game, GameSettingsBits mode)
	{
		return (game.gameSettings & mode) == mode;
	}
}
