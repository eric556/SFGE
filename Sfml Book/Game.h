#pragma once
#include "Window.h"
#include "World.h"

enum States{Playing, Menu, Exiting};

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
	States m_state;
};