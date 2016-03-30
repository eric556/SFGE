#pragma once
#include "Window.h"
#include <SFML\Graphics.hpp>

class Game{
public:
	Game();
	~Game();

	virtual void HandleInput();
	virtual void Render();
	virtual void Update();

	Window* GetWindow(){
		return &m_window;
	}

	sf::Time GetElapsed(){ return m_clock.getElapsedTime(); }
	void RestartClock(){ m_elapsed = m_clock.restart().asSeconds(); }
protected:
	Window m_window;
	sf::Clock m_clock;
	float m_elapsed;
};