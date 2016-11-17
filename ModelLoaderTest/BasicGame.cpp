#include "BasicGame.h"

BasicGame::BasicGame(std::string title, sf::Vector2u windowSize):m_window(title,windowSize,"Resources/Keys/keys.cfg"){

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glViewport(0, 0, windowSize.x, windowSize.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)windowSize.x / (GLfloat)windowSize.y, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	car.LoadObject("Resources/car.obj");
}

BasicGame::~BasicGame(){
}

void BasicGame::Update(){
	m_window.Update();
}

void BasicGame::FixedUpdate(float deltaTime){

}

void BasicGame::Render(){
	m_window.BeginDraw();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	car.Render();
	glutSwapBuffers();
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