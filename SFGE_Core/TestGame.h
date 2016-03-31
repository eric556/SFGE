#pragma once
#include "Game.h"

class TestGame : public Game{
public:
	TestGame(std::string title, sf::Vector2u windowSize);
	~TestGame();
	void Update();
	void Render();
	void HandleInput();

private:
	sf::RectangleShape rect;
};