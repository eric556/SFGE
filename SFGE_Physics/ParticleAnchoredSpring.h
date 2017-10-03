#pragma once
#include "ParticleForceGenerator.h"
#include "Vector3.h"


namespace SFGE{
	namespace Physics{
		namespace Generators{
			class ParticleAnchoredSpring : public ParticleForceGenerator{
			protected:
				Math::Vector3f *anchor;
				float springConstant;
				float restLength;
			public:
				ParticleAnchoredSpring(Math::Vector3f* anchor, float springConstant, float restLength){
					this->anchor = anchor;
					this->springConstant = springConstant;
					this->restLength = restLength;
				}

				virtual void updateForce(Components::Particle* particle, float duration){
					Math::Vector3f force;
					particle->GetPosition(force);
					force -= *anchor;

					float magnitude = force.magnitude();
					magnitude = (restLength - magnitude) * springConstant;

					force.normalize();
					force *= magnitude;
					particle->addForce(force);
				}
			};
		}
	}
}
