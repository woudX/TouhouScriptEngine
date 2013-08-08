#include "stdafx.h"
#include "Point2d.h"

Point2d Point2d::origin = Point2d(0, 0);

Point2d::Point2d()
{

}

Point2d::Point2d(double _x = 0, double _y = 0):x(_x),y(_y)
{

}

Point2d::Point2d(const Point2d& rhs):x(rhs.x),y(rhs.y)
{

}

bool Point2d::operator== (const Point2d& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

bool Point2d::operator!= (const Point2d& rhs) const
{
	return !(*this == rhs);
}

Point2d Point2d::operator- () const 
{
	return Point2d(-x, -y);
}

Point2d Point2d::operator+ (const Point2d& rhs) const
{
	return Point2d(x + rhs.x, y + rhs.y);
}

Point2d Point2d::operator- (const Point2d& rhs) const
{
	return Point2d(x - rhs.x, y - rhs.y);
}

Point2d Point2d::operator* (double a) const 
{
	return Point2d(x * a, y * a);
}

Point2d Point2d::operator/ (double a) const
{
	assert(a != 0 && "Syntax Error(Can't divide zero)");
	return Point2d(x / a, y / a);
}

Point2d Point2d::operator+= (const Point2d& rhs) const
{
	return *this + rhs;
}

Point2d Point2d::operator-= (const Point2d& rhs) const
{
	return *this - rhs;
}

double Point2d::distance(const Point2d& rhs)
{
	double dx = x - rhs.x;
	double dy = y - rhs.y;
	return (sqrt(dx * dx + dy * dy));
}

