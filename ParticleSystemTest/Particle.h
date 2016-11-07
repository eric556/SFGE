#include <VectorMath.h>
#include <random>

struct Particle{
	SFGE::Math::vector2::Vector2f position;
	SFGE::Math::vector2::Vector2f velocity;
	float mass;

	void Initialize(){
		position.x = rand() % 1920;
		position.y = rand() % 1080;
		velocity.x = 0;
		velocity.y = 0;
		mass = 1;
	}

	SFGE::Math::vector2::Vector2f ComputeForce(){
		SFGE::Math::vector2::Vector2f forces(0, this->mass * 9.81);
		return forces;
	}

	SFGE::Math::vector2::Vector2f ComputeGravitationalAttractions(Particle *other){
		SFGE::Math::vector2::Vector2f r(other->position.x - this->position.x, other->position.y - this->position.y);
		float distance = pow((other->position.x - this->position.x), 2) + pow((other->position.y - this->position.y), 2);
		float masses = this->mass * other->mass;
		float force = (5 * masses) / distance;
		r *= force;
		return r;
	}

	void IntegrateForce(SFGE::Math::vector2::Vector2f force, float dt){
		SFGE::Math::vector2::Vector2f acceleration(force.x / this->mass, force.y / this->mass);
		this->velocity.x += acceleration.x * dt;
		this->velocity.y += acceleration.y * dt;
		IntegrateVelocity(dt);
	}

	void IntegrateVelocity(float dt){
		this->position.x += this->velocity.x * dt;
		this->position.y += this->velocity.y * dt;
	}

};