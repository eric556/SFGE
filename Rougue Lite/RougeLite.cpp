#include "RougeLite.h"

RougeLite::RougeLite(std::string title, sf::Vector2u windowSize):m_window(title,windowSize,"Resources/Keys/keys.cfg"),map(this->m_window.GetWindowSize().x/10,this->m_window.GetWindowSize().y/10,10,10){

}

RougeLite::~RougeLite(){
}

void RougeLite::Update(){
	m_window.Update();
}

void RougeLite::FixedUpdate(float deltaTime){

}

void RougeLite::Render(){
	m_window.BeginDraw();
	map.Draw(this->m_window);
	m_window.EndDraw();
}

void RougeLite::Run(){
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