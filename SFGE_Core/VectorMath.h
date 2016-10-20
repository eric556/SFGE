#include <SFML\System\Vector2.hpp>
#include <string>
namespace SFGE{
	namespace Math{
		namespace vector2{
			class Vector2f{
			public:
				float x;
				float y;
				Vector2f(float x, float y){
					this->x = x;
					this->y = y;
				}
				Vector2f(){
					this->x = 0;
					this->y = 0;
				}
				Vector2f(sf::Vector2f vec){
					this->x = vec.x;
					this->y = vec.y;
				}
				Vector2f& operator+=(const Vector2f);
				Vector2f operator+(const Vector2f) const;
				Vector2f& operator-=(const Vector2f);
				Vector2f operator-(const Vector2f) const;
				Vector2f& operator*=(float);
				Vector2f operator*(float) const;
				Vector2f& operator/=(float);
				Vector2f operator/(float) const;
				Vector2f& operator%=(float);
				Vector2f operator%(float) const;
				bool operator==(const Vector2f);
				bool operator!=(const Vector2f);
				float dot(const Vector2f);
				Vector2f normalize();
				Vector2f& truncate(float);
				float angle();
				float magnitude();
				const std::string to_str();
				const sf::Vector2f sf() { return sf::Vector2f(this->x, this->y); }
			};
		}
	}
}