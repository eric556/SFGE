#pragma once
#include <iostream>
#include <string>
#include "Vector2.h"

namespace SFGE{
	namespace Physics{
		namespace Math{
			/*! Templated 3D vector class.*/
			template<typename T>
			class Vector3{
			public:
				/*! Constructs the vector with 0 for x, y and z.*/
				inline Vector3() :x(0), y(0), z(0){}

				/*! Constructor taking in 2 types (Preferably numbers) and setting them to x, y and z.
					\param X a number.
					\param Y a number.
					\param Z a number
				*/
				inline Vector3(T X, T Y, T Z) : x(X), y(Y), z(Z){}
				/*! Constructs based on x and y setting z to 0
					\param X a number
					\param Y a number
				*/
				inline Vector3(T X, T Y) : x(X), y(Y), z(0){}

				/*!Constructor that creates a vector from another vector so long as the second vectors type has a conversion to this vectors type.
					\param vector with type that is convertable to this vector.
				*/
				template<typename U>
				inline Vector3(const Vector3<U>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z)){}

				/*! Constructs a 3D vector based on a 2D vector setting z to 0
					\param vector 2D vector
				*/
				template<typename U>
				inline Vector3(const Vector2<U>& vector){
					Vector3<U> temp();
					temp.x = vector.x;
					temp.y = vector.y;
					Vector3(temp);
				}

				/*! Takes the dot product of this vector and another vector.
					\param other another vector.
					\return a number of the same type as the vector.
				*/
				inline T dot(const Vector3<T>& other){
					return this->x * other.x + this-> * other.y + this->z * other.z;
				}

				/*! Finds the magnitude of the vector.
					\return the magnitude of the vector as the type of the vector.
				*/
				inline T magnitude(){
					return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
				}

				/*! Finds the magnitude of the vector without square rooting (Not an accurate representation of magnitude. Just meant to help with preformance).
					\return not square rooted magnitude as the type of the vector.
				*/
				inline T magnitudeSqr(){
					return std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2);
				}

				/*! Normalizes the vector.
					\return a pointer to the vector.
				*/
				inline Vector3<T>& normalize(){
					*this /= this->magnitude();
					return *this;
				}

				/*! Truncate the vector magnitude to a max value.
					\param max maximum value of the vectors magntude.
					\return a pointer to the vector.
				*/
				inline Vector3<T>& truncate(T max){
					if (this->magnitude() > max){
						this->x = (this->normalize() * max).x;
						this->y = (this->normalize() * max).y;
						this->z = (this->normalize() * max).y;
					}
					return *this
				}
				
				/*! Inverts the vector
					\return a pointer to the vector
				*/
				inline Vector3<T>& invert(){
					this->x = -x;
					this->y = -y;
					this->z = -z;
					return *this;
				}

				/*! Sets all components to 0
					\return pointer to the vector
				*/
				inline Vector3<T>& clear(){
					this->x = 0;
					this->y = 0;
					this->z = 0;
					return *this;
				}

				/*! Use to make a string out of the vector in form "x, y, z".
					\return std::string in form "x, y, z".
				*/
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

				/*! Adds a vector to this vector and then sets this vector to the sum.
				\param right vector to add.
				\return a pointer to the vector.
				*/
				inline Vector3<T>& operator +=(const Vector3<T>& right){
					this->x += right.x;
					this->y += right.y;
					this->z += right.z;
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

				/*! Subtract two vectors.
					\param right vector to subtract.
					\return vector that is the difference of the two vectors.
				*/
				inline Vector3<T> operator -(const Vector3<T>& right){
					return Vector3(this->x - right.x, this->y - right.y, this->z - right.z);
				}
				
				/*! Subtracts a vector from this vector and then sets this vector to the diffrence.
					\param right vector to subtract.
					\return a pointer to the vector.
				*/
				inline Vector3<T>& operator -=(const Vector3<T>& right){
					this->x -= right.x;
					this->y -= right.y;
					this->z -= right.z;
					return *this;
				}

				inline Vector3<T> operator*(T right){
					return Vector3(this->x * right, this->y*right, this->z*right);
				}

				inline Vector3<T>& operator*=(T right){
					this->x *= right;
					this->y *= right;
					this->z *= right;
					return *this;
				}

				inline Vector3<T> operator*(const Vector3& vector) const{
					return this->dot(vector);
				}

				inline Vector3<T>& operator%=(const Vector3<T>& vector){
					*this = this % vector;
					return *this;
				}

				inline Vector3<T> operator%(const Vector3& vector) const{
					return this->vectorProduct(vector);
				}

				inline Vector3<T> operator / (T right){
					return Vector3<T>(this->x / right, this->y / right, this->z / right);
				}

				inline Vector3<T>& operator/=(T right){
					*this = *this / right;
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