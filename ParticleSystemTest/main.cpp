#include <SFML/Graphics.hpp>
#include "BasicGame.h"

int main(){
	BasicGame game("Basic Game", sf::Vector2u(1920, 1080));
	game.Run();
	return 0;
}