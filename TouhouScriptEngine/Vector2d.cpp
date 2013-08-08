#include "stdafx.h"
#include "Point2d.h"
#include "Vector2d.h"
#include "function.h"

Vector2d::Vector2d()
{

}

Vector2d::Vector2d(const Point2d& _first = Point2d::origin, const Point2d& _second = Point2d::origin)
	:first(_first),second(_second)
{

}

Vector2d::Vector2d(const Point2d& _first, double _length, double _degree):first(_first)
{
	second = Point2d(_first.x + _length * cos(reg(_degree)), _first.y + _length * sin(reg(_degree)));
}

bool Vector2d::operator== (const Vector2d& rhs) const
{
	return first == rhs.first && second == rhs.second;
}

bool Vector2d::operator!= (const Vector2d& rhs) const
{
	return !(*this == rhs);
}

Vector2d Vector2d::operator- () const 
{
	return Vector2d(second, first);
}

Vector2d Vector2d::operator+ (const Vector2d& rhs) const
{
	return (Vector2d(first, rhs.second));
}

Vector2d Vector2d::operator- (const Vector2d& rhs) const
{
	return (Vector2d(rhs.second, second));
}

Vector2d Vector2d::operator* (double a) const
{
	return (Vector2d(first, second * a));
}

Vector2d Vector2d::operator/ (double a) const
{
	assert(a != 0 && "Syntax Error(Can't divide zero)");
	return (Vector2d(first, second / a));
}

Vector2d Vector2d::operator+= (const Vector2d& rhs) const
{
	return (*this + rhs);
}

Vector2d Vector2d::operator-= (const Vector2d& rhs) const
{
	return (*this - rhs);
}

double Vector2d::vectorMag()
{
	return first.distance(second);
}