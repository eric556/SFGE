#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Matrix.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	SFGE::Physics::Math::Vector2f vec(1, 2);
	SFGE::Physics::Math::Matrix2i mat(4, 4);
	SFGE::Physics::Math::Matrix2i mat2(5, 5);
	mat.SetValue(1, 1, 5);
	mat2.SetValue(1, 1, 5);
	//std::cout << mat.to_str() << "\n";
	vec.normalize();
	//std::cout << vec.to_str() << "\n";
	std::cout << (mat - mat2).to_str() << "\n";

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
		  if (event.type == sf::Event::Closed)
		    window.close();
		}
		
		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}