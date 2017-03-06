#include "BasicGame.h"


BasicGame::BasicGame(std::string title, sf::Vector2u windowSize):m_window(title,windowSize,"Resources/Keys/keys.cfg") {
	font.loadFromFile("Resources/Fonts/Quivira.otf");
	m_currentShotText.setFont(font);
	m_currentShotText.setString("Current Shot Type: ");
	m_currentShotText.setCharacterSize(12);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
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
	numUnused = ammoRounds;
	m_window.GetEventManager()->AddCallback("Fire_Proj", &BasicGame::FireProj, this);
	m_window.GetEventManager()->AddCallback("Projectile_toggle_a", &BasicGame::ToggleProj, this);
	m_window.GetEventManager()->AddCallback("Projectile_toggle_b", &BasicGame::ToggleProj, this);
	m_window.GetEventManager()->AddCallback("Projectile_toggle_c", &BasicGame::ToggleProj, this);
	m_window.GetEventManager()->AddCallback("Projectile_toggle_d", &BasicGame::ToggleProj, this);
	//car.LoadObject("Resources/IronMan.obj");
	std::vector<SFGE::Physics::Math::Vector3f> vertices;
	std::vector<SFGE::Physics::Math::Vector2f> uvs;
	std::vector<SFGE::Physics::Math::Vector3f> normals;
	bool res = car.LoadObject2("Resources/untitled.obj", vertices,uvs,normals);
	camera_angle_h = 0;
	camera_angle_v = 0;
camera_forward = 0;

}

void BasicGame::FireProj(SFGE::EventDetails* details){
	std::cout << "fired\n";
	std::cout << details->m_name;
	fire();
}

void BasicGame::ToggleProj(SFGE::EventDetails* details){
	switch (details->m_keyCode){
	case sf::Keyboard::Key::A:
		currentShotType = ARTILLERY;
		break;
	case sf::Keyboard::Key::S:
		currentShotType = PISTOL;
		break;
	case sf::Keyboard::Key::D:
		currentShotType = FIREBALL;
		break;
	case sf::Keyboard::Key::F:
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
	numUnused--;
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
		shot->particle.SetMass(0.673); // 200.0kg
		shot->particle.SetVelocity(0.0f, 27.3, 27.3); // 50m/s
		shot->particle.SetAcceleration(0.0f, -98.0f, 0.0f);
		shot->particle.SetDampning(1);
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
	shot->particle.SetPosition(0.0f, 0.264f, 0.0f);
	shot->startTime = GetElapsed();
	shot->type = currentShotType;

	// Clear the force accumulators
	shot->particle.ClearAccum();
}

BasicGame::~BasicGame(){
}

void BasicGame::Update(){
	m_window.Update();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		camera_angle_h += 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		camera_angle_h -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		camera_forward -= 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		camera_forward += 1;
	}
}

void BasicGame::FixedUpdate(float deltaTime){
	for (auto &shot : ammo){
		if (shot.type != UNUSED){
			shot.particle.Integrate(deltaTime);
			if (shot.particle.GetPosition()->y < 0.0f || shot.particle.GetPosition()->z > 200.0f || shot.particle.GetPosition()->y > 1000.f){
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
	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	glTranslated(std::cos(camera_angle_h * 3.14/180) * camera_forward,0,std::sin(camera_angle_h * 3.14/180) * camera_forward);

	// Draw a sphere at the firing point, and add a shadow projected
	// onto the ground plane.
	GLfloat sphereColor[] = { 0.8f, 0.15f, 0.15f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphereColor);
	glPushMatrix();
	glTranslatef(0.0, 3.1, 12.5);
	glutSolidSphere(0.1, 5, 5);
	glTranslatef(0.0f, 1.5f, 0.0f);
	glutSolidSphere(0.01f, 5, 5);
	glTranslatef(0.0f, -1.5f, 0.0f);
	GLfloat sphereShadowColor[] = { 0.17, 0.15, 0.15, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphereShadowColor);
	GLfloat sphereShadowEmission[] = { -1.f, -1.f, -1.f, 1.f };
	glMaterialfv(GL_FRONT, GL_EMISSION, sphereShadowEmission);
	glScalef(1.0f, 0.1f, 1.0f);
	glutSolidSphere(0.01f, 5, 5);
	glPopMatrix();
	GLfloat defaultEmission[] = { 0.f, 0.f, 0.f, 1 };
	glMaterialfv(GL_FRONT, GL_EMISSION, defaultEmission);

	// Draw some scale lines
	GLfloat lineColors[] = { 1, 1, 1, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lineColors);
	GLfloat lineEmission[] = { 1, 1, 1, 1 };
	glMaterialfv(GL_FRONT, GL_EMISSION, lineEmission);
	glBegin(GL_LINES);
	for (unsigned i = 0; i < 200; i += 10)
	{
		glVertex3f(-5.0f, 0.0f, i);
		glVertex3f(5.0f, 0.0f, i);
	}
	glEnd();
	glMaterialfv(GL_FRONT, GL_EMISSION, defaultEmission);

	// Render each particle in turn
	for (AmmoRound *shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type != UNUSED)
		{
			switch (shot->type)
			{
			case PISTOL:
				m_currentShotText.setString("Current Shot Type: Pistol\nAmmo Count: " + std::to_string(numUnused));
				break;
			case ARTILLERY:
				m_currentShotText.setString("Current Shot Type: Artillery\nAmmo Count: " + std::to_string(numUnused));
				break;
			case FIREBALL:
				m_currentShotText.setString("Current Shot Type: Fireball\nAmmo Count: " + std::to_string(numUnused));
				break;
			case LASER:
				m_currentShotText.setString("Current Shot Type: Laser\nAmmo Count: " + std::to_string(numUnused));
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
	//car.Render();
	//glMaterialfv(GL_FRONT, GL_SPECULAR, sphereColor);
	glRotatef(-90, 0, 1, 0);
	//car.Render2();
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
		c++;
	}
}