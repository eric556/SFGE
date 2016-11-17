#include <SFML/Graphics.hpp>
#include "BasicGame.h"

int main(int argc, char** argv){
	glutInit(&argc, argv);
	BasicGame game("Basic Game", sf::Vector2u(800, 600));
	game.Run();
	return 0;
}