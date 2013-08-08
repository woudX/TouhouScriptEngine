#ifndef _H_POINT2F
#define _H_POINT2F

class Point2d
{
public:
	Point2d();
	Point2d(double _x, double _y);
	Point2d(const Point2d& rhs);

	double x;
	double y;

	bool operator== (const Point2d& rhs) const;
	bool operator!= (const Point2d& rhs) const;
	
	Point2d operator-	() const;
	Point2d operator+	(const Point2d& rhs) const;
	Point2d operator-	(const Point2d& rhs) const;
	Point2d operator*	(double a) const;
	Point2d operator/	(double a) const;
	Point2d operator+=	(const Point2d& rhs) const;
	Point2d operator-=	(const Point2d& rhs) const;
	
	double distance(const Point2d& rhs);
	
	static Point2d origin;
};


#endif // !_H_POINT2F
