#include<SFML\Graphics.hpp>
#include <Window.h>
#include<vector>
#include<iostream>

class Cactus{
public:
	Cactus(sf::Texture& l_texture, int l_index);
	void Draw(SFGE::Window& l_window);
	void SetTexture(sf::Texture& l_texture);
	sf::Sprite body;
	int indexOfSpriteSheet;
};