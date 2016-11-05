#include <SFML/Graphics.hpp>
#include "DinoGame.h"

int main(){
	DinoGame game("DinoGame", sf::Vector2u(512, 288));
	game.Run();
	return 0;
}