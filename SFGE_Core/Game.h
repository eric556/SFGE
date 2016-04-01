#pragma once
#include "Window.h"
#include <SFML\Graphics.hpp>

namespace SFGE{
	class Game{
	public:


		virtual void HandleInput() = 0;
		virtual void Render() = 0;
		virtual void Update() = 0;

		Window* GetWindow(){
			return &m_window;
		}

		sf::Time GetElapsed(){ return m_clock.getElapsedTime(); }
		void RestartClock(){ m_elapsed = m_clock.restart().asSeconds(); }
	protected:
		Window m_window;
		sf::Clock m_clock;
		float m_elapsed;
	};
}