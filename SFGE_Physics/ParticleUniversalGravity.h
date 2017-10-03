#pragma once
#include "ParticleForceGenerator.h"
#include "Vector3.h"
#include <vector>

#define G 6.67E-11;

namespace SFGE{
	namespace Physics{
		namespace Generators{
			class ParticleUniversalGravity : public ParticleForceGenerator{
				std::vector<Components::Particle> others;
			public:
				ParticleUniversalGravity(std::vector<Components::Particle> p){
					others = p;
				}

				virtual void updateForce(Components::Particle* p, float duration){

					for each (Components::Particle part in others)
					{
						if (!p->hasFiniteMass()) return;
						if (p == &part) return;
						Math::Vector3f r = (part.GetPosition() - p->GetPosition()).normalize();
						float rMag = r.magnitude();
						Math::Vector3f force = r * (((part.getMass() * p->getMass())) / powf(rMag, 2)) * -G;
						p->addForce(force);
					}
				}
			};
		}
	}
}