#pragma once
#include "Game.h"
#include "EventManager.h"

class TestGame : public SFGE::Game{
public:
	TestGame(std::string title, sf::Vector2u windowSize);
	~TestGame();
	void Update();
	void Render();
	void HandleInput();
	void MoveRight(SFGE::EventDetails* l_details);
	void MoveLeft(SFGE::EventDetails* l_details);

private:
	sf::RectangleShape rect;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};