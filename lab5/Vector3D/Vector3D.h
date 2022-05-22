#pragma once
#include "pch.h"

class Vector3D
{
public:
	// ������������ ������� ������
	Vector3D();

	// ������������ ������ � ��������� ������������
	Vector3D(double x0, double y0, double z0);

	// ���������� ����� �������
	double GetLength() const;

	// ������ ������ � �������� ������
	Vector3D const operator-() const;
	Vector3D const operator+() const;
	Vector3D const operator+(Vector3D const& otherVector) const;
	Vector3D const operator-(Vector3D const& otherVector) const;
	Vector3D& operator+=(Vector3D const& vector);
	Vector3D& operator-=(Vector3D const& vector);
	Vector3D operator*(double scalar) const;
	Vector3D operator/(double scalar) const;
	Vector3D& operator*=(double scalar);
	Vector3D& operator/=(double scalar);
	bool operator==(Vector3D const& otherVector) const;
	bool operator!=(Vector3D const& otherVector) const;
	friend std::istream& operator>>(std::istream& inputStream, Vector3D& vector);
	friend std::ostream& operator<<(std::ostream& outputStream, Vector3D const& vector);

	bool IsValid() const;

	// � ������ ������ ������ ����� ������� ����������
	double x, y, z;
};

Vector3D const operator*(double scalar, Vector3D const& vector);

double DotProduct(Vector3D const&, Vector3D const&);
Vector3D CrossProduct(Vector3D const& vector1, Vector3D const& vector2);
Vector3D Normalize(Vector3D const& vector);