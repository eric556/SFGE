#include "Cactus.h"	

Cactus::Cactus(sf::Texture& l_texture, int l_index){
	body.setTexture(l_texture);
	//srand(time(NULL));
	indexOfSpriteSheet = l_index;
	if (indexOfSpriteSheet == 0){
		int randomTextureRectIndex = rand() % 3;
		body.setTextureRect(sf::IntRect(25 * randomTextureRectIndex, 0, 25, 50));
	}
	else if (indexOfSpriteSheet == 1){
		int randomTextureRectIndex = rand() % 6;
		body.setTextureRect(sf::IntRect(17 * randomTextureRectIndex, 0, 17, 35));
	}
	body.setPosition(sf::Vector2f(512, 210 - this->body.getGlobalBounds().height + 5));
}

void Cactus::Draw(SFGE::Window& l_window){
	l_window.Draw(body);
}
void Cactus::SetTexture(sf::Texture& l_texture){
	body.setTexture(l_texture);
}
