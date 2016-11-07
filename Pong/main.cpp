#include <SFML/Graphics.hpp>
#include "PongGame.h"

int main(){
	PongGame game("Pong!", sf::Vector2u(800, 600));
	game.Run();
	return 0;
}