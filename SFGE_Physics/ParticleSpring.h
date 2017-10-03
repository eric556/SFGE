#pragma once
#include "ParticleForceGenerator.h"
#include "Vector3.h"
#include "Particle.h"

namespace SFGE{
	namespace Physics{
		namespace Generators{
			class ParticleSpring : public ParticleForceGenerator{
				Components::Particle* other;
				float springConstant;
				float restLength;

			public:
				ParticleSpring(Components::Particle* other, float springConstant, float restLength){
					this->other = other;
					this->springConstant = springConstant;
					this->restLength = restLength;
				}

				virtual void updateForce(Components::Particle* p, float duration){
					Math::Vector3f distance = p->GetPosition() - other->GetPosition();
					float x = distance.magnitude() - restLength;
					Math::Vector3f force = distance.normalize() * (-springConstant * x);
					p->addForce(force);
				}
			};
		}
	}
}