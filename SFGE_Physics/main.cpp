#pragma once
#include <SFML/Graphics.hpp>
#include "Vector3.h"
//#include "Particle.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	SFGE::Physics::Math::Vector3f vect(0,0,0);
	std::cout << vect.to_str();
	SFGE::Physics::Math::Vector3f vect2(1, 1, 1);
	vect += vect2;
	std::cout << vect2.to_str();
	//SFGE::Physics::Components::Particle part;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
		  if (event.type == sf::Event::Closed)
		    window.close();
		}
		
		window.clear();
		window.display();
	}
	return 0;
}