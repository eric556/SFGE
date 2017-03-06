#include "Tile.h"

Tile::Tile(float x, float y, float width, float height, sf::Color color){
	this->m_position.x = x;
	this->m_position.y = y;
	m_shape.setPosition(this->m_position);
	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setFillColor(color);
	m_shape.setOutlineColor(sf::Color(255 - color.r, 255 - color.g, 255 - color.b));
	m_shape.setOutlineThickness(0.9f);
	this->m_isOpen = true;
}

void Tile::Draw(SFGE::Window& window){
	window.Draw(m_shape);
}

bool Tile::isOpen(){ 
	return this->m_isOpen;
}

void Tile::setOpen(bool open){ 
	m_isOpen = open; 
}