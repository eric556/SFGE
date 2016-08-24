#pragma once
#include "Game.h"
#include "EventManager.h"
#include "Dino.h"
#include <vector>

class DinoGame : public SFGE::Game
{
public:
	DinoGame(std::string l_title, sf::Vector2u windowSize);
	~DinoGame();
	void Update();
	void Render();
	void Run();
	SFGE::Window* GetWindow(){
		return &m_window;
	}
private:
	SFGE::Window m_window;
	sf::Sprite ground1;
	sf::Sprite ground2;
	sf::Texture groundTexture;
	sf::Texture groundTextureInverse;
	sf::Texture cloudTexture;
	sf::Texture cloudTextureInverse;
	sf::Clock cloudSpawnClock;
	std::vector<sf::Sprite> clouds;
	int cloudSpawnTime;
	sf::Clock cactusSpawnClock;
	sf::Texture cactusTextures[3];
	sf::Texture cactusTexturesInverse[3];
	std::vector<Cactus> cactus;
	float cactusSpawnTime;
	float speed;
	bool inverted;
	sf::Clock dayNightClock;
	sf::Texture moonTexture;
	sf::Sprite moon;
	sf::Texture sunTexture;
	sf::Sprite sun;
	sf::Vector2f sunMoonVel;
	sf::Texture dinoTexture;
	sf::Texture dinoTextureInverse;
	Dino dino;
	sf::Font font;
	sf::Text scoreText;
	sf::Text gameOverText;
	float score;
	bool keepPlaying;
	sf::Texture birdTexture;
	sf::Texture birdTextureInverse;
	std::vector<Bird> birds;
	sf::Clock spawnClock;
	float spawnTime;

	void GroundUpdate();
	void CloudUpdate();
	void CactusUpdate();
	void TimeUpdate();
	void BirdUpdate();
	void Spawner();
	void InvertTime();
	void InvertTextures();
	void Retry(SFGE::EventDetails* l_details);
};

