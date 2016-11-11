#pragma once
#include <string>
namespace SFGE{
	namespace Physics{
		namespace Math{
			/*! A templated Matrix class
			*/
			template<typename T>
			class Matrix{
			public:
				/*! Default constructor that sets the matrix to a 1 by 1 with 0 as the default value
				*/
				inline Matrix(){
					p.resize(1);
					p[0].resize(1);
				}
				/*! Constructor that sets the matrix to a m by n with 0 as the default values
				\param m rows
				\param n columns
				*/
				inline Matrix(int m, int n){
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
				/*! Sets the value given a std::vector<std::vector<T>>
				\param vec values to set
				*/
				inline void SetValue(std::vector<std::vector<T>> vec){
					for (int i = 0; i < GetSize().x; i++){
						for (int j = 0; j < GetSize().y; j++){
							//SetValue(i, j, vec[i][j]);
							this[i][j] = vec[i][j];
						}
					}
				}
				/*! Creates a string from the matrix
				\return a string in form "value_at[0][0], value_at[0][1], ... value_at[amount of rows][ amount of columns]
				*/
				inline std::string to_str(){
					std::string finalString = "";
					for (int i = 0; i < p.size(); i++){
						for (int j = 0; j < p[i].size(); j++){
							finalString += (std::to_string(p[i][j]) + ", ");
							if (j == p[i].size() - 1){
								finalString += "\n";
							}
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

				/*! Gets the row
				\param m column number
				\return std::vector<T> holding the values in the row
				*/
				inline std::vector<T> GetRow(int m){
					return p[m];
				}

				/*! Gets the column
				\param n column number
				\return a std::vector<T> holding the values in the column
				*/
				inline std::vector<T> GetColumn(int n){
					std::vector<T> temp;
					for (int i = 0; i < GetSize().x; i++){
						temp.push_back(p[i][n]);
					}
					return temp;
				}

				/*! Transpose the matrix (Switches rows and columns) and return the result
				\return the result of the transpose
				*/
				inline Matrix<T> Transpose(){
					Matrix<T> temp(GetSize().y, GetSize().x);
					for (int i = 0; i < temp.GetSize().x; i++){
						for (int j = 0; j < temp.GetSize().y; j++){
							//temp.SetValue(i, j, this->GetValue(j, i));
							temp[i][j] = this[i][j];
						}
					}
					return temp;
				}
				/*! Transposes the matrix (Switches rows and columns) and set to self
				\return pointer to the matrix
				*/
				inline Matrix<T>& TransposeSelf(){
					*this = this->Transpose();
					return *this;
				}

				/*! Get the determinant of the matrix if it is a 1 by 1, 2 by 2, or 3 by 3
				\return the determinant if it is 1 by 1, 2 by 2, or 3 by 3. Otherwise returns null.
				*/
				inline T Determinant(){
					if (GetSize().x == 1 && GetSize().y == 1){
						return this[0][0];
					}
					else if (GetSize().x == 2 && GetSize().y == 2){
						return (this[0][0] * this[1][1] - this[0][1] * this[1][0]);
					}
					else if (GetSize().x == 3 && GetSize().y == 3){
						std::vector<T> u = GetRow(0);
						std::vector<T> v = GetRow(1);
						std::vector<T> w = GetRow(2);
						return (u[0] * (v[1] * w[2] - v[2] * w[1]) + u[1] * (v[2] * w[0] - v[0] * w[2]) + u[2] * (v[0] * w[1] - v[1] * w[0]));
					}
					else{
						return NULL;
					}
				}

				std::vector<T>& operator[](int i){
					return p[i];
				}

				/*! Adds two matricies and returns the sum
				\param right matrix to add
				\return a matrix that is the sum of the 2 matricies
				*/
				inline Matrix<T> operator+(Matrix<T>& right){
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

					Matrix<T> mat(m, n);
					for (int i = 0; i < GetSize().x; i++){
						for (int j = 0; j < GetSize().y; j++){
							//mat.SetValue(i, j, this[i][j]);
							mat[i][j] = this[i][j];
						}
					}

					for (int i = 0; i < right.GetSize().x; i++){
						for (int j = 0; j < right.GetSize().y; j++){
							//mat.SetValue(i, j, right[i][j] + mat[i][j]);
							mat[i][j] = right[i][j] + mat[i][j];
						}
					}

					return mat;
				}

				/*! Adds two matricies and sets itself to the sum
				\param right matrix to add
				\return a pointer to the matrix
				*/
				inline Matrix<T>& operator+=(Matrix<T>& right){
					*this = this + right;
					return *this;
				}

				/*! Subtracts two matricies and returns the difference
				\param right matrix to subtract
				\return a matrix that is the difference of the 2 matricies
				*/
				inline Matrix<T> operator-(Matrix<T>& right){
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

					Matrix<T> mat(m, n);
					for (int i = 0; i < GetSize().x; i++){
						for (int j = 0; j < GetSize().y; j++){
							//mat.SetValue(i, j, GetValue(i, j));
							mat[i][j] = this[i][j];
						}
					}

					for (int i = 0; i < right.GetSize().x; i++){
						for (int j = 0; j < right.GetSize().y; j++){
							//mat.SetValue(i, j, right.GetValue(i, j) - mat.GetValue(i, j));
							mat[i][j] = right[i][j] - mat[i][j];
						}
					}

					return mat;
				}

				/*! Subtracts two matricies and sets itself to the difference
				\param right matrix to subtract
				\return a pointer to the matrix
				*/
				inline Matrix<T> operator-=(Matrix<T>& right){
					*this = this - right;
					return *this;
				}

				/*! Multiplys a matrix by a scalar
				\param scalar scalar to multiply by
				\return a new matrix with the scalar applied
				*/
				inline Matrix<T> operator*(T scalar){
					Matrix<T> mat(GetSize().x, GetSize().y);
					for (int i = 0; i < mat.GetSize().x; i++){
						for (int j = 0; j < mat.GetSize().y; j++){
							//mat.SetValue(i, j, mat.GetValue(i, j) * scalar);
							mat[i][j] = mat[i][j] * scalar;
						}
					}
					return mat;
				}

				/*! Multiplys a matrix by a scalar and sets itself to the result
				\param scalar scalar to multiply by
				\return pointer to the matrix
				*/
				inline Matrix<T>& operator*=(T scalar){
					for (int i = 0; i < GetSize().x; i++){
						for (int j = 0; j < GetSize().y; j++){
							//this->SetValue(i, j, this->GetValue(i, j) * scalar);
							this[i][j] = this[i][j] * scalar;
						}
					}
					return *this;
				}

				/*! Multiplies a matrix by a matrix
				\param right matrix to multiply by
				\return new matrix that is the product of the matricies
				*/
				inline Matrix<T> operator*(Matrix<T>& right){
					Matrix<T> mat(this->GetSize().x, right.GetSize().y);
					for (int i = 0; i < mat.GetSize().x; i++){
						for (int j = 0; j < mat.GetSize().y; j++){
							//mat.SetValue(i, j, dot(GetRow(i), right.GetColumn(j)));
							mat[i][j] = dot(GetRow(i), right.GetColumn(j));
						}
					}
					return mat;
				}

				/*! Multiplies a matrix by a matrix and sets iteslf to the product
				\param right matrix to multiply by
				\return pointer to the matrix
				*/
				inline Matrix<T>& operator*=(Matrix<T>& right){
					*this = this * right;
					return *this;
				}

			private:
				std::vector<std::vector<T>> p;

				T dot(std::vector<T> left, std::vector<T>right){
					T result = 0;
					for (int i = 0; i < left.size(); i++){
						result += (left[i] * right[i]);
					}
					return result;
				}

			};

			typedef Matrix<int> Matrixi;
			typedef Matrix<float> Matrixf;
			typedef Matrix<unsigned int> Matrixu;
		}
	}
}