#pragma once
#include "headers.h"
#include <d2d1.h>

/// <summary>
/// ��� Ŭ����
/// ���� �ۼ��� : 2023/07/24
/// ���� �ۼ��� : 2023/07/27
/// �ۼ��� : ����ȯ
/// 
/// ��� ������ ���� Ŭ����
/// ���Ŀ� D2D_MATRIX_4X4 �� ����
/// D2D_MATRIX_4X4�� ����ü���� �پ��� ������ ������ ��� ����
/// �̿� �ش� Ŭ���� ����
/// 
/// �� Ŭ������ �����Ǵ� ��� ����� �������
/// 
/// ���� �� �׵����ȭ �Ͽ� ����
/// ��� ���꿡 ���� �Լ� ����
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

	// �׵���� �����
	void Setidentity();

	D2D_MATRIX_3X2_F ConvertD2D();

	// ��� �����
	std::vector<float>& operator[](int _index);
	const std::vector<float>& operator[](int _index) const;

	Matrix operator+(const Matrix& _other);
	Matrix operator+(const int _other);

	Matrix operator*(const Matrix& _other);
	Matrix operator*(const int _other);
	Vector2 operator*(const Vector2& _matrix) const;

	void operator*=(const Matrix& _other);
};

