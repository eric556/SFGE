#include "VectorMath.h"

namespace SFGE{
	namespace Math{
		namespace vector2{
			Vector2f& Vector2f::operator+=(const Vector2f otr){
				this->x += otr.x;
				this->y += otr.y;
				return *this;
			}
			Vector2f Vector2f::operator+(const Vector2f other) const{
				return Vector2f(this->x + other.x, this->y + other.y);
			}
			Vector2f& Vector2f::operator-=(const Vector2f otr){
				this->x -= otr.x;
				this->y -= otr.y;
				return *this;
			}
			Vector2f Vector2f::operator-(const Vector2f other) const{
				return Vector2f(this->x - other.x, this->y - other.y);
			}
			Vector2f& Vector2f::operator*=(float scale){
				this->x *= scale;
				this->y *= scale;
				return *this;
			}
			Vector2f Vector2f::operator*(float scale) const{
				return Vector2f(this->x * scale, this->y * scale);
			}
			Vector2f& Vector2f::operator/=(float scale){
				this->x /= scale;
				this->y /= scale;
				return *this;
			}
			Vector2f Vector2f::operator/(float scale) const{
				return Vector2f(this->x / scale, this->y / scale);
			}
			Vector2f& Vector2f::operator%=(float theta){
				float cosine = std::cos(theta);
				float sine = std::sin(theta);
				float px = x * cosine - y * sine;
				float py = x * sine + y * cosine;

				this->x = px;
				this->y = py;
				return *this;
			}
			Vector2f Vector2f::operator%(float theta) const{
				float cosine = std::cos(theta);
				float sine = std::sin(theta);
				float px = x * cosine - y * sine;
				float py = x * sine + y * cosine;

				return Vector2f(px, py);
			}
			Vector2f& Vector2f::operator=(const Vector2f other){
				this->x = other.x;
				this->y = other.y;
				return *this;
			}

			bool Vector2f::operator==(const Vector2f other){
				return this->x == other.x && this->y == other.y;
			}
			bool Vector2f::operator!=(const Vector2f other){
				return !(*this == other);
			}
			float Vector2f::dot(const Vector2f other){
				return this->x * other.x + this->y * other.y;
			}
			Vector2f Vector2f::normalize(){
				*this /= this->magnitude();
				return *this;
			}
			Vector2f& Vector2f::truncate(float max){
				if (this->magnitude() > max){
					this->x = (this->normalize() * max).x;
					this->y = (this->normalize() * max).y;
				}
				return *this;
			}
			Vector2f Vector2f::unitVector(){
				float magnitude = this->magnitude();
				this->x = this->x / magnitude;
				this->y = this->y / magnitude;
				return *this;
			}
			float Vector2f::angle(){
				return std::atan2(this->x, this->y);
			}
			float Vector2f::magnitude(){
				return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
			}

			float Vector2f::magnitudeSqrt(){
				return std::pow(this->x, 2) + std::pow(this->y, 2);
			}
			const std::string Vector2f::to_str(){
				std::string finalString = "" + std::to_string(this->x) + ", " + std::to_string(this->y);
				return finalString;
			}
		}
	}

}