#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Math.h"

namespace AppleGame
{
	struct PlayersRecords
	{
		std::string name;
		int record = 0;
	};

	struct UI
	{
		//score text data
		sf::Font font;
		sf::Text scoreText;

		//game over text data
		sf::Text gameOverText;

		//restart text data
		sf::Text restartText;

		//close text data
		sf::Text closeText;

		//fps text data
		sf::Text fpsText;

		//menu ui
		sf::Text menuTitle;
		sf::Text menuText;
		
		//victory text data
		sf::Text victoryText;

		//record table data
		sf::Text recordTableText;
		sf::String recordsString = "";
		sf::Text recordsText;
		std::multimap<std::string, int> records = {
			{PLAYER_NAME, 0},
			{"Alex", GetRandomInt(1,200)},
			{"Gunt", GetRandomInt(1,200)},
			{"Ent", GetRandomInt(1,200)},
			{"Darz", GetRandomInt(1,200)}
		};
		std::multimap<int, std::string> recordsTable;

		//mode settings data
		sf::Text modeSettingsText1;
		sf::Text modeSettingsText2;
		sf::Text activeModeText1;
		sf::Text activeModeText2;
		sf::Text backToMenuText;
		
		//pause menu data
		sf::Text pauseMenuText;
		sf::RectangleShape pauseBackground;
	};

	struct Game;

	static void InitText(sf::Text& text, sf::Font& font, sf::Color color, sf::String string, int size, float positionX, float positionY);
	void InitUI(UI& ui, Game* game);
	void UpdateRecordTable(UI& ui, Game* game);
	void UpdateSettingsUI(UI& ui, Game& game);
	void UpdateUI(UI& ui, Game& game);
	void DrawPauseMenu(UI& ui, sf::RenderWindow& window);
	void DrawRecordTable(UI& ui, sf::RenderWindow& window);
	void DrawGameUI(UI& ui, sf::RenderWindow& window);
	void DrawGameOverUI(UI& ui, sf::RenderWindow& window);
	void DrawMenuUI(UI& ui, sf::RenderWindow& window);
	void DrawVictoryUI(UI& ui, sf::RenderWindow& window);
	void DrawModeSettings(UI& ui, sf::RenderWindow& window);
}
