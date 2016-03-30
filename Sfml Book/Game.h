#pragma once
#include "Window.h"
#include "World.h"
#include "Menu.h"
#include "Leaderboard.h"
#include "Instruction.h"
#include "GUI.h"

enum States{Playing, Instructions,Leaderboards,Exiting, MainMenu};

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
	Menu m_menu;
	Snake m_snake;
	States m_state;
	Instruction m_instructions;
	Leaderboard m_leaderboard;
	GUI m_gui;

};