#pragma once
#include <SFML/Graphics.hpp>

namespace AppleGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 100.f; //pixels per second
	const float PLAYER_SIZE = 20.f; //20
	const float PLAYER_ACCELERATION = 10.f; //pixels per second
	const int MAX_APPLES = 100;
	const int MIN_APPLES = 30;
	const float APPLE_SIZE = 20.f;
	const int NUM_ROCKS = 10;
	const float ROCK_SIZE = 15.f;
	const int FPS_MAX = 60; //0 - for unlimited fps
	const int NUM_RECORD_VALUES = 5; //number of record values
	const std::string PLAYER_NAME = "(You)";
}
