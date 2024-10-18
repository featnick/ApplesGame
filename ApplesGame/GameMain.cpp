#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

using namespace AppleGame;

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);
	//Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	//Game initialization
	Game* game = new Game();
	InitGame(game);

	//Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// main loop
	while (window.isOpen())
	{
		FpsMax(*game);

		//Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
		}

		//Update game state
		UpdateGame(game, deltaTime, window);
		
		//Draw game
		//Draw everything
		window.clear();
		DrawGame(game, window);
		window.display();
	}
	delete game;

	return 0;
}