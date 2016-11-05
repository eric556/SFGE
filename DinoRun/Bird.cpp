#include "Bird.h"

Bird::Bird(sf::Texture& l_texture){
	animClock.restart();
	timeBetweenFrames = 0.1;
	currentFrame = 0;
	int random = rand() % 2;
	if (random == 0){
		body.setPosition(sf::Vector2f(512, 164 - 25));
	}
	else{
		body.setPosition(sf::Vector2f(512, 164));
	}
	body.setTexture(l_texture);
	body.setTextureRect(sf::IntRect(0, 0, 46, 42));
	//boundingBox = sf::FloatRect(body.getGlobalBounds().left, body.getGlobalBounds().top, body.getGlobalBounds().width, body.getGlobalBounds().height);
}

void Bird::SetTexture(sf::Texture& l_texture){
	body.setTexture(l_texture);
}

void Bird::Update(float dt){
	if (animClock.getElapsedTime().asSeconds() > timeBetweenFrames){
		if (currentFrame == 1){
			currentFrame = 0;
		}
		else{
			currentFrame++;
		}
		body.setTextureRect(sf::IntRect(46 * currentFrame, 0, 46, 42));
		animClock.restart();
	}
	boundingBox = sf::FloatRect(body.getGlobalBounds().left, body.getGlobalBounds().top + 10, body.getGlobalBounds().width, body.getGlobalBounds().height - 10);
}

void Bird::Draw(SFGE::Window& l_window){
	l_window.Draw(body);
	sf::RectangleShape r(sf::Vector2f(boundingBox.width, boundingBox.height - 10));
	r.setPosition(body.getPosition().x, body.getPosition().y + 10);
	r.setFillColor(sf::Color::Transparent);
	r.setOutlineThickness(1);
	r.setOutlineColor(sf::Color::Red);
	//l_window.Draw(r);
}