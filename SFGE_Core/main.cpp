
#include <iostream> 
#include "TestGame.h"
#include "DinoGame.h"
#include <SFML\Graphics.hpp>
int main()
{
	
	//TestGame game("Test",sf::Vector2u(800,600));
	DinoGame game2("DinoGame", sf::Vector2u(512, 288));
	game2.Run();
	return 0;
}

