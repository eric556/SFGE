#include "Pickup.h"


Pickup::Pickup(PickupType l_type, sf::Vector2i l_position, int l_radius)
{
	
	m_shape.setRadius(l_radius);
	position = l_position;
	m_shape.setPosition(position.x * m_shape.getRadius() * 2, position.y * m_shape.getRadius() * 2);
	UpdateType(l_type);
	
}


Pickup::~Pickup()
{

}

void Pickup::Render(sf::RenderWindow& window){
	window.draw(m_shape);
}
void Pickup::Update(Snake& l_player, sf::Vector2u& l_windowSize, sf::RectangleShape bounds[]){
	if (l_player.GetPosition() == position){
		l_player.IncreaseScore();
		switch (m_type)
		{
		case PickupType::Extend:
			l_player.Extend();
			break;
		case PickupType::SlowDown:
			l_player.DecreaseSpeed();
			break;
		case PickupType::SpeedUp:
			l_player.IncreaseSpeed();
			break;
		case PickupType::ShrinkArena:
			if (l_windowSize.x > 16, l_windowSize.y > 16){
				l_windowSize -= sf::Vector2u(16, 16);
			}
			for (int i = 0; i < 4; ++i){
				bounds[i].setFillColor(sf::Color(150, 0, 0));
				if (!((i + 1) % 2)){
					bounds[i].setSize(sf::Vector2f(l_windowSize.x, m_shape.getRadius() * 2));
				}
				else {
					bounds[i].setSize(sf::Vector2f(m_shape.getRadius() * 2, l_windowSize.y));
				}
				if (i < 2){
					bounds[i].setPosition(0, 0);
				}
				else {
					bounds[i].setOrigin(bounds[i].getSize());
					bounds[i].setPosition(sf::Vector2f(l_windowSize));
				}
			}
			break;
		case PickupType::ExpandArena:
			if (l_windowSize.x < 800, l_windowSize.y < 600){
				l_windowSize += sf::Vector2u(16, 16);
			}
			for (int i = 0; i < 4; ++i){
				bounds[i].setFillColor(sf::Color(150, 0, 0));
				if (!((i + 1) % 2)){
					bounds[i].setSize(sf::Vector2f(l_windowSize.x, m_shape.getRadius() * 2));
				}
				else {
					bounds[i].setSize(sf::Vector2f(m_shape.getRadius() * 2, l_windowSize.y));
				}
				if (i < 2){
					bounds[i].setPosition(0, 0);
				}
				else {
					bounds[i].setOrigin(bounds[i].getSize());
					bounds[i].setPosition(sf::Vector2f(l_windowSize));

				}
			}
			break;
		case PickupType::ExtraLife:
			l_player.IncreaseLives();
			break;
		default:
			break;
		}

		Respawn(l_windowSize);

	}
	if (m_shape.getPosition().x >= l_windowSize.x || m_shape.getPosition().y >= l_windowSize.y){
		Respawn(l_windowSize);

	}
}

void Pickup::Respawn(sf::Vector2u l_windowSize){
	std::srand(std::time(NULL));

	int maxX = (l_windowSize.x / (m_shape.getRadius() * 2)) - 3;
	int maxY = (l_windowSize.y / (m_shape.getRadius() * 2)) - 3;
	position = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	
	int chance = rand() % 100 + 1;
	if (chance < 100 && chance > 50){
		UpdateType(PickupType::Extend);
	}
	else if(chance < 50 && chance > 30){
		UpdateType(PickupType::SpeedUp);
	}
	else if(chance < 30 && chance > 10){
		UpdateType(PickupType::SlowDown);
	}
	else if(chance < 20 && chance > 5){
		UpdateType(PickupType::ShrinkArena);
	}
	else if (chance < 5 && chance > 3){
		UpdateType(PickupType::ExpandArena);
	}
	else{
		UpdateType(PickupType::ExtraLife);
	}

	m_shape.setPosition(position.x * m_shape.getRadius() * 2, position.y * m_shape.getRadius() * 2);

}

void Pickup::UpdateType(PickupType l_type){
	m_type = l_type;
	switch (l_type){
	case PickupType::ExpandArena:
		m_shape.setFillColor(sf::Color(226, 125, 8));
		break;
	case PickupType::Extend:
		m_shape.setFillColor(sf::Color::Red);
		break;
	case PickupType::ShrinkArena:
		m_shape.setFillColor(sf::Color(255-226,255-125,255-8));
		break;
	case PickupType::SlowDown:
		m_shape.setFillColor(sf::Color(255-158,255-65,255-207));
		break;
	case PickupType::SpeedUp:
		m_shape.setFillColor(sf::Color(158,65,207));

		break;
	case PickupType::Magnet:
		m_shape.setFillColor(sf::Color(239, 215, 0));
		break;
	case PickupType::ExtraLife:
		m_shape.setFillColor(sf::Color(231, 236, 19));
		break;
	default:
		break;
	}
}