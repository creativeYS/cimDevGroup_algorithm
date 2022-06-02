#include "XYCoordinate.h"

XYCoordinate::XYCoordinate() : x(0), y(0)
{
    return;
}

XYCoordinate::XYCoordinate(long long const & x, long long const & y) : x(x), y(y)
{
    return;
}

XYCoordinate::XYCoordinate(XYCoordinate const & src) : x(src.getX()), y(src.getY())
{
    return;
}

XYCoordinate::~XYCoordinate()
{
    return;
}

XYCoordinate &  XYCoordinate::operator=(XYCoordinate const & rhs)
{
    this->x = rhs.getX();
    this->y = rhs.getY();
    return *this;
}

long long   XYCoordinate::getX() const
{
    return this->x;
}

long long   XYCoordinate::getY() const
{
    return this->y;
}

void    XYCoordinate::setX(long long const & x)
{
    this->x = x;
    return;
}

void    XYCoordinate::setY(long long const & y)
{
    this->y = y;
    return;
}