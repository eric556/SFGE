#include <SFML/Graphics.hpp>
#include "BasicGame.h"

int main(){
	BasicGame game("Basic Game", sf::Vector2u(800, 600));
	game.Run();
	return 0;
}