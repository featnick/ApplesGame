#include "Game.h"

namespace AppleGame
{
	void InitGame(Game* game)
	{
		game->playerTexture.loadFromFile(RESOURCES_PATH + "Player.png");
		game->appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png");
		game->rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png");

		//init all
		InitUI(game->ui, game);
		InitSound(game->sound);
	}

	void DeInitGame(Game* game)
	{

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

	void UpdatePlayingState(Game* game, float deltaTime)
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				game->gameState = GameState::PauseMenu;
			}

		}
		else //GAME OVER
		{
			//restart
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				//Restart game;
				game->gameState = GameState::MainMenu;
			}
		}
		UpdateUI(game->ui, *game);
		FpsCount(*game, deltaTime);
	}

	void UpdateMainMenuState(Game* game, sf::RenderWindow& window, float deltaTime)
	{
		sf::sleep(sf::milliseconds(50));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			Restart(game);
			game->gameState = GameState::Playing;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			game->gameState = GameState::ModeSettings;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			UpdateRecordTable(game->ui, game);
			game->gameState = GameState::RecordTable;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			CloseGame(window);
		}
	}

	void UpdateRecordMenuState(Game* game)
	{
		BackToMenu(game);
	}

	void UpdateModeSettingsState(Game* game, float deltaTime)
	{
		sf::sleep(sf::milliseconds(75));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			SwitchMode(*game, GameSettingsBits::endlessApples);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			SwitchMode(*game, GameSettingsBits::acceleratePlayer);
		}
		UpdateSettingsUI(game->ui, *game);
		BackToMenu(game);
	}

	void UpdatePauseMenuState(Game* game)
	{
		sf::sleep(sf::milliseconds(50));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			game->gameState = GameState::Playing;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			game->gameState = GameState::MainMenu;
		}
	}

	void UpdateGame(Game* game, float deltaTime, sf::RenderWindow& window)
	{
		switch (game->gameState)
		{
		case GameState::MainMenu:
		{
			UpdateMainMenuState(game, window, deltaTime);
			break;
		}
		case GameState::Playing:
		{
			UpdatePlayingState(game, deltaTime);
			break;
		}
		case GameState::RecordTable:
		{
			UpdateRecordMenuState(game);
			break;
		}
		case GameState::ModeSettings:
		{
			UpdateModeSettingsState(game, deltaTime);
			break;
		}
		case GameState::PauseMenu:
		{
			UpdatePauseMenuState(game);
			break;
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
		switch (game->gameState)
		{
		case GameState::PauseMenu:
		case GameState::Playing:
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
			
			if (game->gameState == GameState::PauseMenu)
			{
				DrawPauseMenu(game->ui, window);
			}
			break;
		}
		case GameState::MainMenu:
		{
			DrawMenuUI(game->ui, window);
			break;
		}
		case GameState::RecordTable:
		{
			DrawRecordTable(game->ui, window);
			break;
		}
		case GameState::ModeSettings:
		{
			DrawModeSettings(game->ui, window);
			break;
		}
		}
	}

	void BackToMenu(Game* game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			game->gameState = GameState::MainMenu;
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

	void CloseGame(sf::RenderWindow& window)
	{
		window.close();
	}
}
