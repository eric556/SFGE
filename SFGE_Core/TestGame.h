#pragma once
#include "Game.h"
#include "EventManager.h"

class TestGame : public SFGE::Game{
public:
	TestGame(std::string title, sf::Vector2u windowSize);
	~TestGame();
	void Update();
	void Render();
	void Run();
	SFGE::Window* GetWindow(){
		return &m_window;
	}

private:
	std::vector<sf::CircleShape> trail;
	int c;
	int r, g, b, redUp, blueUp, greenUp;
	void ballUpdate();
	void rightPaddleUpdate();
	void leftPaddleUpdate();
	sf::Vector2f vel;
	SFGE::Window m_window;
	void RightPaddleMove(SFGE::EventDetails* l_details);
	void LeftPaddleMove(SFGE::EventDetails* l_details);
	void Debug(SFGE::EventDetails* l_details);
	sf::RectangleShape leftPaddle;
	sf::RectangleShape rightPaddle;
	sf::CircleShape ball;
};