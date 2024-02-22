#pragma once
#include "headers.h"
#include <d2d1.h>

/// <summary>
/// 행렬 클래스
/// 최초 작성일 : 2023/07/24
/// 최초 작성일 : 2023/07/27
/// 작성자 : 김형환
/// 
/// 행렬 연산을 위한 클래스
/// 추후에 D2D_MATRIX_4X4 와 연동
/// D2D_MATRIX_4X4는 구조체여서 다양한 정보와 연산을 담기 힘듬
/// 이에 해당 클래스 생성
/// 
/// 이 클래스로 생성되는 모든 행렬은 정방행렬
/// 
/// 생성 시 항등행렬화 하여 제공
/// 행렬 연산에 대한 함수 제공
/// </summary>

class Vector2;

class Matrix
{
public:
	std::vector<std::vector<float>> matrix;
	int size;
public:
	Matrix(int _size = 4);
	~Matrix();

	// 항등행렬 만들기
	void Setidentity();

	D2D_MATRIX_3X2_F ConvertD2D();

	// 행렬 연산들
	std::vector<float>& operator[](int _index);
	const std::vector<float>& operator[](int _index) const;

	Matrix operator+(const Matrix& _other);
	Matrix operator+(const int _other);

	Matrix operator*(const Matrix& _other);
	Matrix operator*(const int _other);
	Vector2 operator*(const Vector2& _matrix) const;

	void operator*=(const Matrix& _other);
};

