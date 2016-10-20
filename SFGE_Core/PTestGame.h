#pragma once
#include "Game.h"
#include "EventManager.h"
#include "RigidBody.h"

class PTestGame : public SFGE::Game
{
public:
	PTestGame(std::string l_title, sf::Vector2u windowSize);
	~PTestGame();
	void Update();
	void FixedUpdate(float deltaTime);
	void Render();
	void Run();
	SFGE::Window* GetWindow(){
		return &m_window;
	}

private:
	SFGE::Window m_window;
	RigidBody body;
	RigidBody body2;
private:
	void Jump(SFGE::EventDetails* details);
	void Right(SFGE::EventDetails* details);
	void Left(SFGE::EventDetails* details);
	void Down(SFGE::EventDetails* details);
};