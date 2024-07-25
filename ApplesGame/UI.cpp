#include "UI.h"
#include "Game.h"

namespace AppleGame
{
	static void InitText(sf::Text& text, sf::Font& font, sf::Color color, sf::String string, int size, float positionX, float positionY)
	{
		text.setCharacterSize(size);
		text.setFont(font);
		text.setFillColor(color);
		text.setPosition(positionX, positionY);
		text.setString(string);
	}

	void ShaffleRecordArray(UI& ui)
	{
		for (int i = 0; i < 20; ++i)
		{
			int firstElement = GetRandomInt(1, 14);
			int secondElement = GetRandomInt(1, 14);
			while (firstElement == secondElement)
			{
				secondElement = GetRandomInt(1, 14);
			}
			int temp = ui.playersRecords[firstElement].record;
			std::string tempS = ui.playersRecords[firstElement].name;

			ui.playersRecords[firstElement].record = ui.playersRecords[secondElement].record;
			ui.playersRecords[firstElement].name = ui.playersRecords[secondElement].name;

			ui.playersRecords[secondElement].record = temp;
			ui.playersRecords[secondElement].name = tempS;
		}
	}

	void InitUI(UI& ui)
	{
		ui.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Black.ttf");

		//init score text
		InitText(ui.scoreText, ui.font, sf::Color::Magenta, "0", 20, 6.f, 6.f);

		//init game over text
		InitText(ui.gameOverText, ui.font, sf::Color::Red, "Game over!", 40, 300.f, 200.f);

		//init restart text
		InitText(ui.restartText, ui.font, sf::Color::White, "Press 'Space' to restart a game!", 20, 250.f, 300.f);

		//init close text
		InitText(ui.closeText, ui.font, sf::Color::White, "Press 'Escape' to close a game\nMove on 'wasd' or 'arrows'", 15, 550.f, 550.f);

		//init fps text
		InitText(ui.fpsText, ui.font, sf::Color::White, "0", 15, 6.f, 30.f);

		//init menu title
		InitText(ui.menuTitle, ui.font, sf::Color::White, "MENU", 50, SCREEN_WIDTH / 2.f, 100.f);
		ui.menuTitle.setOrigin(75,1);

		//init menu text (mode selector)
		InitText(ui.firstModeText, ui.font, sf::Color::White, "END_APPLES mode - 1 \nENDLESS_APPLES mode - 2", 30, SCREEN_WIDTH / 2.f, 300.f);
		ui.firstModeText.setOrigin(190, 1);

		//init second menu text
		InitText(ui.secondModeText, ui.font, sf::Color::White, "NO_ACCELERATION mode - 1 \nACCELERATION mode - 2", 30, SCREEN_WIDTH / 2.f, 300.f);
		ui.secondModeText.setOrigin(190, 1);

		//init victory text
		InitText(ui.victoryText, ui.font, sf::Color::Yellow, "You won!", 40, 300.f, 200.f);
	
		//init record table text
		InitText(ui.namesText, ui.font, sf::Color::White, ui.stringNames, 15, 650.f, 27.5f);
		InitText(ui.recordsText, ui.font, sf::Color::White, ui.stringRecords, 15, 750.f, 27.5f);
		InitText(ui.recordTableText, ui.font, sf::Color::White, "RECORD TABLE: \n1.\n2.\n3.\n4.\n5.", 15, 600.f, 10.f);
		ShaffleRecordArray(ui);
	}

	void UpdateRecordTable(UI& ui, const struct Game& game)
	{
		//sort
		for (int i = 0; i < NUM_RECORD_VALUES; ++i)
		{
			for (int j = NUM_RECORD_VALUES - 1; j > 0; --j)
			{
				if (ui.playersRecords[j].record > ui.playersRecords[j - 1].record)
				{
					int temp = ui.playersRecords[j].record;
					std::string tempS = ui.playersRecords[j].name;

					ui.playersRecords[j].record = ui.playersRecords[j - 1].record;
					ui.playersRecords[j].name = ui.playersRecords[j - 1].name;

					ui.playersRecords[j - 1].record = temp;
					ui.playersRecords[j - 1].name = tempS;
				}
			}
		}
		//update string
		ui.stringNames = "";
		ui.stringRecords = "";
		for (int i = 0; i < NUM_RECORD_VALUES; ++i)
		{
			ui.stringNames += ui.playersRecords[i].name + "\n";
			ui.stringRecords += std::to_string(ui.playersRecords[i].record) + "\n";
		}
		ui.namesText.setString(ui.stringNames);
		ui.recordsText.setString(ui.stringRecords);
	}

	void UpdateUI(UI& ui, const struct Game& game)
	{
		for (int i = 0; i < NUM_RECORD_VALUES; ++i)
		{
			if (ui.playersRecords[i].name == PLAYER_NAME) //find player in record table
			{
				if (ui.playersRecords[i].record < game.numEatenApples || ui.playersRecords[i].record == 0)
				{
					ui.playersRecords[i].record = game.numEatenApples;
					UpdateRecordTable(ui, game);
				}
			}
		}

		ui.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples)); //Score text

		ui.fpsText.setString("fps: " + std::to_string(game.fps)); //fps text
	}

	void DrawGameUI(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.closeText);
		window.draw(ui.scoreText);
		window.draw(ui.fpsText);
		window.draw(ui.namesText);
		window.draw(ui.recordsText);
		window.draw(ui.recordTableText);
	}

	void DrawGameOverUI(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.gameOverText);
		window.draw(ui.restartText);
	}

	void DrawMenuUI(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.menuTitle);
		if (!ui.firstModeSelected)
		{
			window.draw(ui.firstModeText);
		}
		else
		{
			window.draw(ui.secondModeText);
		}
	}

	void DrawVictoryUI(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.victoryText);
		window.draw(ui.restartText);
	}
}
