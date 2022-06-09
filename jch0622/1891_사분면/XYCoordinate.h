#pragma once

class XYCoordinate
{
private:
    long long   x;
    long long   y;

public:
    XYCoordinate();
    XYCoordinate(long long const & x, long long const & y);
    XYCoordinate(XYCoordinate const & src);
    ~XYCoordinate();

    XYCoordinate &  operator=(XYCoordinate const & rhs);

    long long   getX() const;
    long long   getY() const;
    void        setX(long long const & x);
    void        setY(long long const & y);
};

XYCoordinate::XYCoordinate() : x(0), y(0) {};
XYCoordinate::XYCoordinate(long long const & x, long long const & y) : x(x), y(y) {};
XYCoordinate::XYCoordinate(XYCoordinate const & src) : x(src.getX()), y(src.getY()) {};
XYCoordinate::~XYCoordinate() {};

XYCoordinate &  XYCoordinate::operator=(XYCoordinate const & rhs)
{
    this->x = rhs.getX();
    this->y = rhs.getY();
    return *this;
}

long long   XYCoordinate::getX() const { return this->x; };
long long   XYCoordinate::getY() const { return this->y; };

void    XYCoordinate::setX(long long const & x) { this->x = x; };
void    XYCoordinate::setY(long long const & y) { this->y = y; };