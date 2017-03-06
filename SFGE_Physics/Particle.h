#include "Vector3.h"
#include <assert.h>
namespace SFGE{
	namespace Physics{
		namespace Components{
			/*! A point in space with a position a velocity and an acceleration
			*/
			class Particle{
			public:

				/*! Creates a new Particle with the given values for position, velocity, mass, and optionaly dampening
					\param position of the particle
					\param velocity of particle
					\param mass of the particle
					\param dampening of the particle (Set to 0.99f by default)
				*/
				Particle(SFGE::Physics::Math::Vector3f position, SFGE::Physics::Math::Vector3f velocity, float mass, float dampening = 0.99f){
					(mass <= 0) ? this->SetInverseMass(0) : this->SetMass(mass);
					this->SetPosition(position);
					this->SetVelocity(velocity);
					this->SetDampning(dampening);
				}

				/*! Creates a new Particle with the given values for position, velocity, mass, and optionaly dampening
					\param x x position of the particle
					\param y y position of the particle
					\param z z position of the particle
					\param vx x component of velocity
					\param vy y component of velocity
					\param vz z component of velocity
					\param mass of the particle
					\param dampening of the particle (Set to 0.99f by default)
				*/
				Particle(float x, float y, float z, float vx, float vy, float vz, float mass, float dampening = 0.99f) : 
					Particle(SFGE::Physics::Math::Vector3f(x, y, z), SFGE::Physics::Math::Vector3f(vx, vy, vz), mass, dampening){}

				/*! Sets the mass of the Particle. Only use with none 0 mass
					\param mass mass to set
				*/
				void SetMass(float mass){
					inverseMass = 1 / mass;
				}
				/*! Sets the inverse mass of the Particle. Use if you want mass of 0
					\param imass inverse mass to set
				*/
				void SetInverseMass(float imass){
					inverseMass = imass;
				}

				void SetVelocity(float x, float y, float z){
					velocity.x = x;
					velocity.y = y;
					velocity.z = z;
				}

				void SetVelocity(Math::Vector3f vec){
					velocity = vec;
				}

				Math::Vector3f* GetVelocity(){
					return &velocity;
				}

				void SetAcceleration(float x, float y, float z){
					acceleration.x = x;
					acceleration.y = y;
					acceleration.z = z;
				}

				void SetAcceleration(Math::Vector3f vec){
					acceleration = vec;
				}

				Math::Vector3f* GetAcceleration(){
					return &acceleration;
				}

				void SetPosition(float x, float y, float z){
					position.x = x;
					position.y = y;
					position.z = z;
				}

				void SetPosition(Math::Vector3f vec){
					position = vec;
				}

				Math::Vector3f* GetPosition(){
					return &position;
				}

				void SetDampning(float d){
					assert((d <= 1 && d >=0) && "Invalid Dampning");
					dampening = d;
				}

				/*! Update position, velocity and acceleration based on forces accumulated during the current frame.
					\param dt time since last update
				*/
				void Integrate(float dt){
					if (inverseMass <= 0.0f) return;

					assert(dt > 0.0);
					IntegratePosition(dt);
					IntegrateVelocity(dt);
					ApplyDrag(dt);
					ClearAccum();
				}
				void ClearAccum(){
					forceAccum.clear();
				}

				bool hasFiniteMass(){
					if (this->inverseMass > 0){
						return true;
					}
					return false;
				}

				void addForce(Math::Vector3f force){
					this->forceAccum += force;
				}

				float getMass(){
					return 1 / this->inverseMass;
				}
			private:
				/*! Updates the position based on velocity
					\param dt time since last update
				*/
				void IntegratePosition(float dt){
					position += velocity * dt;
				}
				/*! Updates the velocity based on acceleration
					\param dt time since last update
				*/
				void IntegrateVelocity(float dt){
					acceleration += forceAccum * inverseMass;
					velocity += acceleration * dt;
				}
				/*! Apply dampening to velocity
					\param dt time since last update
				*/
				void ApplyDrag(float dt){
					velocity *= powf(dampening, dt);
				}
				/*! Clears the force accumulator
				*/
				
			protected:
				//! position of particle
				Math::Vector3f position;
				//! velocity of particle
				Math::Vector3f velocity;
				//! acceleration of particle
				Math::Vector3f acceleration;
				//! holds the forces that accumulate until the next update. Gets cleared each update
				Math::Vector3f forceAccum;
				//! fake drag to counteract numerical inaccuracies in floating point calculations. 0 means all velocity is removed every tick, 1 means all velocity is kept every tick
				float dampening;
				//! the inverse of the mass of the object (1/mass)
				float inverseMass;
			};
		}
	}
}
