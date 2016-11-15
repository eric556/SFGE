#include <SFML/Graphics.hpp>
#include "BasicGame.h"

int main(){
	BasicGame game("SFML-OpenGL", sf::Vector2u(800, 600));
	game.Run();
	return 0;
}