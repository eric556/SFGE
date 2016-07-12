#include "TestGame.h"

TestGame::TestGame(std::string title, sf::Vector2u windowSize){
	m_window.GetRenderWindow()->setSize(windowSize);
	m_window.GetRenderWindow()->setTitle(title);
	rect.setSize(sf::Vector2f(100, 100));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(0, 0);
	if (!m_texture.loadFromFile("Mushroom.png")){
		std::cout << "Error: Loading Mushroom File\n";
	}

	m_sprite.setTexture(m_texture);

	m_window.GetEventManager()->AddCallback("Move_left", &TestGame::MoveLeft, this);
	m_window.GetEventManager()->AddCallback("Move_right", &TestGame::MoveRight, this);
}

TestGame::~TestGame(){

}


void TestGame::Update(){
	this->m_window.Update();
}

void TestGame::Render(){
	m_window.BeginDraw();
	m_window.Draw(m_sprite);
	m_window.EndDraw();
}

void TestGame::HandleInput(){
}

void TestGame::MoveRight(SFGE::EventDetails* l_details){
	std::cout << "moving right\n";
	m_sprite.move(sf::Vector2f(5 * this->GetElapsed().asMilliseconds(),0));
}

void TestGame::MoveLeft(SFGE::EventDetails* l_details){
	std::cout << "moving left\n";
	m_sprite.move(sf::Vector2f(-5 * this->GetElapsed().asMilliseconds(), 0));
	
}
