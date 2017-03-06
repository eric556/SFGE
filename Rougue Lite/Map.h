#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <Window.h>
#include "Tile.h"


class Map{
public:
	Map(int width, int height, int tileWidth, int tileHeight);
	void Draw(SFGE::Window& window);
	Tile getTile(int x, int y);
	bool isTileOpen(int x, int y);
private:
	std::vector<std::vector<Tile>> spaces;
	int amountOfTilesX;
	int amountOfTileY;
};