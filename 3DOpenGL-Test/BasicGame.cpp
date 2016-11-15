#include "BasicGame.h"

BasicGame::BasicGame(std::string title, sf::Vector2u windowSize):m_window(title,windowSize,"Resources/Keys/keys.cfg"){
	//prepare OpenGL surface for HSR
	glClearDepth(1.f);
	glClearColor(0.3f, 0.3f, 0.3f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	//// Setup a perspective projection & Camera position
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar
	rotate = true;
	m_window.GetEventManager()->AddCallback("Rotate_toggle", &BasicGame::Rotate_toggle, this);
	clock.restart();
}

void BasicGame::Rotate_toggle(SFGE::EventDetails* details){
	rotate != rotate;
	std::cout << "Test\n";
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
	//Prepare for drawing
	// Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Apply some transformations for the cube
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.f, 0.f, -200.f);

	if (rotate){
		angle = clock.getElapsedTime().asSeconds();
	}
	else{
		angle = 0;
	}
	glRotatef(angle * 50, 1.f, 0.f, 0.f);
	glRotatef(angle * 30, 0.f, 1.f, 0.f);
	glRotatef(angle * 90, 0.f, 0.f, 1.f);


	
	//Draw a cube
	glBegin(GL_QUADS);//draw some squares
	glColor3i(0, 1, 1);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glVertex3f(50.f, -50.f, -50.f);

	glColor3f(0, 0, 1);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(50.f, -50.f, 50.f);

	glColor3f(1, 0, 1);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, -50.f, 50.f);

	glColor3f(0, 1, 0);
	glVertex3f(50.f, -50.f, -50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glVertex3f(50.f, 50.f, 50.f);
	glVertex3f(50.f, -50.f, 50.f);

	glColor3f(1, 1, 0);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(50.f, -50.f, -50.f);
	glVertex3f(50.f, -50.f, 50.f);

	glColor3f(1, 0, 0);
	glVertex3f(-50.f, 50.f, 50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f(50.f, 50.f, -50.f);
	glVertex3f(50.f, 50.f, 50.f);

	glEnd();

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