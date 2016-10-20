#include "PTestGame.h"

void print(sf::Vector2f vec)
{
	std::cout << vec.x << ", " << vec.y << "\n";
}

void PTestGame::Jump(SFGE::EventDetails* details){
	body.AddImpulse(sf::Vector2f(0, -100),0.1, GetElapsed());
	std::cout << "key pressed\n";
}

void PTestGame::Right(SFGE::EventDetails* details){
	body.AddImpulse(sf::Vector2f(100, 0), 0.1, GetElapsed());
	std::cout << "key pressed\n";
}

void PTestGame::Left(SFGE::EventDetails* details){
	body.AddImpulse(sf::Vector2f(-100, 0), 0.1, GetElapsed());
	std::cout << "key pressed\n";
}

void PTestGame::Down(SFGE::EventDetails* details){
	body.AddImpulse(sf::Vector2f(0 , 100), 0.1, GetElapsed());
	std::cout << "key pressed Down\n";
}

PTestGame::PTestGame(std::string l_title, sf::Vector2u windowSize) : m_window(l_title, windowSize, "PhysicsTestGame/keys.cfg"), body(0, 1), body2(0, 1)
{
	m_window.SetClearColor(sf::Color::Black);
	body.SetPosition(m_window.GetWindowSize().x / 2 , m_window.GetWindowSize().y / 2 - 300);
	body2.SetPosition(m_window.GetWindowSize().x / 2 - 10, m_window.GetWindowSize().y / 2  );
	body2.GetBoundingBox().setFillColor(sf::Color::Green);
	body2.SetCollisionMask("Ground");
	body.collidables.push_back(body2);
	m_window.GetEventManager()->AddCallback("Jump", &PTestGame::Jump, this);
	m_window.GetEventManager()->AddCallback("Left", &PTestGame::Left, this);
	m_window.GetEventManager()->AddCallback("Right", &PTestGame::Right, this);
	m_window.GetEventManager()->AddCallback("Down", &PTestGame::Down, this);
}

PTestGame::~PTestGame()
{

}

void PTestGame::Update()
{
	this->m_window.Update();
}

void PTestGame::FixedUpdate(float deltaTime){

	for (int i = 0; i < body.collidedWith.size(); i++){
		
	}

	body.Update(deltaTime);
	body2.Update(deltaTime);
	/*if (body.GetPosition().y >= m_window.GetWindowSize().y / 2){
		body.AddImpulse(sf::Vector2f(0, -200), 0.5, deltaTime);
	}*/
}

void PTestGame::Render()
{
	m_window.BeginDraw();
	body.Draw(m_window);
	body2.Draw(m_window);
	m_window.EndDraw();
}

void PTestGame::Run()
{
	sf::Clock fixedUpdateClock;
	fixedUpdateClock.restart();
	this->RestartClock();
	int c = 0;
	while (!this->GetWindow()->IsDone())
	{
		this->Update();
		if (fixedUpdateClock.getElapsedTime().asSeconds() >= (1.0f/60.0f)){
			this->FixedUpdate(fixedUpdateClock.restart().asSeconds());
		}
		this->Render();
		this->RestartClock();
	}
}
