#include "Cactus.h"	

Cactus::Cactus(sf::Texture& l_texture, int l_index){
	body.setTexture(l_texture);
	indexOfSpriteSheet = l_index;
}

void Cactus::Draw(SFGE::Window& l_window){
	l_window.Draw(body);
}
void Cactus::SetTexture(sf::Texture& l_texture){
	body.setTexture(l_texture);
}