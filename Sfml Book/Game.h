#pragma once
#include "Window.h"
#include "World.h"

class Game{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();
private:
	void MoveMushroom();

	Window m_window;
	sf::Clock m_clock;
	float m_elapsed;
	World m_world;
	Snake m_snake;
};