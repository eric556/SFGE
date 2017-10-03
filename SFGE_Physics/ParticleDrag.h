#pragma once
#include "ParticleForceGenerator.h"
#include "Vector3.h"

namespace SFGE{
	namespace Physics{
		namespace Generators{

			class ParticleDrag : public ParticleForceGenerator{
				float k1;
				float k2;
				sf::Clock clock;
			public:
				ParticleDrag(float k1, float k2){
					this->k1 = k1;
					this->k2 = k2;
				}

				virtual void updateForce(Components::Particle* p, float duration){
					Math::Vector3f force;
					p->GetVelocity(force);
					float dragCoeff = force.magnitude();
					dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

					force.normalize();
					force *= -dragCoeff;
					p->addForce(force);*/
					clock.restart();
					Math::Vector3f velocity;
					p->GetVelocity(velocity);
					Math::Vector3f force = (velocity*-1) * (k1*velocity.magnitude() + k2 * powf(velocity.magnitude(), 2));
					p->addForce(force);
				}
			};
		}
	}
}