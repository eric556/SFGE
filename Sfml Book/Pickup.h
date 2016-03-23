#pragma once
#include "Snake.h"
#include <stdlib.h>
#include <time.h>

enum PickupType{SpeedUp,SlowDown,Extend,ShrinkArena,ExpandArena,Magnet,ExtraLife};

class Pickup
{
public:
	Pickup(PickupType l_type, sf::Vector2i l_position, int l_radius);
	~Pickup();

	void Update(Snake& l_player, sf::Vector2u& l_windowSize, sf::RectangleShape bounds[]);
	void Render(sf::RenderWindow& l_window);
	void SetType(PickupType l_type){ m_type = l_type; }
	sf::CircleShape& GetShape(){ return m_shape; }
private:
	void UpdateType(PickupType l_type);
	PickupType m_type;
	sf::CircleShape m_shape;
	sf::Vector2i position;
	void Respawn(sf::Vector2u l_windowSize);
	
};

