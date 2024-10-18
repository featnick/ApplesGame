#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "UI.h"
#include "Sound.h"
#include "Settings.h"

namespace AppleGame
{
	enum class GameState
	{
		MainMenu = 0,
		Playing,
		RecordTable,
		ModeSettings,
		PauseMenu,
	};

	enum GameSettingsBits
	{
		endlessApples = 1 << 0,
		acceleratePlayer = 1 << 1
	};
	
	struct Game
	{
		Player player;
		Apple apple;
		Rock rock;
		UI ui;
		Sound sound;

		bool isGameOver = false;
		bool isVictory = false;
		
		GameState gameState = GameState::MainMenu;

		//game mode
		int gameSettings = 0;
		//Scores
		int numEatenApples = 0;
		//fps
		int fps = 0;
		int fpsCount = 0;
		float timeSinceStart = 0;
		float timeSinceChoice = 0;

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
	};

	void InitGame(Game* game);
	void DeInitGame(Game* game);
	void HandleInput(Game& game);
	void Restart(Game* game);
	void UpdatePlayingState(Game* game, float deltaTime);
	void UpdateMainMenuState(Game* game, sf::RenderWindow& window, float deltaTime);
	void UpdateRecordMenuState(Game* game);
	void UpdateModeSettingsState(Game* game, float deltaTime);
	void UpdatePauseMenuState(Game* game);
	void UpdateGame(Game* game, float deltaTime, sf::RenderWindow& window);
	void DrawGame(Game* game, sf::RenderWindow& window);
	void BackToMenu(Game* game);
	void FpsCount(Game& game, float deltaTime);
	void FpsMax(Game& game);
	void IsVictory(Game& game);
	void SwitchMode(Game& game, GameSettingsBits mode);
	bool ModeActive(Game& game, GameSettingsBits mode);
	void CloseGame(sf::RenderWindow& window);
}
