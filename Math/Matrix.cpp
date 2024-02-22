#include "Matrix.h"
#include "Vector2.h"

/// <summary>
/// 최초 생성시 4x4 정방항등행렬
/// </summary>
/// <param name="_size"></param>
Matrix::Matrix(int _size /*= 4*/)
	: size(_size)
	, matrix(_size, std::vector<float>(_size))
{
	Setidentity();
}


Matrix::~Matrix()
{
}

/// <summary>
/// 행렬 데이터를 항등행렬로 변경
/// </summary>
void Matrix::Setidentity()
{
	for (size_t i = 0; i < this->matrix.size(); i++)
	{
		for (size_t j = 0; j < this->matrix[i].size(); j++)
		{
			matrix[i][j] = 0;
			if (i == j)
			{
				matrix[i][j] = 1;
			}
		}
	}
}

/// <summary>
/// 행렬을 D2D에 맞게 바꿔줌
/// </summary>
/// <returns>변환된 D2D행렬</returns>
D2D_MATRIX_3X2_F Matrix::ConvertD2D()
{
	D2D_MATRIX_3X2_F result = { 0, };

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result.m[i][j] = (*this)[i][j];
		}
	}

	result.m[2][0] = (*this)[size - 1][0];
	result.m[2][1] = (*this)[size - 1][1];
	return result;
}

#pragma region operator

std::vector<float>& Matrix::operator[](int _index)
{
	return this->matrix[_index];
}

const std::vector<float>& Matrix::operator[](int _index) const
{
	return this->matrix[_index];
}

Matrix Matrix::operator+(const Matrix& _other)
{
	assert(this->size == _other.size && "diffrent matrix size");

	Matrix temp(this->size);

	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			temp[i][j] = (*this)[i][j] + _other[i][j];
		}
	}

	return temp;
}

Matrix Matrix::operator+(const int _other)
{
	Matrix temp(this->size);
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			temp[i][j] = (*this)[i][j] + _other;
		}
	}
	return temp;
}

Matrix Matrix::operator*(const Matrix& _other)
{
	assert(this->size == _other.size && "diffrent matrix size to muliply");

	Matrix result = _other;
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			float acc = 0.0f;
			for (int k = 0; k < this->size; k++)
			{
				acc += _other[i][k] * (*this)[k][j];
			}
			result[i][j] = acc;
		}
	}
	return result;
}

Matrix Matrix::operator*(const int _other)
{
	Matrix temp(this->size);
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			temp[i][j] = (*this)[i][j] * _other;
		}
	}
	return temp;
}

void Matrix::operator*=(const Matrix& _other)
{
	(*this) = (*this) * _other;
}

// TODO: 최적화
Vector2 Matrix::operator*(const Vector2& _vector) const
{
	Matrix temp;
	temp[3][0] = _vector.x;
	temp[3][1] = _vector.y;

	temp *= (*this);

	return Vector2{ temp[3][0], temp[3][1] };
}

#pragma endregion
