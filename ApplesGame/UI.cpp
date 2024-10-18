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

	void InitUI(UI& ui, Game* game)
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

		//init menu
		InitText(ui.menuTitle, ui.font, sf::Color::White, "MENU", 50, 320.f, 100.f);
		InitText(ui.menuText, ui.font, sf::Color::White, "1 - Play \n2 - Game mode \n3 - Record table \n4 - Exit", 35, 270.f, 200.f);

		//init victory text
		InitText(ui.victoryText, ui.font, sf::Color::Yellow, "You won!", 40, 300.f, 200.f);
	
		//init record table text
		InitText(ui.recordTableText, ui.font, sf::Color::White, "RECORD TABLE: \n1.\n2.\n3.\n4.\n5.", 45, 250.f, 50.f);
		InitText(ui.recordsText, ui.font, sf::Color::Yellow, "", 45, 320, 100.f);

		//init mode settings text
		InitText(ui.modeSettingsText1, ui.font, sf::Color::White, "1 - Endless apples: ", 45, 120.f, 50.f);
		InitText(ui.modeSettingsText2, ui.font, sf::Color::White, "2 - Accelerate player: ", 45, 120.f, 130.f);
		InitText(ui.activeModeText1, ui.font, sf::Color::White, "", 45, 650.f, 50.f);
		InitText(ui.activeModeText2, ui.font, sf::Color::White, "", 45, 650.f, 130.f);

		InitText(ui.backToMenuText, ui.font, sf::Color::White, "Press 'b' or 'Escape' to return to the menu", 20, 50.f, 530.f);

		//init pause menu
		InitText(ui.pauseMenuText, ui.font, sf::Color::White, "\tPause\n1 - resume\n2 - exit to menu", 30, 320.f, 210.f);
		ui.pauseBackground.setFillColor(sf::Color::Blue);
		ui.pauseBackground.setPosition(300.f, 200.f);
		ui.pauseBackground.setSize({ 250.f, 150.f });
		
	}

	void UpdateRecordTable(UI& ui, Game* game)
	{
		auto playerRecord = ui.records.find(PLAYER_NAME);
		playerRecord->second = game->numEatenApples; //set the number of points for player
		ui.recordsTable.clear(); //clear the table
		for (auto it : ui.records)
		{
			ui.recordsTable.insert({ it.second,it.first }); //fill the table so that the autosorting is by the number of points
		}
		ui.recordsString = "";
		for (auto it = ui.recordsTable.rbegin(); it != ui.recordsTable.rend(); ++it)
		{
			ui.recordsString += it->second + ": " + std::to_string(it->first) + "\n";
		}
		ui.recordsText.setString(ui.recordsString);
	}

	void UpdateSettingsUI(UI& ui, Game& game)
	{
		ui.activeModeText1.setString(ModeActive(game, GameSettingsBits::endlessApples) ? "On" : "Off");
		ui.activeModeText2.setString(ModeActive(game, GameSettingsBits::acceleratePlayer) ? "On" : "Off");
	}

	void UpdateUI(UI& ui, Game& game)
	{
		ui.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples)); //Score text

		ui.fpsText.setString("fps: " + std::to_string(game.fps)); //fps text
	}

	void DrawPauseMenu(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.pauseBackground);
		window.draw(ui.pauseMenuText);
	}

	void DrawRecordTable(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.recordTableText);
		window.draw(ui.recordsText);
		window.draw(ui.backToMenuText);
	}

	void DrawGameUI(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.closeText);
		window.draw(ui.scoreText);
		window.draw(ui.fpsText);
	}

	void DrawGameOverUI(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.gameOverText);
		window.draw(ui.restartText);
	}

	void DrawMenuUI(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.menuTitle);
		window.draw(ui.menuText);
	}

	void DrawVictoryUI(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.victoryText);
		window.draw(ui.restartText);
	}

	void DrawModeSettings(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.modeSettingsText1);
		window.draw(ui.modeSettingsText2);
		window.draw(ui.activeModeText1);
		window.draw(ui.activeModeText2);
		window.draw(ui.backToMenuText);
	}
}
