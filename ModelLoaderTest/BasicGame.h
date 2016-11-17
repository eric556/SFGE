
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
#include "Game.h"
#include "EventManager.h"
#include <SFML\OpenGL.hpp>
#include <assert.h>
#include <glut.h>

struct Model{
	void LoadObject(char* fname){
		FILE *fp;
		int read;
		GLfloat x, y, z;
		char ch;
		model = glGenLists(1);
		fp = fopen(fname, "r");
		//assert(fp && "Couldn't open the file. Make sure it exists");
		if (!fp){
			std::cout << "Couldn't load the file\n";
		}
		else{
			std::cout << "Opened the file\n";
		}
		glPointSize(2.0);
		glNewList(model, GL_COMPILE);
		{
			glPushMatrix();
			glBegin(GL_POINTS);
			while (!(feof(fp))){
				read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
				if (read == 4 && ch == 'v'){
					glVertex3f(x, y, z);
				}
			}
			glEnd();
		}
		glPopMatrix();
		glEndList();
		fclose(fp);
	}

	void Render(){
		glPushMatrix();
		glTranslatef(0, -40.00, -105);
		glColor3f(1.0, 0.23, 0.27);
		glScalef(0.1, 0.1, 0.1);
		glRotatef(rot, 0, 1, 0);
		glCallList(model);
		glPopMatrix();
		rot = rot + 0.6;
		if (rot > 360)rot = rot - 360;
	}

	char* filename;
	GLuint model;
	char ch;
	float rot;
};

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
private:
	SFGE::Window m_window;
	Model car;
};