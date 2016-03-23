#include "Game.h"


Game::Game() : m_window("Snake", sf::Vector2u(800, 600)), m_snake(m_world.GetBlockSize()), m_world(sf::Vector2u(800, 600)), m_menu(sf::Vector2u(800, 600)), m_instructions(sf::Vector2u(800, 600)), m_leaderboard(sf::Vector2u(800, 600)), m_gui(m_snake, sf::Vector2u(800,600))
{
	m_state = States::MainMenu;
	m_window.GetRenderWindow()->setKeyRepeatEnabled(false);
}


Game::~Game()
{
}

void Game::Update(){
	m_window.Update();
	float timestep = 1.0f / m_snake.GetSpeed();
	int a = 0;
	switch (m_state)
	{
	case States::Playing:
		a = 0;
		if (m_elapsed >= timestep){
			m_snake.Tick();
			m_world.Update(m_snake);
			m_gui.Update(m_snake);
			m_elapsed -= timestep;
			if (m_snake.HasLost()){
				m_snake.Reset();
			}
		}
		break;
	case States::MainMenu:
		a = 0;
		m_menu.Update();
		if (m_elapsed >= timestep){
			m_elapsed -= timestep;
		}
		break;
	case States::Instructions:
		a = 0;
		m_instructions.Update();
		if (m_elapsed >= timestep){
			m_elapsed -= timestep;
		}
		break;
	case States::Leaderboards:
		
		if (a == 0){
			m_leaderboard.Update();
			a++;
		}


		if (m_elapsed >= timestep){
			m_elapsed -= timestep;
		}
		break;
	case States::Exiting:
		m_window.SetDone(true);
		break;
	default:
		break;
	}
	
}


void Game::Render(){
	m_window.BeginDraw();
	
	switch (m_state)
	{
	case States::Playing:
		m_world.Render(*m_window.GetRenderWindow());
		m_snake.Render(*m_window.GetRenderWindow());
		m_gui.Render(*m_window.GetRenderWindow());
		break;
	case States::MainMenu:
		m_menu.Render(*m_window.GetRenderWindow());
		break;
	case States::Instructions:
		m_instructions.Render(*m_window.GetRenderWindow());
		break;
	case States::Leaderboards:
		m_leaderboard.Render(*m_window.GetRenderWindow());
		break;
	default:
		break;
	}
	m_window.EndDraw();
}

void Game::HandleInput(){
	bool upKeyPressed = false;
	bool downKeyPressed = false;
	sf::Event event;

	switch (m_state)
	{
	case States::Playing:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetPhysicalDirection() != Direction::Down)
		{
			m_snake.SetDirection(Direction::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetPhysicalDirection() != Direction::Up)
		{
			m_snake.SetDirection(Direction::Down);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetPhysicalDirection() != Direction::Right)
		{
			m_snake.SetDirection(Direction::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.GetPhysicalDirection() != Direction::Left)
		{
			m_snake.SetDirection(Direction::Right);
		}

		
		while (m_window.GetRenderWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)){
				m_window.SetDone(true);
			}
			else if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Key::BackSpace){
					m_state = States::MainMenu;
				}
			}

		}
		break;

		
	case States::MainMenu:
		while (m_window.GetRenderWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)){
				m_window.SetDone(true);
			}
			else if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Key::Up && m_menu.menuIndex > 0){
					m_menu.menuIndex--;
				}
				if (event.key.code == sf::Keyboard::Key::Down && m_menu.menuIndex < m_menu.menuOptions.size()-1){
					m_menu.menuIndex++;
				}
				if (event.key.code == sf::Keyboard::Key::Return){
					m_state = States(m_menu.menuIndex);
				}
			}

		}
		
		break;
	case States::Instructions:
		while (m_window.GetRenderWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)){
				m_window.SetDone(true);
			}
			else if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Key::BackSpace){
					m_state = States::MainMenu;
				}
			}

		}
	case States::Leaderboards:
		while (m_window.GetRenderWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)){
				m_window.SetDone(true);
			}
			else if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Key::BackSpace){
					m_state = States::MainMenu;
				}
			}

		}
		break;
	default:
		break;
	}
}

Window* Game::GetWindow(){
	return &m_window;
}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed += m_clock.restart().asSeconds(); }
