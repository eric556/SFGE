
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include <glut.h>
#include <Game.h>
#include <EventManager.h>
#include <Particle.h>


class BasicGame : public SFGE::Game{
public:
	BasicGame(std::string title, sf::Vector2u windowSize);
	~BasicGame();
	void Update();
	void FixedUpdate(float deltaTime);
	void Render();
	void Run();
	SFGE::Window* GetWindow(){
		return &m_window;
	}
	enum ShotType{
		UNUSED = 0,
		PISTOL,
		ARTILLERY,
		FIREBALL,
		LASER
	};

	struct AmmoRound{
		SFGE::Physics::Components::Particle particle;
		ShotType type;
		unsigned startTime;

		void render(){
			SFGE::Physics::Math::Vector3f* position;
			position = particle.GetPosition();

			//creating the actual sphere
			glColor3f(1.0, 0, 0);
			glPushMatrix();
			glTranslatef(position->x, position->y, position->z);
			glutSolidSphere(0.3f, 5, 4);
			glPopMatrix();

			//creating some shadows 
			glColor3f(0.75, 0.75, 0.75);
			glPushMatrix();
			glTranslatef(position->x, 0, position->z);
			glScalef(1.0f, 0.1f, 1.0f);
			glutSolidSphere(0.6f, 5, 4);
			glPopMatrix();
		}
	};

	const static unsigned int ammoRounds = 16;
	unsigned int numUnused = 0;

	AmmoRound ammo[ammoRounds];

	/** Holds the current shot type. */
	ShotType currentShotType;

	/** Dispatches a round. */
	void fire();

private:
	void FireProj(SFGE::EventDetails* details);
	void ToggleProj(SFGE::EventDetails* details);
	SFGE::Window m_window;
	sf::Text m_currentShotText;
	sf::Font font;


};