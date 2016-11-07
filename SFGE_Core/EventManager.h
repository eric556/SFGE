#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>


namespace SFGE{
	/*! Enum holding all the sf::Event types
	*/
	enum class EventType{
		KeyDown = sf::Event::KeyPressed,
		KeyUp = sf::Event::KeyReleased,
		MButtonDown = sf::Event::MouseButtonPressed,
		MButtonUp = sf::Event::MouseButtonReleased,
		MouseWheel = sf::Event::MouseWheelMoved,
		WindowResized = sf::Event::Resized,
		GainedFocus = sf::Event::LostFocus,
		MouseEntered = sf::Event::MouseEntered,
		MouseLeft = sf::Event::MouseLeft,
		Closed = sf::Event::Closed,
		TextEntered = sf::Event::TextEntered,
		Keyboard = sf::Event::Count + 1, 
		Mouse, 
		Joystick
	};

	/*! Info of the event
	*/
	struct EventInfo{
		/*! Default Constructor for EventInfo
		*/
		EventInfo(){ m_code = 0; }
		/*! Constructor for EventInfo
			\param l_event event code
		*/
		EventInfo(int l_event){ m_code = l_event; }
		/*! Union holding an event code
		*/
		union{
			int m_code;
		};
	};

	using Events = std::vector < std::pair<EventType, EventInfo> > ;

	/*! Struct holding event details
	*/
	struct EventDetails{
		EventDetails(const std::string& l_bindName) : m_name(l_bindName){
			Clear();
		}
		//! name of the event
		std::string m_name;
		//! size of the event (if needed)
		sf::Vector2i m_size;
		//! text entered
		sf::Uint32 m_textEntered;
		//! mouse location
		sf::Vector2i m_mouse;
		//! mouse wheel position change
		int m_mouseWheelDelta;
		//! key code
		int m_keyCode;

		/*! Sets all the members of EventDetails to default
		*/
		void Clear(){
			m_size = sf::Vector2i(0, 0);
			m_textEntered = 0;
			m_mouse = sf::Vector2i(0, 0);
			m_mouseWheelDelta = 0;
			m_keyCode = -1;
		}

	};

	/*! Struct holding binding info
	*/
	struct Binding {
		/*! Constructor for binding
			\param l_name name of the binding
		*/
		Binding(const std::string& l_name) :m_name(l_name), m_details(l_name), c(0){}

		/*! Puts the EventType and EventInfo into a vector of EventType and EventInfo pairs
		*/
		void BindEvent(EventType l_type, EventInfo l_info = EventInfo()){
			m_events.emplace_back(l_type, l_info);
		}
		//! vector of pairs containing EventInfo and EventDetails
		Events m_events;
		//! name of the binding
		std::string m_name;
		//! details of the event
		EventDetails m_details;
		//! 
		int c;
	};

	using Bindings = std::unordered_map < std::string, Binding* > ;
	using Callbacks = std::unordered_map < std::string, std::function<void(EventDetails*)> > ;
	
	/*! Handles events
	*/
	class EventManager{
	public:
		EventManager(std::string l_filepath);
		~EventManager();

		bool AddBinding(Binding *l_binding);
		bool RemoveBinding(std::string l_name);
		void SetFocus(const bool& l_focus){ m_hasFocus = l_focus; }

		template<class T>
		bool AddCallback(const std::string& l_name, void(T::*l_func)(EventDetails*), T* l_instance){
			auto temp = std::bind(l_func, l_instance,std::placeholders::_1);
			return m_callbacks.emplace(l_name, temp).second;
		}

		void RemoveCallback(const std::string& l_name){
			m_callbacks.erase(l_name);
		}

		void HandleEvent(sf::Event& l_event);
		void Update();

		sf::Vector2i GetMousePos(sf::RenderWindow* l_wind = nullptr){
			return (l_wind ? sf::Mouse::getPosition(*l_wind) : sf::Mouse::getPosition());
		}

	private:
		void LoadBindings();
		std::string m_bindingsFilepath;

		Bindings m_bindings;
		Callbacks m_callbacks;
		bool m_hasFocus;
	};
}