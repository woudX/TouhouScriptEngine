#ifndef _H_VECTOE2D
#define _H_VECTOE2D

class Vector2d
{
public:
	Point2d first, second;

	Vector2d();
	Vector2d(const Point2d& _first, const Point2d& _second);
	Vector2d(const Point2d& _first, double _length, double _degree);

	bool operator ==(const Vector2d& rhs) const;
	bool operator !=(const Vector2d& rhs) const;

	Vector2d operator-	() const;
	Vector2d operator+	(const Vector2d& rhs) const;
	Vector2d operator-	(const Vector2d& rhs) const;
	Vector2d operator*	(double a) const;
	Vector2d operator/	(double a) const;
	Vector2d operator+=	(const Vector2d& rhs) const;
	Vector2d operator-=	(const Vector2d& rhs) const;

	double	 operator*	(const Vector2d& rhs) const;	// 向量点乘
	double	 vectorMag	();								// 向量求模
};

#endif // !_H_VECTOE2D
