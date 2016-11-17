
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
			glColor3f(0.8, 0.15, 0.15);
			GLfloat sphereColor[] = { 0.8f, 0.15f, 0.15f, 1.0f };
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphereColor);
			glPushMatrix();
			glTranslatef(position->x, position->y, position->z);
			glutSolidSphere(0.3f, 5, 10);
			glPopMatrix();

			//creating some shadows 
			GLfloat sphereShadowColor[] = { 0.17, 0.15, 0.15, 1.0 };
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphereShadowColor);
			GLfloat sphereShadowEmission[] = { -1.f, -1.f, -1.f, 1.f };
			glMaterialfv(GL_FRONT, GL_EMISSION, sphereShadowEmission);
			//glColor3f(0.17, 0.15, 0.15);
			glPushMatrix();
			glTranslatef(position->x, 0, position->z);
			glScalef(1.0f, 0.1f, 1.0f);
			glutSolidSphere(0.6f, 5, 4);
			glPopMatrix();
			GLfloat defaultEmission[] = { 0.f, 0.f, 0.f, 1 };
			glMaterialfv(GL_FRONT, GL_EMISSION, defaultEmission);
		}
	};

	struct Model{
		void LoadObject(char* fname){
			FILE *fp;
			int read;
			GLfloat x, y, z;
			char ch;
			model = glGenLists(1);
			fp = fopen(fname, "r");
			rot = 0;
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
		
		bool LoadObject2(char *fname, std::vector<SFGE::Physics::Math::Vector3f>& out_verticies, std::vector<SFGE::Physics::Math::Vector2f>& out_uvs, std::vector<SFGE::Physics::Math::Vector3f>& out_normals){
			std::vector<unsigned int> vertexIndicies, uvIndicies, normalIndicies;
			std::vector<SFGE::Physics::Math::Vector3f> temp_vertices;
			std::vector<SFGE::Physics::Math::Vector2f> temp_uvs;
			std::vector<SFGE::Physics::Math::Vector3f> temp_normals;
			FILE* file = fopen(fname, "r");
			if (file == NULL){
				std::cout << "Couldn't open file\n";
				return false;
			}

			while (1){
				char lineHeader[128];

				int res = fscanf(file, "%s", lineHeader);
				if (res == EOF){
					break;
				}
				if (strcmp(lineHeader, "v") == 0){
					SFGE::Physics::Math::Vector3f vertex;
					fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
					temp_vertices.push_back(vertex);
				}
				else if (strcmp(lineHeader, "vt") == 0){
					SFGE::Physics::Math::Vector2f uv;
					fscanf(file, "%f %f\n", &uv.x, &uv.y);
					temp_uvs.push_back(uv);
				}
				else if (strcmp(lineHeader, "vn") == 0){
					SFGE::Physics::Math::Vector3f normal;
					fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
					temp_normals.push_back(normal);
				}
				else if (strcmp(lineHeader, "f") == 0){
					std::string vertex1, vertex2, vertex3;
					unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
					int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
					
					vertexIndicies.push_back(vertexIndex[0]);
					vertexIndicies.push_back(vertexIndex[1]);
					vertexIndicies.push_back(vertexIndex[2]);
					uvIndicies.push_back(uvIndex[0]);
					uvIndicies.push_back(uvIndex[1]);
					uvIndicies.push_back(uvIndex[2]);
					normalIndicies.push_back(normalIndex[0]);
					normalIndicies.push_back(normalIndex[1]);
					normalIndicies.push_back(normalIndex[2]);
				}
			}
			fclose(file);
			model = glGenLists(1);
			glNewList(model, GL_COMPILE);
			{
				glPushMatrix();
				glBegin(GL_POINTS);
				
				for (unsigned int i = 0; i < vertexIndicies.size(); i++){
					unsigned int vertexIndex = vertexIndicies[i];
					SFGE::Physics::Math::Vector3f vertex = temp_vertices[vertexIndex - 1];
					out_verticies.push_back(vertex);
					glVertex3f(vertex.x, vertex.y, vertex.z);
				}
				for (unsigned int i = 0; i < uvIndicies.size(); i++){
					unsigned int uvIndex = uvIndicies[i];
					SFGE::Physics::Math::Vector2f uv = temp_uvs[uvIndex - 1];
					out_uvs.push_back(uv);
					glTexCoord2f(uv.x, uv.y);
				}
				for (unsigned int i = 0; i < normalIndicies.size(); i++){
					unsigned int normalIndex = normalIndicies[i];
					SFGE::Physics::Math::Vector3f noraml = temp_normals[normalIndex - 1];
					out_normals.push_back(noraml);
					glNormal3f(noraml.x, noraml.y, noraml.z);
				}
				glEnd();
			}
			glPopMatrix();
			glEndList();
		}

		void Render(){
			glPushMatrix();
			glTranslatef(0.0f, 1.5f, 0.0f);
			glColor3f(1.0, 0.23, 0.27);
			glScalef(0.05, 0.05, 0.05);
			glRotatef(rot, 0, 1, 0);
			glCallList(model);
			glPopMatrix();
			rot = rot + 0.6;
			if (rot > 360)rot = rot - 360;
		}

		void Render2(){
			glPushMatrix();
			glTranslatef(-2.0f, 0.0f, 0.0f);
			glScalef(0.05, 0.05, 0.05);
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
	Model car;
	double camera_angle_h;
	double camera_angle_v;
	double camera_forward;

};