#pragma once
#include "Window.h"
#include <SFML\Graphics.hpp>

namespace SFGE{
	class Game{
	public:

		virtual void Render() = 0;
		virtual void Update() = 0;
		virtual void Run() = 0;


		float GetElapsed(){ return m_elapsed;/*m_clock.getElapsedTime();*/ }
		void RestartClock(){ m_elapsed = m_clock.restart().asSeconds(); }
	protected:
		sf::Clock m_clock;
		float m_elapsed;
	};
}