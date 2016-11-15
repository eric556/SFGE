#pragma once
#include <iostream>
#include <string>

namespace SFGE{
	namespace Physics{
		namespace Math{
			/*! Templated 2D vector class.*/
			template <typename T>
			class Vector2{
			public:

				/*! Constructs the vector with 0 for x and y.*/
				inline Vector2() :x(0), y(0){}

				/*! Constructor taking in 2 types (Preferably numbers) and setting them to x and y.
					\param X a number.
					\param Y a number.
				*/
				inline Vector2(T X, T Y) : x(X), y(Y){}

				/*! Constructor that creates a vector from another vector so long as the second vectors type has a conversion to this vectors type.
					\param vector with type that is convertable to this vector.
				*/
				template<typename U>
				inline Vector2(const Vector2<U>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)){}


				T& operator[](int i){
					return ((i > 0) ? y : x);
				}

				/*! Takes the dot product of this vector and another vector.
					\param other another vector.
					\return a number of the same type as the vector.
				*/
				inline T dot(const Vector2<T>& other){
					return this->x * other.x + this->y * other.y;
				}

				/*! Normalizes the vector.
					\return a pointer to the vector.
				*/
				inline Vector2<T> normalize(){
					*this /= this->magnitude();
					return *this;
				}

				/*! Truncate the vector magnitude to a max value.
					\param max maximum value of the vectors magntude.
					\return a pointer to the vector.
				*/
				inline Vector2<T>& truncate(T max){
					if (this->magnitude() > max){
						this->x = (this->normalize() * max).x;
						this->y = (this->normalize() * max).y;
					}
					return *this;
				}

				/*! Turn the vector into a unit vector (vector with magnitude of 1).
					\return a pointer to the vector.
				*/
				inline Vector2<T> unitVector(){
					T magnitude = this->magnitude();
					this->x = this->x / magnitude;
					this->y = this->y / magnitude;
					return *this;
				}

				/*! Finds the angle of the vector.
					\return the angle of the vector as the type of the vector.
				*/
				inline T angle(){
					return std::atan2(this->x, this->y);
				}

				/*! Finds the magnitude of the vector.
					\return the magnitude of the vector as the type of the vector.
				*/
				inline T magnitude(){
					return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
				}

				/*! Finds the magnitude of the vector without square rooting (Not an accurate representation of magnitude. Just meant to help with preformance).
					\return not square rooted magnitude as the type of the vector.
				*/
				inline T magnitudeSqrt(){
					return std::pow(this->x, 2) + std::pow(this->y, 2);
				}

				/*! Use to make a string out of the vector in form "x, y".
					\return std::string in form "x, y".
				*/
				inline const std::string to_str(){
					std::string finalString = "" + std::to_string(this->x) + ", " + std::to_string(this->y);
					return finalString;
				}

				/*! Adds a vector to this vector and then sets this vector to the sum.
					\param right vector to add.
					\return a pointer to the vector.
				*/
				inline Vector2<T>& operator +=(const Vector2<T>& right){
					this->x += right.x;
					this->y += right.y;
					return *this;
				}

				/*! Subtracts a vector from this vector and then sets this vector to the diffrence.
					\param right vector to subtract.
					\return a pointer to the vector.
				*/
				inline Vector2<T>& operator -=(const Vector2<T>& right){
					this->x -= right.x;
					this->y -= right.y;
					return *this;
				}

				/*! Adds two vectors together.
					\param right vector to add.
					\return vector that is the sum of the two vectors.
				*/
				inline Vector2<T> operator+( const Vector2<T>& right){
					return Vector2(this->x + right.x, this->y + right.y);
				}

				/*! Subtract two vectors.
					\param right vector to subtract.
					\return vector that is the difference of the two vectors.
				*/
				inline Vector2<T> operator-( const Vector2<T>& right){
					return Vector2(this->x - right.x, this->y - right.y);
				}

				/*! Subtract two vectors.
					\param right scaler to multiply by. 
					\return vector scaled up by T right.
				*/
				inline Vector2<T> operator*( T right){
					return Vector2(this->x * right, this->y * right);
				}

				/*! Multiply a vector by a scalar and set it to itself.
					\param right scalar to multiply by.
					\return pointer to vector.
				*/
				inline Vector2<T>& operator *=( T right){
					this->x *= right;
					this->y *= right;
					return *this;
				}

				/*! Divide a vector by a scalar.
					\param right scalar.
					\return Vector2<T>, new vector with the scalar applied
				*/
				inline Vector2<T> operator /( T right){
					return Vector2<T>(this->x / right, this->y / right);
				}

				/*! Divide a vector by a scalar and set self to result.
				\param right scalar.
				\return Vector2<T>, new vector with the scalar applied
				*/
				inline Vector2<T>& operator /=( T right){
					this->x /= right;
					this->y /= right;

					return *this;
				}

				/*! Honestly I don't remember why I made this...
				\param right angle.
				\return new vector with some transform applied to it.
				*/
				inline Vector2<T> operator% ( T right){
					T cosine = std::cos(right);
					T sine = std::sin(right);
					T px = x * cosine - y * sine;
					T py = y * sine + y * cosine;
					return Vector2f(px, py);
				}

				/*! Honestly I don't remember why I made this...
					\param right angle.
					\return pointer to vector.
				*/
				inline Vector2<T>& operator%= ( T right){
					T cosine = std::cos(T);
					T sine = std::sin(T);
					T px = x * cosine - y * sine;
					T py = x * sine + y * cosine;

					this->x = px;
					this->y = py;
					return *this;
				}

				/*! Checks equality of vectors using the components of the vector
					\param right vector to check equality with.
					\return bool that is true when the vector components are equal and false when the vector components are not equal.
				*/
				inline bool operator ==(const Vector2<T>& right){
					return (this->x == right.x) && (this->y == right.y);
				}

				/*! Checks equality of vectors using the components of the vector
					\param right vector to check equality with.
					\return bool that is false when the vector components are equal and true when the vector components are not equal.
				*/
				inline bool operator !=( const Vector2<T>& right){
					return (this->x != right.x) || (this->y != right.y);
				}


			//members
			public:
				//! X component of vector
				T x;
				//! Y component of vector
				T y;
			};

			//defining some basic types
			/*! Common Vector Type*/
			typedef Vector2<int> Vector2i;
			/*! Common Vector Type*/
			typedef Vector2<unsigned int> Vector2u;
			/*! Common Vector Type*/
			typedef Vector2<float> Vector2f;

		}
	}
}