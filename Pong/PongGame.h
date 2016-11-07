#pragma once
#include <Game.h>
#include <EventManager.h>

class PongGame : public SFGE::Game{
public:
	PongGame(std::string title, sf::Vector2u windowSize);
	~PongGame();
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