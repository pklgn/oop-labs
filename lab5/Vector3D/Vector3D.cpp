#include "pch.h"
#include "Vector3D.h"


constexpr int DEFAULT_VECTOR_POSITION_X = 0;
constexpr int DEFAULT_VECTOR_POSITION_Y = 0;
constexpr int DEFAULT_VECTOR_POSITION_Z = 0;

Vector3D::Vector3D()
	: x(DEFAULT_VECTOR_POSITION_X)
	, y(DEFAULT_VECTOR_POSITION_Y)
	, z(DEFAULT_VECTOR_POSITION_Z)
{	
}

Vector3D::Vector3D(double x0, double y0, double z0)
	: x(x0)
	, y(y0)
	, z(z0)
{
}

double Vector3D::GetLength() const
{
	return std::hypot(x, y, z);
}

Vector3D const Vector3D::operator-() const
{
	return Vector3D(-x, -y, -z);
}

Vector3D const Vector3D::operator+() const
{
	return *this;
}

Vector3D const Vector3D::operator+(Vector3D const& otherVector) const
{
	return Vector3D(x + otherVector.x, y + otherVector.y, z + otherVector.z);
}

Vector3D const Vector3D::operator-(Vector3D const& otherVector) const
{
	return Vector3D(x - otherVector.x, y - otherVector.y, z - otherVector.z);
}

Vector3D& Vector3D::operator+=(Vector3D const& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

Vector3D& Vector3D::operator-=(Vector3D const& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}
