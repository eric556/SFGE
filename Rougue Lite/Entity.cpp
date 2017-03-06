#include "Entity.h"

Entity::Entity(int x, int y, float width, float height, Map& map):m_map(map){
	position.x = x;
	position.y = y;
	size.x = width;
	size.y = height;
	m_moveDirection = Direction::NONE;
	m_shape.setSize(size);
	m_shape.setFillColor(sf::Color::Red);

}

void Entity::update(float dt){

}