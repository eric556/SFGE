#pragma once
#include <SFML/Graphics.hpp>
#include "Vector3.h"
#include "ParticleForceRegistry.h"
#include "ParticleGravity.h"
#include "ParticleDrag.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Engine Testing");
	SFGE::Physics::Components::Particle p(0,0,0,0,0,0,10);
	SFGE::Physics::Generators::ParticleGravity gravity(SFGE::Physics::Math::Vector3f(2,2,0));
	SFGE::Physics::Generators::ParticleDrag drag(0.47f, 0.47f);
	SFGE::Physics::Generators::ParticleForceRegistry forceRegistry;
	forceRegistry.add(&p, &gravity);
	forceRegistry.add(&p, &drag);

	sf::Clock deltaClock;
	sf::CircleShape shape(10.0f);
	shape.setPosition(p.GetPosition()->x, p.GetPosition()->y);

	while (window.isOpen())
	{
		sf::Time dt = deltaClock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
		  if (event.type == sf::Event::Closed)
		    window.close();
		}
		forceRegistry.updateForces(dt.asSeconds());
		p.Integrate(dt.asSeconds());
		shape.setPosition(p.GetPosition()->x, p.GetPosition()->y);
		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}