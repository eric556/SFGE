#include "Game.h"


Game::Game() : m_window(" Page 31", sf::Vector2u(600,400))
{
	
	m_mushroomTexture.loadFromFile("Mushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);
	m_increment = sf::Vector2i(400, 400);
}


Game::~Game()
{
}

void Game::Update(){
	m_window.Update();
	MoveMushroom();
}

void Game::MoveMushroom(){
	sf::Vector2u l_windSize = m_window.GetWindowSize();   sf::Vector2u l_textSize = m_mushroomTexture.getSize();
	if ((m_mushroom.getPosition().x > l_windSize.x - l_textSize.x&&m_increment.x> 0) || (m_mushroom.getPosition().x < 0 && m_increment.x< 0))
	{ 
		m_increment.x = -m_increment.x; 
	}
	if ((m_mushroom.getPosition().y > l_windSize.y - l_textSize.y&&m_increment.y> 0) || (m_mushroom.getPosition().y < 0 && m_increment.y< 0))
	{ 
		m_increment.y = -m_increment.y; 
	}
	float fElapsed = m_elapsed.asSeconds();

	m_mushroom.setPosition(m_mushroom.getPosition().x + (m_increment.x * fElapsed), m_mushroom.getPosition().y +( m_increment.y * fElapsed));
}

void Game::Render(){
	m_window.BeginDraw();
	m_window.Draw(m_mushroom);
	m_window.EndDraw();
}

void Game::HandleInput(){

}

Window* Game::GetWindow(){
	return &m_window;
}

sf::Time Game::GetElapsed(){ return m_elapsed; } 
void Game::RestartClock(){ m_elapsed = m_clock.restart(); }