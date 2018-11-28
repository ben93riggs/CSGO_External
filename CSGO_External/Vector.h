#pragma once
#include <Math.h>
#include <ostream>
#include "Point.h"


using namespace std;

class Vector
{
public:

	float x, y, z;

	Vector(float x = 0, float y = 0, float z = 0);

	float getDistance() const
	{ // square root of: (x2 - x1)^2 + (y2 - y1)^2) = straight line distance in 3D plane
		return
			sqrt(
				pow(x, 2.f) + // square roof of: (x^2 + y^2)
				pow(y, 2.f) +
				pow(z, 2.f)
			);
	}

	Vector NormalizeAngle()
	{
		if (this->y > 180.0f || this->y < -180.0f)
		{
			float ry = this->y / 360.f;
			if (ry < 0.f)
				ry = -ry;

			ry = round(ry);

			if (this->y < 0.f)
				this->y = (this->y + 360.f * ry);
			else
				this->y = (this->y - 360.f * ry);
		}

		if (this->x > 89.0f || this->x < -89.0f)
		{
			float rx = this->x / 360.f;
			if (rx < 0.f)
				rx = -rx;

			rx = round(rx);

			if (this->x < 0.f)
				this->x = (this->x + 360.f * rx);
			else
				this->x = (this->x - 360.f * rx);
		}

		//this->z = 0.f;

		return *this;
	}

	Vector operator = (const float& In)
	{
		this->x = In;
		this->y = In;
		this->z = In;

		return *this;
	}

	Vector operator + (const Vector& In) const
	{
		return Vector(x + In.x, y + In.y, z + In.z);
	}

	Vector operator - (const Vector& In) const
	{
		return Vector(x - In.x, y - In.y, z - In.z);
	}

	Vector operator * (const Vector& In) const
	{
		return Vector(x * In.x, y * In.y, z * In.z);
	}

	Vector operator / (const Vector& In) const
	{
		return Vector(x / In.x, y / In.y, z / In.z);
	}

	Vector operator -= (const Vector& In)
	{
		this->x -= In.x;
		this->y -= In.y;
		this->z -= In.z;

		return *this;
	}

	Vector operator += (const Vector& In)
	{
		this->x += In.x;
		this->y += In.y;
		this->z += In.z;

		return *this;
	}
	
	Vector operator *= (const Vector& In)
	{
		this->x *= In.x;
		this->y *= In.y;
		this->z *= In.z;

		return *this;
	}

	Vector operator /= (const Vector& In)
	{
		this->x /= In.x;
		this->y /= In.y;
		this->z /= In.z;

		return *this;
	}

	Vector operator += (const float& In)
	{
		this->x += In;
		this->y += In;
		this->z += In;

		return *this;
	}

	Vector operator -= (const float& In)
	{
		this->x -= In;
		this->y -= In;
		this->z -= In;

		return *this;
	}

	Vector operator *= (const float& In)
	{
		this->x *= In;
		this->y *= In;
		this->z *= In;

		return *this;
	}

	Vector operator /= (const float& In)
	{
		this->x /= In;
		this->y /= In;
		this->z /= In;

		return *this;
	}

	Vector operator = (const Point& In)
	{
		this->x = In.x;
		this->y = In.y;

		return *this;
	}

	friend ostream& operator<< (ostream& os, const Vector& In)
	{
		os << "(" << In.x << ",\t\t" << In.y << ",\t\t" << In.z << ")";
		return os;
	}

};

inline Vector::Vector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

/*class Vec2
{
public:
float x, y;
Vec2() {};
Vec2(float, float)
{
this->x;
this->y;
}
float calcDistance() const
{ // square root of: (x2 - x1)^2 + (y2 - y1)^2) = straight line distance in 3D plane
return
sqrt(
pow(x, 2) + // square roof of: (x^2 + y^2)
pow(y, 2)
);
}

Vec2 getDelta(Vec2 vec)
{
Vec2 temp;
temp.x = this->x - vec.x;
temp.y = this->y - vec.y;
return temp;
}

float printVec() const
{
return x, y;
}

};*/