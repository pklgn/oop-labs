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
	*this += -vector;

	return *this;
}

Vector3D Vector3D::operator*(double scalar) const
{
	return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D const operator*(double scalar, Vector3D const& vector)
{
	return vector * scalar;
}


Vector3D Vector3D::operator/(double scalar) const
{
	if (scalar == 0)
	{
		return Vector3D(x > 0 ? INFINITY : -INFINITY,
			y > 0 ? INFINITY : -INFINITY,
			z > 0 ? INFINITY : -INFINITY);
	}

	return Vector3D(x / scalar, y / scalar, z / scalar);
}

Vector3D& Vector3D::operator*=(double scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3D& Vector3D::operator/=(double scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

bool Vector3D::operator==(Vector3D const& otherVector) const
{
	return (std::abs(x - otherVector.x) <= DBL_EPSILON)
		&& (std::abs(y - otherVector.y) <= DBL_EPSILON)
		&& (std::abs(z - otherVector.z) <= DBL_EPSILON);
}

bool Vector3D::operator!=(Vector3D const& otherVector) const
{
	return !(*this == otherVector);
}

bool Vector3D::IsValid() const
{
	return (this->x != -INFINITY &&
		this->y != -INFINITY &&
		this->z != -INFINITY);
}

std::istream& operator>>(std::istream& inputStream, Vector3D& vector)
{
	double x, y, z;

	if ((inputStream >> x) && (inputStream.get() == ',') &&
		(inputStream >> y) && (inputStream.get() == ',') &&
		(inputStream >> z))
	{
		vector = Vector3D(x, y, z);
	}
	else
	{
		inputStream.setstate(std::ios_base::failbit | inputStream.rdstate());
	}

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, Vector3D const& vector)
{
	outputStream << vector.x << ", " << vector.y << ", " << vector.z;

	return outputStream;
}

double DotProduct(Vector3D const& vector1, Vector3D const& vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

Vector3D CrossProduct(Vector3D const& vector1, Vector3D const& vector2)
{
	return Vector3D(vector1.y * vector2.z - vector1.z * vector2.y,
		vector1.z * vector2.x - vector1.x * vector2.z,
		vector1.x * vector2.y - vector1.y * vector2.x);
}

Vector3D Normalize(Vector3D const& vector)
{
	return vector / vector.GetLength();
}