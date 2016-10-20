#include "RigidBody.h"

RigidBody::RigidBody(float l_maxJumpHeight, float l_timeToReachMaxHeight)
{
	maxJumpHeight = l_maxJumpHeight;
	timeToReachMaxHeight = l_timeToReachMaxHeight;
	gravity = (2 * maxJumpHeight) / (timeToReachMaxHeight * timeToReachMaxHeight);
	velocityOfJump = sqrtf(2 * gravity*maxJumpHeight);
	mass = 100;
	//volume = l_boundingBox.width * l_boundingBox.height;
	//density = mass / volume;
	terminalVel = sqrt((2 * mass * gravity) / (1 * 1 * 10));
	//std::cout << terminalVel << "\n";
	bbox.setPointCount(4);
	bbox.setPoint(0, sf::Vector2f(0, 0));
	bbox.setPoint(1, sf::Vector2f(50, 0));
	bbox.setPoint(2, sf::Vector2f(50, 50));
	bbox.setPoint(3, sf::Vector2f(0, 50));
	bbox.setPosition(position);
	bbox.setFillColor(sf::Color(sf::Color::Red.r, sf::Color::Red.g, sf::Color::Red.b, 100));
	this->collisionMask = "";
}

RigidBody::RigidBody(){
	maxJumpHeight = 0;
	timeToReachMaxHeight = 1;
	gravity = (2 * maxJumpHeight) / (timeToReachMaxHeight * timeToReachMaxHeight);
	velocityOfJump = sqrtf(2 * gravity*maxJumpHeight);
	mass = 100;
	//volume = l_boundingBox.width * l_boundingBox.height;
	//density = mass / volume;
	terminalVel = sqrt((2 * mass * gravity) / (1 * 1 * 10));
	std::cout << terminalVel << "\n";
	bbox.setPointCount(4);
	bbox.setPoint(0, sf::Vector2f(0, 0));
	bbox.setPoint(1, sf::Vector2f(50, 0));
	bbox.setPoint(2, sf::Vector2f(50, 50));
	bbox.setPoint(3, sf::Vector2f(0, 50));
	bbox.setPosition(position);
	bbox.setFillColor(sf::Color(sf::Color::Red.r, sf::Color::Red.g, sf::Color::Red.b, 100));
	this->collisionMask = "";
}

void RigidBody::Draw(SFGE::Window& l_window){
	//l_window.Draw(BoundingBoxDrawable);
	l_window.Draw(bbox);
}

void RigidBody::Update(float deltaTime)
{
	bbox.setPosition(position);
	if (vel.y * deltaTime < terminalVel){
		vel.y += gravity;
	}
	for (int i = 0; i < this->collidables.size(); i++){
		PolygonCollisionResult result = this->checkCollision(collidables[i], deltaTime);
		sf::Vector2f velocity;
		if (( result.WillIntersect ) && collidables[i].GetCollisionMask() == "Ground"){
			result.collisionMask = collidables[i].GetCollisionMask();
			this->AddImpulse(-(result.MinimumTranslationVector * 1).sf(), 0 , deltaTime);
		}
		std::cout << "Intersect: " << result.Intersect << " Will Intersect: " << result.WillIntersect << " Velocity: " << result.MinimumTranslationVector.to_str() << " Collision Mask: " << result.collisionMask << "\n";
	}
	
	this->Move(this->vel * deltaTime);
	
}

void RigidBody::addImpulseThread(sf::Vector2f l_impulseVector, float durationOfImpulse, float deltaTime){
	sf::Clock impulseDuration;
	
	do
	{
		this->vel += (l_impulseVector / impulseDuration.getElapsedTime().asSeconds());
	} while (impulseDuration.getElapsedTime().asSeconds() < durationOfImpulse);
	//std::cout << "broke out of the while loop\n";
	impulseDuration.restart();
}

void RigidBody::AddImpulse(sf::Vector2f l_impulseVector, float durationOfImpulse, float deltaTime)
{
	this->vel += l_impulseVector;
}

void RigidBody::Move(sf::Vector2f vel){
	this->position.x += vel.x;
	this->position.y += vel.y;
}


float RigidBody::intervalDistance(float minA, float maxA, float minB, float maxB){
	if (minA < minB){
		return minB - maxA;
	}
	else{
		return minA - maxB;
	}
}



RigidBody::PolygonCollisionResult RigidBody::checkCollision(RigidBody body, float deltaTime){
	PolygonCollisionResult result;
	SFGE::Math::vector2::Vector2f otherBodyMid(body.GetBoundingBox().getGlobalBounds().width / 2 + body.GetPosition().x, body.GetBoundingBox().getGlobalBounds().height / 2 + body.GetPosition().y);
	SFGE::Math::vector2::Vector2f thisBodyMid(this->GetBoundingBox().getGlobalBounds().width / 2 + this->GetPosition().x, this->GetBoundingBox().getGlobalBounds().height / 2 + this->GetPosition().y);
	//std::cout << otherBodyMid.to_str();
	std::vector<SFGE::Math::vector2::Vector2f> otherBodyWorldPoints;
	for (int j = 0; j < body.GetBoundingBox().getPointCount(); j++){
		otherBodyWorldPoints.push_back(SFGE::Math::vector2::Vector2f(body.GetBoundingBox().getPoint(j).x + body.GetPosition().x, body.GetBoundingBox().getPoint(j).y + body.GetPosition().y));
	}
	bool isSpereated = false;
	SFGE::Math::vector2::Vector2f translationAxis;
	SFGE::Math::vector2::Vector2f axis;
	float minIntervalDistance = std::numeric_limits<float>::infinity();
	for (int edgeIndex = 0; edgeIndex < body.GetBoundingBox().GetEdgeCount() + this->GetBoundingBox().GetEdgeCount(); edgeIndex++){
		if (edgeIndex < body.GetBoundingBox().GetEdgeCount()){

			 axis = SFGE::Math::vector2::Vector2f(-body.GetBoundingBox().GetEdge(edgeIndex).y, body.GetBoundingBox().GetEdge(edgeIndex).x);
		}
		else{
			axis = SFGE::Math::vector2::Vector2f(-this->GetBoundingBox().GetEdge(edgeIndex - body.GetBoundingBox().GetEdgeCount()).y, this->GetBoundingBox().GetEdge(edgeIndex - body.GetBoundingBox().GetEdgeCount()).x);
		}
		//SFGE::Math::vector2::Vector2f axis(-this->GetBoundingBox().GetEdge(edgeIndex).y, this->GetBoundingBox().GetEdge(edgeIndex).x);
		axis = axis.normalize();
		//std::cout << axis.to_str() << "\n";
		float minProjectionA = this->GetBoundingBox().GetWorldPoint(1).dot(axis);
		int minDotA = 1;
		float maxProjectionA = this->GetBoundingBox().GetWorldPoint(1).dot(axis);
		int maxDotA = 1;

		for (int j = 2; j < this->GetBoundingBox().getPointCount(); j++){
			float currentProjection = this->GetBoundingBox().GetWorldPoint(j).dot(axis);
			if (minProjectionA > currentProjection){
				minProjectionA = currentProjection;
				minDotA = j;
			}

			if (currentProjection > maxProjectionA){
				maxProjectionA = currentProjection;
				maxDotA = j;
			}
		}

		float minProjectionB = otherBodyWorldPoints[1].dot(axis);
		int minDotB = 1;
		float maxProjectionB = otherBodyWorldPoints[1].dot(axis);
		int maxDotB = 1;

		for (int j = 2; j < body.GetBoundingBox().getPointCount(); j++){
			float currentProjection = otherBodyWorldPoints[j].dot(axis);
			if (minProjectionB > currentProjection){
				minProjectionB = currentProjection;
				minDotB = j;
			}

			if (currentProjection > maxProjectionB){
				maxProjectionB = currentProjection;
				maxDotB = j;
			}
		}

		
		if (intervalDistance(minProjectionA, maxProjectionA, minProjectionB, maxProjectionB) > 0){
			result.Intersect = false;
		}

		float velocityProjection = axis.dot(this->vel * deltaTime);
		//std::cout << "Vel Projection: " << velocityProjection << "\n";
		if (velocityProjection < 0){
			minProjectionA += velocityProjection;
		}
		else{
			maxProjectionA += velocityProjection;
		}

		float distance = intervalDistance(minProjectionA, maxProjectionA, minProjectionA, maxProjectionB);
		if (distance > 0){
			result.WillIntersect = false;
		}
		if (!result.Intersect && !result.WillIntersect) break;

		
		if (distance < minIntervalDistance){
			//std::cout << distance << "\n";
			minIntervalDistance = distance;
			translationAxis = axis;

			SFGE::Math::vector2::Vector2f d = thisBodyMid - otherBodyMid;
			if (d.dot(translationAxis) < 0){
				translationAxis = translationAxis * -1;
			}
		}

	}
	if (result.WillIntersect){
		result.MinimumTranslationVector = (translationAxis * minIntervalDistance);
	}
	return result;
}

