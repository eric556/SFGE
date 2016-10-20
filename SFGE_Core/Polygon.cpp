#include "Polygon.h"

namespace SFGE{

	SFGE::Math::vector2::Vector2f Polygon::GetEdge(int index){
		if (index < this->getPointCount() - 1){
			return SFGE::Math::vector2::Vector2f(this->getPoint(index).x - this->getPoint(index+1).x,this->getPoint(index).y - this->getPoint(index + 1).y);
		}else if (index == this->getPointCount()-1){
			return SFGE::Math::vector2::Vector2f(this->getPoint(index).x - this->getPoint(0).x, this->getPoint(index).y - this->getPoint(0).y);
		}else{
			return SFGE::Math::vector2::Vector2f();
		}
	}

	int Polygon::GetEdgeCount(){
		return this->getPointCount();
	}

	SFGE::Math::vector2::Vector2f Polygon::GetMidPoint(){
		return SFGE::Math::vector2::Vector2f(this->getGlobalBounds().width / 2 + this->getPosition().x, this->getGlobalBounds().height / 2 + this->getPosition().y);
	}

	SFGE::Math::vector2::Vector2f Polygon::GetWorldPoint(int index){
		return SFGE::Math::vector2::Vector2f(this->getPoint(index).x + this->getPosition().x, this->getPoint(index).y + this->getPosition().y);
	}

}