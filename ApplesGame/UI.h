#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"

namespace AppleGame
{
	struct PlayersRecords
	{
		std::string name;
		int record = 0;
	};

	struct UI
	{
		bool firstModeSelected = false;

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
		sf::Text firstModeText;
		sf::Text secondModeText;

		//victory text data
		sf::Text victoryText;

		//record table text
		sf::Text namesText;
		sf::Text recordsText;

		sf::Text recordTableText;

		sf::String stringNames = "";
		sf::String stringRecords = "";

		PlayersRecords playersRecords[15] = {
		{PLAYER_NAME,0},
		{"Rona",43},
		{"Saniel",32},
		{"Hannard",2},
		{"Dannedia",11},
		{"Myrna",7},
		{"Musoa",76},
		{"Darz",33},
		{"Hantha",55},
		{"Wal",111},
		{"Gunt",87},
		{"Zacches",63},
		{"Ent",25},
		{"Zita",77},
		{"Orka",97},
		};
	};


	static void InitText(sf::Text& text, sf::Font& font, sf::Color color, sf::String string, int size, float positionX, float positionY);
	void ShaffleRecordArray(UI& ui);
	void InitUI(UI& ui);
	void UpdateRecordTable(UI& ui, const struct Game& game);
	void UpdateUI(UI& ui, const struct Game& game);
	void DrawGameUI(UI& ui, sf::RenderWindow& window);
	void DrawGameOverUI(UI& ui, sf::RenderWindow& window);
	void DrawMenuUI(UI& ui, sf::RenderWindow& window);
	void DrawVictoryUI(UI& ui, sf::RenderWindow& window);
}
