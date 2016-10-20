#include <SFML\Graphics.hpp>
#include <thread>
#include "Window.h"
#include "Polygon.h"

class RigidBody{
	
public:
	struct PolygonCollisionResult{
		bool WillIntersect;
		bool Intersect;
		SFGE::Math::vector2::Vector2f MinimumTranslationVector;
		std::string collisionMask;
	};

	RigidBody(float l_maxJumpHeight, float l_timeToReachMaxHeight);
	RigidBody();
	void Update(float deltaTime);
	void Draw(SFGE::Window& l_window);
	void AddImpulse(sf::Vector2f l_impulseVector, float durationOfImpulse, float delatTime);
	void Move(sf::Vector2f vel);
	void SetPosition(sf::Vector2f pos){
		this->SetPosition(pos.x, pos.y);
	}
	void SetPosition(float x, float y){
		position.x = x;
		position.y = y;
	}
	sf::Vector2f GetPosition(){ return position; }
	void SetBoundingBox(SFGE::Polygon shape){
		bbox = shape;
	}
	SFGE::Polygon& GetBoundingBox(){
		return bbox;
	}
	void SetCollisionMask(std::string mask){
		this->collisionMask = mask;
	}
	std::string GetCollisionMask(){
		return this->collisionMask;
	}
	float GetGravity(){
		return gravity;
	}
	void SetGravity(float grav){
		gravity = grav;
	}
	sf::Vector2f GetVelocity(){
		return vel;
	}
	void SetVelocity(sf::Vector2f vel){
		this->vel = vel;
	}
public:
	std::vector<RigidBody> collidables;
	std::vector<PolygonCollisionResult> collidedWith;
	std::vector<PolygonCollisionResult> willCollideWith;

private:
	void addImpulseThread(sf::Vector2f l_impulseVector, float durationOfImpulse, float deltaTime);
	PolygonCollisionResult checkCollision(RigidBody body, float deltaTime);
	void projectPolygon(SFGE::Math::vector2::Vector2f axis, SFGE::Polygon polygon, float& min, float& max);
	float intervalDistance(float minA, float maxA, float minB, float maxB);
	PolygonCollisionResult polygonCollision(SFGE::Polygon& polygonA, SFGE::Polygon& polygonB, SFGE::Math::vector2::Vector2f velocity);
private:
	float maxJumpHeight;
	float timeToReachMaxHeight;
	float velocityOfJump;
	float gravity;
	float terminalVel;
	float mass;
	float volume;
	float density;
	sf::FloatRect boundingBox;
	sf::RectangleShape BoundingBoxDrawable;
	SFGE::Polygon bbox;
	sf::Vector2f vel;
	sf::Vector2f position;
	std::string collisionMask;
};