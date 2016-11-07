#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "EventManager.h"
namespace SFGE{
	//! Window Class
	/*! 
		Window class that is basicly a wrapper for the sf::RenderWindow class.
	*/
	class Window
	{
	public:
		/*! Default constructer for Window
			\param l_bindingsFilepath filepath to the key bindings
		*/
		Window(std::string l_bindingsFilepath);
		/*! Constructer for Window
			\param l_title title of the window
			\param l_size window size
			\param l_bindingsFilepath filepath to the key bindings
		*/
		Window(const std::string& l_title, const sf::Vector2u& l_size, std::string l_bindingsFilepath);
		/*! Closes the window.
		*/
		~Window();

		/*! Clears the window and prepares it for drawing
		*/
		void BeginDraw();//Clear the window
		/*! Displays what has been drawn to the window
		*/
		void EndDraw();// Display the changes

		/*! Updates the event manager by polling for sf::event from the window.
		*/
		void Update();
		/*! Checks if the Window is closed
			\return bool that is true if the window is closed and false if the window is open.
		*/
		bool IsDone();
		/*! Checks if the Window is focused
			\return bool
		*/
		bool IsFocused();
		/*! Check if the Window is fullscreen
			\return bool
		*/
		bool IsFullscreen();
		/*! Sets m_isDone to a bool
			\param done bool
		*/
		void SetDone(bool done);
		/*! Gets the Windows size
			\return Vector2u window size
		*/
		sf::Vector2u GetWindowSize();
		/*! Gets the sf::RenderWindow
			\return pointer to the sf::RenderWindow
		*/
		sf::RenderWindow* GetRenderWindow(){ return &m_window; }
		/*! Sets the clear color
			\param l_c color
		*/
		void SetClearColor(sf::Color l_c){ m_clearColor = l_c; }
		/*! Gets the clear color
			\return the clear color as sf::Color
		*/
		sf::Color GetClearColor(){ return m_clearColor; }
		/*! Gets the SFGE::EventManager of the Window
			\return pointer to the event manager
		*/
		EventManager* GetEventManager() { return &m_eventManager; }
		/*! Toggles fullscreen. Used by the Event Manager and is bound to a key
			\param l_details used by the event manager
		*/
		void ToggleFullscreen(EventDetails* l_details);
		/*! Closes the window. Used by event manager and is bound to a key
			\param l_details by default set to nullptr
		*/
		void Close(EventDetails* l_details = nullptr);
		/*! Used to draw to the Window
			\param l_drawable an sf::Drawable to draw to the screen
		*/
		void Draw(sf::Drawable& l_drawable);
		/*! Used to draw to the Window with a shader applied to the sf::Drawable
			\param l_drawable an sf::Drawable to draw to the screen
			\param l_shader and sf::Shader to apply to l_drawable
		*/
		void Draw(sf::Drawable& l_drawable, sf::Shader& l_shader);


	private:

		void Setup(const std::string& l_title, const sf::Vector2u& l_size);
		void Destroy();
		void Create();

		sf::RenderWindow m_window;
		sf::Vector2u m_windowSize;
		std::string m_windowTitle;
		bool m_isDone;
		bool m_isFullscreen;
		bool m_isFocused;
		sf::Color m_clearColor;

		EventManager m_eventManager;

	};
}

