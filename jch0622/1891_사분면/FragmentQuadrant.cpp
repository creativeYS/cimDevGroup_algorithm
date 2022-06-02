#include "FragmentQuadrant.h"

FragmentQuadrant::FragmentQuadrant()
{
    return;
}

FragmentQuadrant::FragmentQuadrant(int const & digit, string const & number) 
: digit(digit), number(number), xy(findXYCoordinate())
{
    return;
}

FragmentQuadrant::FragmentQuadrant(FragmentQuadrant const & src)
: digit(src.getDigit()), number(src.getNumber()), xy(src.getXY())
{
    return;
}

FragmentQuadrant::~FragmentQuadrant()
{
    return;
}

FragmentQuadrant &  FragmentQuadrant::operator=(FragmentQuadrant const & rhs)
{
    this->digit = rhs.getDigit();
    this->number = rhs.getNumber();
    this->xy = rhs.getXY();
    return *this;
}

int FragmentQuadrant::getDigit() const
{
    return this->digit;
}

string  FragmentQuadrant::getNumber() const
{
    return this->number;
}

XYCoordinate    FragmentQuadrant::getXY() const
{
    return this->xy;
}

void    FragmentQuadrant::setDigit(int const & digit)
{
    this->digit = digit;
    return;
}

void    FragmentQuadrant::setNumber(string const & number)
{
    this->number = number;
    return;
}

void    FragmentQuadrant::setXY(XYCoordinate const & xy)
{
    this->xy = xy;
    return;
}

bool    FragmentQuadrant::boolXYcoordinate(XY const & axis, int const & quadrant)
{
    if (axis == X)
    {
        if (quadrant == 1 || quadrant == 4)
        {
            return true;
        }
    }
    else if (axis == Y)
    {
        if (quadrant == 1 || quadrant == 2)
        {
            return true;
        }
    }
    return false;
}

XYCoordinate    FragmentQuadrant::findXYCoordinate()
{
    long long       x = 0;
    long long       y = 0;
    for (int i = 0; i < number.size(); i++)
    {
        int quadrant = number[i] - '0';
        x = (x << 1) + boolXYcoordinate(X, quadrant);
        y = (y << 1) + boolXYcoordinate(Y, quadrant);
    }
    XYCoordinate    xy(x, y);
    return xy;
}

void    FragmentQuadrant::moveXY(long long const & x, long long const & y)
{
    long long   nextX = this->getXY().getX() + x;
    long long   nextY = this->getXY().getY() + y;
    if (nextX < 0 || nextY < 0)
    {
        setNumber("-1");
        return;
    }
    else if ((nextX >> number.size()) > 0 || (nextY >> number.size()) > 0)
    {
        setNumber("-1");
        return;
    }

    string  fixNumber(number);
    for (long long i = 0; i < number.size(); i++)
    {
        long long   idx = number.size() -1 - i;
        if ((nextX >> i & 1) == 1 && (nextY >> i & 1) == 1)
        {
            fixNumber[idx] = '1';
        }
        else if ((nextX >> i & 1) == 0 && (nextY >> i & 1) == 1)
        {
            fixNumber[idx] = '2';
        }
        else if ((nextX >> i & 1) == 0 && (nextY >> i & 1) == 0)
        {
            fixNumber[idx] = '3';
        }
        else if ((nextX >> i & 1) == 1 && (nextY >> i & 1) == 0)
        {
            fixNumber[idx] = '4';
        }
    }
    
    setNumber(fixNumber);
    setXY(XYCoordinate(x,y));
    return;
}