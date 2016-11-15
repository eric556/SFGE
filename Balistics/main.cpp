#include <SFML/Graphics.hpp>
#include "BasicGame.h"

int main(int argc, char** argv){
	glutInit(&argc, argv);
	BasicGame game("Ballistics Test", sf::Vector2u(1920, 1080));
	game.Run();
	return 0;
}