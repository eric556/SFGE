#pragma once
#include <SFML/Graphics.hpp>
#include "Vector3.h"
#include "ParticleForceRegistry.h"
#include "ParticleGravity.h"
#include "ParticleDrag.h"
#include "ParticleSpring.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleUniversalGravity.h"

#define PI 3.1415926535

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Physics Engine Testing");
	SFGE::Physics::Components::Particle p(400,300,0,(41 * cos(72 * PI / 180))*10, (-41 * sin(72 * PI / 180))*10,0,0.145);
	SFGE::Physics::Generators::ParticleGravity gravity(SFGE::Physics::Math::Vector3f(0,9.81*0.1,0));
	SFGE::Physics::Generators::ParticleForceRegistry forceRegistry;
	SFGE::Physics::Generators::ParticleDrag drag(1, 1);
	std::vector<SFGE::Physics::Components::Particle> particles;

	SFGE::Physics::Generators::ParticleUniversalGravity grav(particles);
	//forceRegistry.add(&p, &gravity);
	//forceRegistry.add(&p, &drag);
  
	sf::Clock deltaClock;
	sf::CircleShape shape(10.0f);
	shape.setPosition(p.GetPosition().x, p.GetPosition().y);

	while (window.isOpen())
	{
		sf::Time dt = deltaClock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Key::Escape)
					window.close();
				else if (event.key.code == sf::Keyboard::Key::Space)
					p.addForce(SFGE::Physics::Math::Vector3f(0, -200, 0));
		}
		forceRegistry.updateForces(dt.asSeconds());
		p.Integrate(dt.asSeconds());
		shape.setPosition(p.GetPosition().x, p.GetPosition().y);
		//std::cout << p.GetPosition()->to_str() << "\n";

		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}


void initializeParticles(std::vector<SFGE::Physics::Components::Particle>& particles){
	
}