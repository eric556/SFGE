#pragma once
#include "Window.h"
#include <SFML\Graphics.hpp>

namespace SFGE{
	class Game{
	public:

		/*! A pure virtual method for the render phase
		*/
		virtual void Render() = 0;
		/*! A pure virtual method for the update phase
		*/
		virtual void Update() = 0;
		/*! A pure virtual method for running the game
		*/
		virtual void Run() = 0;

		/*! Gets the elapsed time from the start of the game clock
			\return float elapsed time
		*/
		float GetElapsed(){ return m_elapsed; }
		/*! Resets the game clock		
		*/
		void RestartClock(){ m_elapsed = m_clock.restart().asSeconds(); }
	protected:
		sf::Clock m_clock;
		float m_elapsed;
	};
}