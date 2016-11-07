#include <string>
#include "Vector2.h"
namespace SFGE{
	namespace Physics{
		namespace Math{
			/*! A templated Matrix class
			*/
			template<typename T>
			class Matrix2{
			public:
				/*! Default constructor that sets the matrix to a 1 by 1 with 0 as the default value
				*/
				inline Matrix2(){
					p.resize(1);
					p[0].resize(1);
				}

				/*! Constructor that sets the matrix to a m by n with 0 as the default values
					\param m rows
					\param n columns
				*/
				inline Matrix2(int m, int n){
					p.resize(m);
					for (int i = 0; i < p.size(); i++){
						p[i].resize(n);
					}
				}

				/*! Sets the value at m, n 
					\param m row
					\param n column
					\param value value to set
				*/
				inline void SetValue(int m, int n, T value){
					p[m][n] = value;
				}

				/*! Creates a string from the matrix
					\return a string in form "value_at[0][0], value_at[0][1], ... value_at[amount of rows][ amount of columns]
				*/
				inline std::string to_str(){
					std::string finalString = "";
					for (int i = 0; i < p.size(); i++){
						for (int j = 0; j < p[i].size(); j++){
							finalString += (std::to_string(p[i][j]) + ", ");
						}
					}
					return finalString;
				}

				/*! Get the size of the matrix
					\return a vector holding the size of the matrix vec.x = m, vec.y = n
				*/
				inline Vector2i GetSize(){
					return Vector2f(p.size(), p[0].size());
				}

				/*! Gets the value at m, n
					\return value at m, n
				*/
				inline T GetValue(int m, int n){
					return p[m][n];
				}

				/*! Adds two matricies and returns the sum
					\param right matrix to subtract
					\return a matrix that is the sum of the 2 matricies
				*/
				inline Matrix2<T> operator+( Matrix2<T>& right){
					int m;
					int n;
					if (GetSize().x < right.GetSize().x)
						m = right.GetSize().x;
					else
						m = GetSize().x;

					if (GetSize().y < right.GetSize().y)
						n = right.GetSize().y;
					else
						n = right.GetSize().x;

					Matrix2<T> mat(m, n);
					for (int i = 0; i < GetSize().x; i++){
						for (int j = 0; j < GetSize().y; j++){
							mat.SetValue(i, j, GetValue(i, j));
						}
					}

					for (int i = 0; i < right.GetSize().x; i++){
						for (int j = 0; j < right.GetSize().y; j++){
							mat.SetValue(i, j, right.GetValue(i, j) + mat.GetValue(i, j));
						}
					}

					return mat;
				}
				/*! Subtracts two matricies and returns the difference
					\param right matrix to subtract
					\return a matrix that is the difference of the 2 matricies
				*/
				inline Matrix2<T> operator-(Matrix2<T>& right){
					int m;
					int n;
					if (GetSize().x < right.GetSize().x)
						m = right.GetSize().x;
					else
						m = GetSize().x;

					if (GetSize().y < right.GetSize().y)
						n = right.GetSize().y;
					else
						n = right.GetSize().x;

					Matrix2<T> mat(m, n);
					for (int i = 0; i < GetSize().x; i++){
						for (int j = 0; j < GetSize().y; j++){
							mat.SetValue(i, j, GetValue(i, j));
						}
					}

					for (int i = 0; i < right.GetSize().x; i++){
						for (int j = 0; j < right.GetSize().y; j++){
							mat.SetValue(i, j, right.GetValue(i, j) - mat.GetValue(i, j));
						}
					}

					return mat;
				}

				inline Matrix2<T> operator*(T scalar){
					Matrix2<T> mat(GetSize().x, GetSize().y);
					for (int i = 0; i < mat.GetSize().x; i++){
						for (int j = 0; j < mat.GetSize().y; j++){
							mat.SetValue(i, j, mat.GetValue(i, j) * scalar);
						}
					}
					return mat;
				}

				inline Matrix2<T>& operator*=(T scalar){
					for (int i = 0; i < GetSize().x; i++){
						for (int j = 0; j < GetSize().y; j++){
							this->SetValue(i, j, this->GetValue(i, j) * scalar);
						}
					}
					return *this;
				}
				
			private:
				std::vector<std::vector<T>> p;
			};

			typedef Matrix2<int> Matrix2i;
			typedef Matrix2<float> Matrix2f;
			typedef Matrix2<unsigned int> Matrix2u;
		}
	}
}