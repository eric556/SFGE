#include "Game.h"
#include "EventManager.h"
#include "Map.h"

class RougeLite : public SFGE::Game{
public:
	RougeLite(std::string title, sf::Vector2u windowSize);
	~RougeLite();
	void Update();
	void FixedUpdate(float deltaTime);
	void Render();
	void Run();
	SFGE::Window* GetWindow(){
		return &m_window;
	}
private:
	SFGE::Window m_window;
	Map map;

};