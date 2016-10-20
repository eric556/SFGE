#include <SFML\Graphics.hpp>
#include "VectorMath.h"
namespace SFGE{
	class Polygon:public sf::ConvexShape{
	public:
		SFGE::Math::vector2::Vector2f GetEdge(int index);
		int GetEdgeCount();
		SFGE::Math::vector2::Vector2f GetMidPoint();
		SFGE::Math::vector2::Vector2f GetWorldPoint(int index);
	};
}