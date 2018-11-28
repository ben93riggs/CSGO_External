#pragma once
class Vector;

class Point
{
public:

	float x, y;

	Point(float x = 0, float y = 0)
	{
		this->x = x;
		this->y = y;
	}

	Point operator + (const Point& In)
	{
		return Point(x + In.x, y + In.y);
	}

	Point operator - (const Point& In)
	{
		return Point(x - In.x, y - In.y);
	}

	Point operator * (const Point& In)
	{
		return Point(x * In.x, y * In.y);
	}

	Point operator / (const Point& In)
	{
		return Point(x / In.x, y / In.y);
	}

	Point operator -= (const Point& In)
	{
		this->x -= In.x;
		this->y -= In.y;

		return *this;
	}

	Point operator += (const Point& In)
	{
		this->x += In.x;
		this->y += In.y;

		return *this;
	}

	Point operator *= (const Point& In)
	{
		this->x *= In.x;
		this->y *= In.y;

		return *this;
	}

	Point operator /= (const Point& In)
	{
		this->x /= In.x;
		this->y /= In.y;

		return *this;
	}

	Point operator += (const float& In)
	{
		this->x += In;
		this->y += In;

		return *this;
	}

	Point operator -= (const float& In)
	{
		this->x -= In;
		this->y -= In;

		return *this;
	}

	Point operator *= (const float& In)
	{
		this->x *= In;
		this->y *= In;

		return *this;
	}

	Point operator /= (const float& In)
	{
		this->x /= In;
		this->y /= In;

		return *this;
	}

	//Point operator = (const Vector& In)
	//{
	//	return Point(In.x, In.y);
	//}

};
