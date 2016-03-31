#include "TestGame.h"

TestGame::TestGame(std::string title, sf::Vector2u windowSize){
	m_window.GetRenderWindow()->setSize(windowSize);
	m_window.GetRenderWindow()->setTitle(title);
	rect.setSize(sf::Vector2f(100, 100));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(0, 0);
}

TestGame::~TestGame(){

}


void TestGame::Update(){
	this->m_window.Update();
}

void TestGame::Render(){
	m_window.BeginDraw();
	m_window.Draw(rect);
	m_window.EndDraw();
}

void TestGame::HandleInput(){

}
