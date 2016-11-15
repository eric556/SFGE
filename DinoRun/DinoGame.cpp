#include "DinoGame.h"


DinoGame::DinoGame(std::string l_title, sf::Vector2u windowSize) : m_window(l_title, windowSize, "Resources/Keys/keys.cfg"), dino(m_window)
{
	m_window.SetClearColor(sf::Color(247, 247, 247));

	if (!groundTexture.loadFromFile("Resources/Assets/ground.png")){
		std::cout << "ground texture error\n";
	}
	if (!cloudTexture.loadFromFile("Resources/Assets/cloud.png")){
		std::cout << "cloud texture error\n";
	}
	if (!cactusTextures[0].loadFromFile("Resources/Assets/Cactus/cactusbig.png")){

	}
	if (!cactusTextures[1].loadFromFile("Resources/Assets/Cactus/cactussmall.png")){

	}
	if (!cactusTextures[2].loadFromFile("Resources/Assets/Cactus/cactusbigfour.png")){

	}
	if (!moonTexture.loadFromFile("Resources/Assets/moon.png")){

	}
	if (!sunTexture.loadFromFile("Resources/Assets/sun.png")){

	}
	if (!dinoTexture.loadFromFile("Resources/Assets/dino.png")){

	}
	if (!font.loadFromFile("Resources/Assets/PressStart2P.ttf")){

	}
	if (!birdTexture.loadFromFile("Resources/Assets/Bird.png")){

	}
	InvertTextures();
	inverted = false;
	ground1.setTexture(groundTexture);
	ground1.setPosition(sf::Vector2f(0, 200));
	ground2.setTexture(groundTexture);
	ground2.setPosition(sf::Vector2f(1204, 200));
	cloudSpawnClock.restart();
	cactusSpawnClock.restart();
	dayNightClock.restart();
	srand(time(NULL));
	cloudSpawnTime = 5 + (rand() % (int)(10 - 5 + 1));
	cactusSpawnTime = 1 + (rand() % (int)(3 - 1 + 1));
	spawnTime = 1 + (rand() % (int)(3 - 1 + 1));
	speed = 300;
	sun.setTexture(sunTexture);
	sun.setPosition(512, 200 - 32);
	moon.setTexture(moonTexture);
	moon.setPosition(512, 200 - 32);
	sunMoonVel = sf::Vector2f(-5, -5);
	dino.SetTexture(dinoTexture);
	dino.body.setPosition(0, 164);
	dino.timeBetweenFrames = .05;
	scoreText.setFont(font);
	scoreText.setString("0000");
	scoreText.setCharacterSize(12);
	scoreText.setColor(sf::Color(83, 83, 83));
	gameOverText.setFont(font);
	gameOverText.setColor(sf::Color(83, 83, 83));
	gameOverText.setCharacterSize(24);
	gameOverText.setString("GAME OVER");
	gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2, gameOverText.getGlobalBounds().height / 2);
	gameOverText.setPosition(512 / 2, 288 / 2);
	m_window.GetEventManager()->AddCallback("Retry", &DinoGame::Retry, this);
	keepPlaying = false;
	spawnClock.restart();
}


DinoGame::~DinoGame()
{
}

void DinoGame::Update(){
	this->m_window.Update();

	if (dino.dead == false){
		GroundUpdate();
		CloudUpdate();
		Spawner();
		CactusUpdate();
		BirdUpdate();
		dino.Update(GetElapsed(), cactus, birds);
		TimeUpdate();
		score += .2f;
		speed += .08f;
		scoreText.setString(std::to_string((int)score));
		scoreText.setPosition(512 - scoreText.getGlobalBounds().width, 50);
	}
	else{
		if (dino.deathClock.getElapsedTime().asSeconds() > 2 && keepPlaying == true){
			cactus.clear();
			birds.clear();
			score = 0;
			speed = 300;
			cactusSpawnTime = 1 + (rand() % (int)(3 - 1 + 1));
			if (inverted){
				moon.setPosition(512, 200 - 32);
			}
			else{
				sun.setPosition(512, 200 - 32);
			}
			sunMoonVel = sf::Vector2f(-5, -5);
			dino.dead = false;
			keepPlaying = false;
		}
	}
}

void DinoGame::Render(){
	m_window.BeginDraw();
	m_window.Draw(sun);
	m_window.Draw(moon);
	for (int i = 0; i < clouds.size(); i++){
		m_window.Draw(clouds[i]);
	}
	m_window.Draw(ground1);
	m_window.Draw(ground2);
	for (int i = 0; i < cactus.size(); i++){
		cactus[i].Draw(m_window);
		sf::RectangleShape r(sf::Vector2f(cactus[i].body.getGlobalBounds().width - 20, cactus[i].body.getGlobalBounds().height - 10));
		r.setPosition(cactus[i].body.getPosition().x + 10, cactus[i].body.getPosition().y + 10);
		r.setFillColor(sf::Color::Transparent);
		r.setOutlineThickness(1);
		r.setOutlineColor(sf::Color::Red);
		//m_window.Draw(r);
	}
	dino.Draw(m_window);
	m_window.Draw(scoreText);
	if (dino.dead){
		m_window.Draw(gameOverText);
	}
	for (Bird b : birds){
		b.Draw(m_window);
	}
	m_window.EndDraw();
}

void DinoGame::Run(){
	this->RestartClock();
	while (!this->GetWindow()->IsDone()){
		this->Update();
		this->Render();
		this->RestartClock();
	}
}

void DinoGame::GroundUpdate(){
	if (ground1.getPosition().x > -1204){
		ground1.move(-speed * GetElapsed(), 0);
	}
	else{
		ground1.setPosition(ground2.getPosition().x + 1204, ground1.getPosition().y);
	}

	if (ground2.getPosition().x > -1204){
		ground2.move(-speed * GetElapsed(), 0);
	}
	else{
		ground2.setPosition(ground1.getPosition().x + 1204, ground2.getPosition().y);
	}
}

void DinoGame::CloudUpdate(){
	//spawn the clouds with a timer
	if (cloudSpawnClock.getElapsedTime().asSeconds() > cloudSpawnTime){
		sf::Sprite c;
		c.setTexture(cloudTexture);
		c.setPosition(sf::Vector2f(512, 100 + (rand() % (int)(150 - 100 + 1))));
		clouds.push_back(c);
		cloudSpawnTime = 5 + (rand() % (int)(10 - 5 + 1));
		cloudSpawnClock.restart();
	}

	for (int i = 0; i < clouds.size(); i++){
		if (clouds[i].getPosition().x < -46){
			clouds.erase(clouds.begin() + i);
		}
		clouds[i].move(-40 * GetElapsed(), 0);
	}

}

void DinoGame::CactusUpdate(){
	for (int i = 0; i < cactus.size(); i++){
		if (cactus[i].body.getPosition().x < -cactus[i].body.getGlobalBounds().width){
			cactus.erase(cactus.begin() + i);
		}
		else{
			cactus[i].body.move(-speed * GetElapsed(), 0);
			if (inverted){
				cactus[i].SetTexture(cactusTexturesInverse[cactus[i].indexOfSpriteSheet]);
			}
			else{
				cactus[i].SetTexture(cactusTextures[cactus[i].indexOfSpriteSheet]);
			}
		}
	}
}

void DinoGame::InvertTime(){

	if (inverted){
		m_window.SetClearColor(sf::Color(247, 247, 247));
		ground1.setTexture(groundTexture);
		ground2.setTexture(groundTexture);
		dino.SetTexture(dinoTexture);
		for (Bird b : birds){
			b.SetTexture(birdTexture);
		}
		for (sf::Sprite c : clouds){
			c.setTexture(cloudTexture);
		}
		for (Cactus c : cactus){
			c.body.setTexture(cactusTextures[c.indexOfSpriteSheet]);
		}
		scoreText.setColor(sf::Color(83, 83, 83));
		gameOverText.setColor(sf::Color(83, 83, 83));
		inverted = false;
	}
	else{
		m_window.SetClearColor(sf::Color::Black);
		ground1.setTexture(groundTextureInverse);
		ground2.setTexture(groundTextureInverse);
		dino.SetTexture(dinoTextureInverse);
		for (Bird b : birds){
			b.SetTexture(birdTextureInverse);
		}
		for (sf::Sprite c : clouds){
			c.setTexture(cloudTextureInverse);
		}
		for (Cactus c : cactus){
			c.SetTexture(cactusTexturesInverse[c.indexOfSpriteSheet]);
		}
		scoreText.setColor(sf::Color(247, 247, 247));
		gameOverText.setColor(sf::Color(247, 247, 247));
		inverted = true;
	}


}

void DinoGame::TimeUpdate(){
	if (sun.getPosition().x < -(int)(sun.getTexture()->getSize().x)){
		sun.setPosition(512, 200 - 32);
		sunMoonVel = sf::Vector2f(-5, -5);
		InvertTime();
	}
	if (moon.getPosition().x < -(int)(moon.getTexture()->getSize().x)){
		moon.setPosition(512, 200 - 32);
		sunMoonVel = sf::Vector2f(-5, -5);
		InvertTime();
	}

	if (inverted){
		moon.move(sunMoonVel * GetElapsed());
		sunMoonVel.y += 0.0014f;
	}
	else{
		sun.move(sunMoonVel * GetElapsed());
		sunMoonVel.y += 0.0014f;
	}
}

void DinoGame::InvertTextures(){
	sf::Image g1 = groundTexture.copyToImage();
	for (int y = 0; y < groundTexture.getSize().y; y++){
		for (int x = 0; x < groundTexture.getSize().x; x++){
			if (g1.getPixel(x, y) == sf::Color(247, 247, 247)){
				g1.setPixel(x, y, sf::Color::Black);
			}
			else if (g1.getPixel(x, y) == sf::Color(83, 83, 83)){
				g1.setPixel(x, y, sf::Color::White);
			}
		}
	}
	groundTextureInverse.loadFromImage(g1);

	sf::Image c = cloudTexture.copyToImage();
	for (int y = 0; y < cloudTexture.getSize().y; y++){
		for (int x = 0; x < cloudTexture.getSize().x; x++){
			if (c.getPixel(x, y) == sf::Color(247, 247, 247)){
				c.setPixel(x, y, sf::Color::Black);
			}
			else if (c.getPixel(x, y) == sf::Color(83, 83, 83)){
				c.setPixel(x, y, sf::Color::White);
			}
		}
	}
	cloudTextureInverse.loadFromImage(c);

	for (int i = 0; i < 3; i++){
		sf::Image cact = cactusTextures[i].copyToImage();
		for (int y = 0; y < cactusTextures[i].getSize().y; y++){
			for (int x = 0; x < cactusTextures[i].getSize().x; x++){
				if (cact.getPixel(x, y) == sf::Color(247, 247, 247)){
					cact.setPixel(x, y, sf::Color::Black);
				}
				else if (cact.getPixel(x, y) == sf::Color(83, 83, 83)){
					cact.setPixel(x, y, sf::Color::White);
				}
			}
		}
		cactusTexturesInverse[i].loadFromImage(cact);
	}

	sf::Image d = dinoTexture.copyToImage();
	for (int y = 0; y < dinoTexture.getSize().y; y++){
		for (int x = 0; x < dinoTexture.getSize().x; x++){
			if (d.getPixel(x, y) == sf::Color(247, 247, 247)){
				d.setPixel(x, y, sf::Color::Black);
			}
			else if (d.getPixel(x, y) == sf::Color(83, 83, 83)){
				d.setPixel(x, y, sf::Color::White);
			}
		}
	}
	dinoTextureInverse.loadFromImage(d);

	sf::Image bird = birdTexture.copyToImage();
	for (int y = 0; y < birdTexture.getSize().y; y++){
		for (int x = 0; x < birdTexture.getSize().x; x++){
			if (bird.getPixel(x, y) == sf::Color(247, 247, 247)){
				bird.setPixel(x, y, sf::Color::Black);
			}
			else if (bird.getPixel(x, y) == sf::Color(83, 83, 83)){
				bird.setPixel(x, y, sf::Color::White);
			}
		}
	}
	birdTextureInverse.loadFromImage(bird);
}

void DinoGame::Retry(SFGE::EventDetails* l_details){
	std::cout << l_details->m_keyCode;
	keepPlaying = true;
}

void DinoGame::BirdUpdate(){
	for (int i = 0; i < birds.size(); i++){
		if (birds[i].body.getPosition().x < -birds[i].body.getGlobalBounds().width){
			birds.erase(birds.begin() + i);
		}
		else{
			birds[i].body.move(-speed * GetElapsed(), 0);
			birds[i].Update(GetElapsed());
			if (inverted){
				birds[i].SetTexture(birdTextureInverse);
			}
			else{
				birds[i].SetTexture(birdTexture);
			}
		}
	}
}

void DinoGame::Spawner(){
	if (spawnClock.getElapsedTime().asSeconds() > spawnTime){
		int randomEntity = rand() % 100;
		if (randomEntity >= 40){
			int randomTextureIndex = rand() % 3;
			Cactus c(cactusTextures[randomTextureIndex], randomTextureIndex);
			cactus.push_back(c);
			spawnTime = 2 + (rand() % (int)(3 - 2 + 1)) - (score / 1000);
			spawnClock.restart();
		}
		else if (randomEntity < 40){
			Bird b(birdTexture);
			birds.push_back(b);
			spawnTime = 2 + (rand() % (int)(3 - 2 + 1)) - (score / 1000);
			spawnClock.restart();
		}
	}
}