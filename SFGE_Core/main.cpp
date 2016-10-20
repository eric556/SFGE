
#include <iostream> 
#include "TestGame.h"
#include "DinoGame.h"
#include "PTestGame.h"
#include <SFML\Graphics.hpp>
int main()
{
	
	//TestGame game2("Test",sf::Vector2u(800,600));
	//DinoGame game2("DinoGame", sf::Vector2u(512, 288));
	PTestGame game2("Physics Test", sf::Vector2u(800, 600));
	game2.Run();
	return 0;
}

