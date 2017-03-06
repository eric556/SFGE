#include <SFML/Graphics.hpp>
#include "RougeLite.h"

int main(){
	RougeLite game("Basic Game", sf::Vector2u(800, 600));
	game.Run();
	return 0;
}