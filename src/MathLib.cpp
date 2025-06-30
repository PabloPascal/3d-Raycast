#include "../headers/MathLib.h"
#include <iostream>



namespace myMATH {

	float scalarProd(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	//matrix
	Matrix2x2::Matrix2x2() {
		alloc();
	}


	Matrix2x2::Matrix2x2(float a11, float a12, float a21, float a22) {
		alloc();

		m[0][0] = a11;
		m[0][1] = a12;
		m[1][0] = a21;
		m[1][1] = a22;
	}

	void Matrix2x2::operator=(const Matrix2x2& other_m) {
		m = other_m.m;
	}

	Matrix2x2 Matrix2x2::operator*(const Matrix2x2& other_m) const
	{
		Matrix2x2 temp;
		
		temp.m[0][0] = m[0][0] * other_m.m[0][0] + m[0][1] * other_m.m[1][0];
		temp.m[0][1] = m[0][0] * other_m.m[0][1] + m[0][1] * other_m.m[1][1];
		temp.m[1][0] = m[1][0] * other_m.m[0][0] + m[1][1] * other_m.m[1][0];
		temp.m[1][1] = m[1][0] * other_m.m[0][1] + m[1][1] * other_m.m[1][1];

		return temp;
	}

	Matrix2x2 Matrix2x2::operator*(float s) const {
		Matrix2x2 temp(m[0][0]*s, m[0][1]*s, m[1][0]*s, m[1][1]*s);
		return temp;
	}


	Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other_m) const
	{
		Matrix2x2 temp;
	
		temp.m[0][0] = m[0][0] + other_m.m[0][0];
		temp.m[0][1] = m[0][1] + other_m.m[0][1];
		temp.m[1][0] = m[1][0] + other_m.m[1][0];
		temp.m[1][1] = m[1][1] + other_m.m[1][1];

		return temp;

	}

	float Matrix2x2::operator()(int i, int j) const { return m[i][j]; }

	float& Matrix2x2::operator()(int i, int j) { return m[i][j]; }

	sf::Vector2f Matrix2x2::operator*(const sf::Vector2f& vec) const
	{
		
		return sf::Vector2f{ m[0][0] * vec.x + m[0][1] * vec.y,
				 m[1][0] * vec.x + m[1][1] * vec.y};

	}


	Matrix2x2::Matrix2x2(const Matrix2x2& _m) {
		alloc();

		m = _m.m;
	}

	void Matrix2x2::alloc() {
		m.resize(2);
		m[0].resize(2);
		m[1].resize(2);
	}

	Matrix2x2 inverseMatrix(const Matrix2x2& mat) {

		float det = mat(0, 0)*mat(1,1) - mat(1,0) * mat(0,1);

		std::cout << "det = " << det << "\n";

		Matrix2x2 new_mat(mat(1,1), -mat(0,1), -mat(1,0), mat(0,0));

		return new_mat * (1/det);


	}

}