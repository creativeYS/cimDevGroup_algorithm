#include <iostream>

class Point
{
private:
    double x;
    double y;

public:
    Point();
    Point(const double & x, const double & y);
    Point(const Point & src);
    ~Point();

    double getX() const;
    double getY() const;

    static double outerProduct(const Point & p1, const Point & p2);
    static bool isAcross(const Point & pa1, const Point & pa2, const Point & pb1, const Point & pb2);

    Point & operator=(const Point & rhs);
    Point operator-(const Point & rhs) const;

};

Point::Point() : x(0), y(0) {};
Point::Point(const double & x, const double & y) : x(x), y(y) {};
Point::Point(const Point & src) : x(src.getX()), y(src.getY()) {}; 
Point::~Point() {};

double Point::getX() const { return this->x; };
double Point::getY() const { return this->y; };

Point & Point::operator=(const Point & rhs)
{
    this->x = rhs.getX();
    this->y = rhs.getY();
    return *this;
}
Point Point::operator-(const Point & rhs) const
{
    return Point(this->getX() - rhs.getX(), this->getY() - rhs.getY());
}

// function for algorithm
double Point::outerProduct(const Point & p1, const Point & p2)
{
    return p1.getX() * p2.getY() - p2.getX() * p1.getY();
}

bool Point::isAcross(const Point & pa1, const Point & pa2, const Point & pb1, const Point & pb2)
{
    double op1 = Point::outerProduct(pa2 - pa1, pb1 - pa1);
    double op2 = Point::outerProduct(pa2 - pa1, pb2 - pa1);
    if ( (op1 > 0 && op2 < 0) || (op1 < 0 && op2 > 0) )
        return true;
    return false;
}


int main()
{
    Point point[4];
    for (int i = 0; i < 4; i++)
    {
        double x, y;
        std::cin >> x >> y;
        point[i] = Point(x, y);
    }

    std::cout << Point::isAcross(point[0], point[1], point[2], point[3]);
}