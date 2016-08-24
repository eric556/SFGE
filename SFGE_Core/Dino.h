#pragma once
#include "Window.h"
#include <SFML\Graphics.hpp>
#include "Cactus.h"
#include "Bird.h"

enum AnimState { RUNNING, JUMPING, DUCKING };

class Dino{
public:
	Dino(SFGE::Window& l_window);
	void SetTexture(sf::Texture& l_texture);
	void Draw(SFGE::Window& l_window);
	void Update(float dt, std::vector<Cactus>l_cacti, std::vector<Bird> l_birds);
	sf::Sprite body;
	sf::Clock animClock;
	float timeBetweenFrames;
	int currentFrame;
	bool dead;
	sf::Clock deathClock;
	AnimState animState;
private:
	bool jumping;
	bool grounded;
	void Jump(SFGE::EventDetails* details);
	void Duck(SFGE::EventDetails* details);
	sf::Clock jumpClock;
	sf::Vector2f vel;
	sf::FloatRect boundingBox;
	float gravity;
};