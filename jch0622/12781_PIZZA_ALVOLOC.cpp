#include <iostream>

class Point
{
private:
	const double x;
	const double y;
	Point();

public:
	Point(const double & x, const double & y);
	Point(const Point & src);
	~Point();

	double getX() const;
	double getY() const;

	double outerProduct(const Point & point);

	Point operator-(const Point & rhs) const;
};
bool isAcross(const Point & pa1, const Point & pa2, const Point & pb1, const Point & pb2);

Point::Point(const double & x, const double & y) : x(x), y(y) {};
Point::Point(const Point & src) : x(src.getX()), y(src.getY()) {};
Point::~Point() {};

double Point::getX() const { return this->x; };
double Point::getY() const { return this->y; };

// function for algorithm
Point Point::operator-(const Point & rhs) const
{
	return Point(this->getX() - rhs.getX(), this->getY() - rhs.getY());
}

double Point::outerProduct(const Point & point)
{
	return this->getX() * point.getY() - point.getX() * this->getY();
}

bool isAcross(const Point & pa1, const Point & pa2, const Point & pb1, const Point & pb2)
{
	Point pa = pa2 - pa1;
	double op1 = pa.outerProduct(pb1 - pa1);
	double op2 = pa.outerProduct(pb2 - pa1);

	if ((op1 > 0 && op2 < 0) || (op1 < 0 && op2 > 0))
		return true;
	return false;
}

int main()
{
	double x[4], y[4];

	for (int i = 0; i < 4; i++)
		std::cin >> x[i] >> y[i];

	Point point[4] = { {x[0], y[0]}, {x[1], y[1]}, {x[2], y[2]}, {x[3], y[3]} };

	std::cout << isAcross(point[0], point[1], point[2], point[3]);
}