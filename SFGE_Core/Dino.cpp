#include "Dino.h"

Dino::Dino(SFGE::Window& l_window){
	jumping = false;
	grounded = true;
	l_window.GetEventManager()->AddCallback("Jump", &Dino::Jump, this);
	vel = sf::Vector2f(0, 0);
	gravity = 30.0f;
	dead = false;
}

void Dino::Draw(SFGE::Window& l_window){
	l_window.Draw(body);
}

void Dino::Update(float dt, std::vector<Cactus>l_cacti){
	
	if (dead == true){
		vel.x = 0;
		vel.y = 0;
	}

	body.move(vel * dt);
	

	if (body.getPosition().y < 164){
		body.setTextureRect(sf::IntRect(0, 0, 44, 54));
		vel.y += gravity;
	}
	else{
		if (animClock.getElapsedTime().asSeconds() > timeBetweenFrames){
			if (currentFrame == 2){
				currentFrame = 0;
			}
			else{
				currentFrame++;
			}
			body.setTextureRect(sf::IntRect(44 * currentFrame, 0, 44, 54));
			animClock.restart();
		}
		body.setPosition(body.getPosition().x, 164);
		//vel.y = 0;
	}

	for (Cactus cactus : l_cacti){
		sf::FloatRect bb = cactus.body.getGlobalBounds();
		if (body.getGlobalBounds().intersects(sf::FloatRect(bb.left + 10,bb.top + 15,bb.width-10,bb.height-15))){
			dead = true;
			deathClock.restart();
		}
	}



}

void Dino::SetTexture(sf::Texture& l_texture){
	body.setTexture(l_texture);
	body.setTextureRect(sf::IntRect(0, 0, 44, 54));
	animClock.restart();
	currentFrame = 0;
} 

void Dino::Jump(SFGE::EventDetails* details){
	if (body.getPosition().y >= 164){
		vel.y = -500;
	}
}