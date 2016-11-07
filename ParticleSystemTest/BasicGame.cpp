#include "BasicGame.h"

void BasicGame::InitializeParticalSim(){
	particleColor = sf::Color(254, 254, 254, 255);

	for (int i = 0; i < 1630; i++){
		sf::CircleShape shape(1);
		Particle p;
		p.Initialize();
		p.mass = rand() % 5 + 1;
		shape.setRadius(p.mass);
		particleColor.r = particleColor.r / p.mass;
		shape.setFillColor(particleColor);
		particles.push_back(p);
		shape.setPosition(p.position.x, p.position.y);
		particleShapes.push_back(shape);
	}
	Particle bigmofo;
	bigmofo.Initialize();
	bigmofo.mass = 5;
	sf::CircleShape shape(bigmofo.mass);
	shape.setFillColor(sf::Color(106, 140, 233, 100));
	shape.setPosition(bigmofo.position.x, bigmofo.position.y);
	particles.push_back(bigmofo);
	particleShapes.push_back(shape);
}

void BasicGame::RunParticalSim(float deltaTime){
	particleColor.r -= 3;
	
	for (int i = 0; i < particles.size(); i++){
		Particle *particle = &particles[i];
		SFGE::Math::vector2::Vector2f force(0, 0);
		for (int j = 0; j < particles.size(); j++){
			Particle* other = &particles[j];
			if (particle != other){
				force += particle->ComputeGravitationalAttractions(other);
			}
		}
		particle->IntegrateForce(force, deltaTime);
		particleShapes[i].setPosition(particle->position.x, particle->position.y);
		particleShapes[i].setFillColor(particleColor);
	}
}

void BasicGame::DrawParticlSim(){
	for (int i = 0; i < particleShapes.size(); i++){
		m_window.Draw(particleShapes[i]);
	}
}

BasicGame::BasicGame(std::string title, sf::Vector2u windowSize):m_window(title,windowSize,"Resources/Keys/keys.cfg"){
	m_window.SetClearColor(sf::Color(125, 125, 125));
	InitializeParticalSim();
}

BasicGame::~BasicGame(){
}

void BasicGame::Update(){
	m_window.Update();
	//RunParticalSim();
}

void BasicGame::FixedUpdate(float deltaTime){
	RunParticalSim(deltaTime);
}

void BasicGame::Render(){
	m_window.BeginDraw();
	DrawParticlSim();
	m_window.EndDraw();
}

void BasicGame::Run(){
	sf::Clock fixedUpdateClock;
	fixedUpdateClock.restart();
	this->RestartClock();
	int c = 0;
	while (!this->GetWindow()->IsDone())
	{
		this->Update();
		if (fixedUpdateClock.getElapsedTime().asSeconds() >= (1.0f / 60.0f)){
			this->FixedUpdate(fixedUpdateClock.restart().asSeconds());
		}
		this->Render();
		this->RestartClock();
	}
}