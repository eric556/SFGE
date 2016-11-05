#include <SFML\Graphics.hpp>
#include <Window.h>

class Bird{
public:
	sf::Sprite body;
	void Update(float dt);
	void SetTexture(sf::Texture& l_texture);
	void Draw(SFGE::Window& l_window);
	Bird(sf::Texture& l_texture);
	sf::Clock animClock;
	float timeBetweenFrames;
	int currentFrame;
	sf::Vector2f vel;
	sf::FloatRect boundingBox;
private:
};