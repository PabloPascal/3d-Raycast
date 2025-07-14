#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace myMATH {

	const float PI = 3.1415;


	template <typename T>
	using matrix = std::vector<std::vector<T>>;
	
	
	float scalarProd(const sf::Vector2f& v1, const sf::Vector2f& v2);
	float VectorLen(const sf::Vector2f& v);

	class Matrix2x2 {

		matrix<float> m;

	public:

		Matrix2x2();

		Matrix2x2(const Matrix2x2& _m);

		Matrix2x2(float a11, float a12, float a21, float a22);

		void operator=(const Matrix2x2& other_m);

		Matrix2x2 operator*(const Matrix2x2& other_m) const;

		Matrix2x2 operator*(float) const;

		sf::Vector2f operator*(const sf::Vector2f& vec) const;

		Matrix2x2 operator+(const Matrix2x2& other_m) const;

		float& operator()(int i, int j);

		float operator()(int i, int j) const;

	private:
		void alloc();
	};


	Matrix2x2 inverseMatrix(const Matrix2x2& matrix);


}
