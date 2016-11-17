#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include "Game.h"
#include "EventManager.h"
#include <SFML/OpenGL.hpp>
#include <glut.h>

class BasicGame : public SFGE::Game{
public:
	BasicGame(std::string title, sf::Vector2u windowSize);
	~BasicGame();
	void Update();
	void FixedUpdate(float deltaTime);
	void Render();
	void Run();
	SFGE::Window* GetWindow(){
		return &m_window;
	}
private:
	SFGE::Window m_window;

};