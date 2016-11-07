#include <Game.h>
#include <EventManager.h>
#include "Particle.h"

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
	sf::Color particleColor;
	int ColorSpeed;
	int currentColor;
	SFGE::Window m_window;
	std::vector<sf::CircleShape> particleShapes;
	std::vector<Particle> particles;
	void InitializeParticalSim();
	void RunParticalSim(float deltaTime);
	void DrawParticlSim();
};