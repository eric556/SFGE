#include "BasicGame.h"

BasicGame::BasicGame(std::string title, sf::Vector2u windowSize):m_window(title,windowSize,"Resources/Keys/keys.cfg"){
}

BasicGame::~BasicGame(){
}

void BasicGame::Update(){
	m_window.Update();
}

void BasicGame::FixedUpdate(float deltaTime){

}

void BasicGame::Render(){
	m_window.BeginDraw();
	m_window.EndDraw();
}

void BasicGame::Run(){
	sf::Clock fixedUpdateClock;
	fixedUpdateClock.restart();
	this->RestartClock();
	int c = 0;
	while (!this->GetWindow()->IsDone())
	{
		this->Update();
		if (fixedUpdateClock.getElapsedTime().asSeconds() >= (1.0f / 60.0f)){
			this->FixedUpdate(fixedUpdateClock.restart().asSeconds());
		}
		this->Render();
		this->RestartClock();
	}
}