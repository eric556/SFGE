#pragma once
#include <iostream>
#include <string>
#include "Vector2.h"

namespace SFGE{
	namespace Physics{
		namespace Math{
			template<typename T>
			class Vector3{
			public:
				inline Vector3() :x(0), y(0), z(0){}

				inline Vector3(T X, T Y, T Z) : x(X), y(Y), z(Z){}

				inline Vector3(T X, T Y) : x(X), y(Y), z(0){}

				template<typename U>
				inline Vector3(const Vector3<U>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z)){}

				template<typename U>
				inline Vector3(const Vector2<U>& vector){
					Vector3<U> temp();
					temp.x = vector.x;
					temp.y = vector.y;
					Vector3(temp);
				}


				inline T dot(const Vector3<T>& other){
					return this->x * other.x + this-> * other.y + this->z * other.z;
				}

				inline T magnitude(){
					return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
				}

				inline T magnitudeSqr(){
					return std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2);
				}

				inline Vector3<T>& normalize(){
					*this /= this->magnitude();
					return *this;
				}

				inline Vector3<T>& truncate(T max){
					if (this->magnitude() > max){
						this->x = (this->normalize() * max).x;
						this->y = (this->normalize() * max).y;
						this->z = (this->normalize() * max).y;
					}
					return *this
				}
				
				inline Vector3<T>& invert(){
					this->x = -x;
					this->y = -y;
					this->z = -z;
					return *this;
				}

				inline const std::string to_str(){
					std::string finalString = "" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z);
					return finalString;
				}

				T& operator[](int i) {
					switch (i){
					case 0:
						return x;
						break;
					case 1:
						return y;
						break;
					case 2:
						return z;
						break;
					}
				}

				inline Vector3<T> operator +(const Vector3<T>& right){
					return Vector3(this->x + right.x, this->y + right.y, this->z + right.z);
				}

				inline Vector3<T>& operator +=(const Vector3<T>& right){
					*this = this + right;
					return *this;
				}

				inline T angle(Vector3<T> other){
					return acos((this->dot(other)) / (this->magnitude() * other.magnitude()));
				}

				inline Vector3<T> componentProduct(const Vector3<T>& vector) const{
					return Vector3(x * vector.x, y* vector.y, z * vector.z);
				}

				inline Vector3<T>& componentProductUpdate(const Vector3<T>& vector){
					x *= vector.x;
					y *= vector.y;
					z *= vector.z;
					return *this;
				}

				inline Vector3<T> vectorProduct(const Vector3<T>& vector) const{
					return Vector3(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
				}

				inline void makeOrthonormalBasis(Vector3<T> *a, Vector3<T> *b, Vector3<T> *c){
					a->normalize();
					(*c) = (*a) % (*b);
					if (c->magnitudeSqr() == 0.0) return;
					c->normalize();
					(*b) = (*c) % (*a);
				}

				inline Vector3<T> operator -(const Vector3<T>& right){
					return Vector3(this->x - right.x, this->y - right.y, this->z - right.z);
				}
				
				inline Vector3<T>& operator -=(const Vector3<T>& right){
					*this = this - right;
					return *this;
				}

				inline Vector3<T> operator*(T right){
					return Vector3(this->x * right, this->y*right, this->z*right);
				}

				inline Vector3<T>& operator*=(T right){
					*this = this * right;
					return *this;
				}

				inline Vector3<T> operator*(const Vector3& vector) const{
					return this->dot(vector);
				}

				inline Vector3<T>& operator%=(const Vector3<T>& vector){
					*this = this % vector;
					return *this;
				}

				inline Vector3<T> operator%(const VEctor3& vector) const{
					return this->vectorProduct(vector);
				}

				inline Vector3<T> operator / (T right){
					return Vector3<T>(this->x / right, this->y / right, this->z / right);
				}

				inline Vector3<T>& operator/=(T right){
					*this = this / right;
					return *this;
				}

				inline bool operator == (const Vector3<T>& right){
					return this->x == right.x && this->y == right.y && this->z == right.z;
				}

				inline bool operator != (const Vector3<T>& right){
					return !(this == right);
				}
				
			public:
				T x;
				T y;
				T z;
			}; 

			typedef Vector3<int> Vector3i;
			typedef Vector3<float> Vector3f;
			typedef Vector3<unsigned int> Vector3u;
		}
	}
}