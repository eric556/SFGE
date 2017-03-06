#include "Map.h"

Map::Map(int width, int height, int tileWidth, int tileHeight){
	this->amountOfTilesX = width / tileWidth;
	this->amountOfTileY = height / tileHeight;
	for (int y = 0; y < height*tileHeight; y += tileHeight){
		std::vector<Tile> temp;
		for (int x = 0; x < width*tileWidth; x += tileWidth){
			temp.push_back(Tile(x, y, tileWidth, tileHeight, sf::Color::Red));
		}
		spaces.push_back(temp);
	}
}

void Map::Draw(SFGE::Window& window){
	for each (std::vector<Tile> temp in spaces){
		for each(Tile t in temp){
			t.Draw(window);
		}
	}
}

Tile Map::getTile(int x, int y){
	return spaces[x][y];
}

bool Map::isTileOpen(int x, int y){
	return getTile(x, y).isOpen();
}