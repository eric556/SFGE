#include "BasicGame.h"


BasicGame::BasicGame(std::string title, sf::Vector2u windowSize):m_window(title,windowSize,"Resources/Keys/keys.cfg") {
	font.loadFromFile("Resources/Fonts/Quivira.otf");
	m_currentShotText.setFont(font);
	m_currentShotText.setString("Current Shot Type: ");
	m_currentShotText.setCharacterSize(12);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//prepare OpenGL surface for HSR
	glClearDepth(1.f);
	glClearColor(0.3f, 0.3f, 0.3f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	//// Setup a perspective projection & Camera position
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.f, 1.7f, 1.f, 300.0f);//fov, aspect, zNear, zFar
	currentShotType = ARTILLERY;

	for (auto &shot : ammo){
		shot.type = UNUSED;
	}
	m_window.GetEventManager()->AddCallback("Fire_Proj", &BasicGame::FireProj, this);
	m_window.GetEventManager()->AddCallback("Projectile_toggle_a", &BasicGame::ToggleProj, this);
	m_window.GetEventManager()->AddCallback("Projectile_toggle_b", &BasicGame::ToggleProj, this);
	m_window.GetEventManager()->AddCallback("Projectile_toggle_c", &BasicGame::ToggleProj, this);
	m_window.GetEventManager()->AddCallback("Projectile_toggle_d", &BasicGame::ToggleProj, this);
}

void BasicGame::FireProj(SFGE::EventDetails* details){
	std::cout << "fired\n";
	std::cout << details->m_name;
	fire();
}

void BasicGame::ToggleProj(SFGE::EventDetails* details){
	std::cout << "setting projectile\n"; 
	std::cout << details->m_keyCode;
	switch (details->m_keyCode){
	case sf::Keyboard::Key::A:
		std::cout << "setting artillery\n";
		currentShotType = ARTILLERY;
		break;
	case sf::Keyboard::Key::S:
		std::cout << "setting pistol\n";
		currentShotType = PISTOL;
		break;
	case sf::Keyboard::Key::D:
		std::cout << "setting fireball\n";
		currentShotType = FIREBALL;
		break;
	case sf::Keyboard::Key::F:
		std::cout << "setting laser\n";
		currentShotType = LASER;
		break;
	}
}

void BasicGame::fire(){

	AmmoRound *shot = &ammo[0];
	int countUsed = 0;
	for (auto &s : ammo){
		if (s.type == UNUSED){
			shot = &s;
			break;
		}
		else{
			countUsed++;
		}
	}

	if (countUsed == ammoRounds) return;

	// Set the properties of the particle
	switch (currentShotType)
	{
	case PISTOL: 
		shot->particle.SetMass(2.0f); // 2.0kg
		shot->particle.SetVelocity(0.0f, 0.0f, 35.0f); // 35m/s
		shot->particle.SetAcceleration(0.0f, -1.0f, 0.0f);
		shot->particle.SetDampning(0.99f);
		break;

	case ARTILLERY:
		shot->particle.SetMass(200.0f); // 200.0kg
		shot->particle.SetVelocity(0.0f, 30.0f, 40.0f); // 50m/s
		shot->particle.SetAcceleration(0.0f, -20.0f, 0.0f);
		shot->particle.SetDampning(0.99f);
		break;

	case FIREBALL:
		shot->particle.SetMass(1.0f); // 1.0kg - mostly blast damage
		shot->particle.SetVelocity(0.0f, 0.0f, 10.0f); // 5m/s
		shot->particle.SetAcceleration(0.0f, 0.6f, 0.0f); // Floats up
		shot->particle.SetDampning(0.9f);
		break;

	case LASER:
		// Note that this is the kind of laser bolt seen in films,
		// not a realistic laser beam!
		shot->particle.SetMass(0.1f); // 0.1kg - almost no weight
		shot->particle.SetVelocity(0.0f, 0.0f, 100.0f); // 100m/s
		shot->particle.SetAcceleration(0.0f, 0.0f, 0.0f); // No gravity
		shot->particle.SetDampning(0.99f);
		break;
	}

	// Set the data common to all particle types
	shot->particle.SetPosition(0.0f, 1.5f, 0.0f);
	shot->startTime = GetElapsed();
	shot->type = currentShotType;

	// Clear the force accumulators
	shot->particle.ClearAccum();
}

BasicGame::~BasicGame(){
}

void BasicGame::Update(){
	m_window.Update();
}

void BasicGame::FixedUpdate(float deltaTime){
	for (auto &shot : ammo){
		if (shot.type != UNUSED){
			shot.particle.Integrate(deltaTime);
			if (shot.particle.GetPosition()->y < 0.0f || shot.particle.GetPosition()->z > 200.0f){
				shot.type = UNUSED;
				numUnused++;
			}
		}
	}
}

void BasicGame::Render(){
	m_window.BeginDraw();
	// Clear the viewport and set the camera direction
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(-25.0, 8.0, 5.0, 0.0, 5.0, 22.0, 0.0, 1.0, 0.0);

	// Draw a sphere at the firing point, and add a shadow projected
	// onto the ground plane.
	glColor3f(1.f, 1.f, 1.f);
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glutSolidSphere(0.1f, 5, 5);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glColor3f(0.75f, 0.75f, 0.75f);
	glScalef(1.0f, 0.1f, 1.0f);
	glutSolidSphere(0.1f, 5, 5);
	glPopMatrix();

	// Draw some scale lines
	glColor3f(0.75f, 0.75f, 0.75f);
	glBegin(GL_LINES);
	for (unsigned i = 0; i < 200; i += 10)
	{
		glVertex3f(-5.0f, 0.0f, i);
		glVertex3f(5.0f, 0.0f, i);
	}
	glEnd();

	// Render each particle in turn
	for (AmmoRound *shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type != UNUSED)
		{
			switch (shot->type)
			{
			case PISTOL:
				m_currentShotText.setString("Current Shot Type: Pistol\nAmmo Count: " + std::to_string(ammoRounds));
				break;
			case ARTILLERY:
				m_currentShotText.setString("Current Shot Type: Artillery\nAmmo Count: " + std::to_string(ammoRounds));
				break;
			case FIREBALL:
				m_currentShotText.setString("Current Shot Type: Fireball\nAmmo Count: " + std::to_string(ammoRounds));
				break;
			case LASER:
				m_currentShotText.setString("Current Shot Type: Laser\nAmmo Count: " + std::to_string(ammoRounds));
				break;
			default:
				break;
			}
			shot->render();
		}
	}
	m_window.GetRenderWindow()->pushGLStates();
	m_window.Draw(m_currentShotText);
	m_window.GetRenderWindow()->popGLStates();
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