#pragma once

#include "XYCoordinate.h"
#include <string>
using namespace std;

class FragmentQuadrant
{
private:
    int             digit;
    string          number;
    XYCoordinate    xy;

    FragmentQuadrant();

    void    setDigit(int const & digit);
    void    setNumber(string const & number);
    void    setXY(XYCoordinate const & XY);

    bool            boolXCoordinate(int const & quadrant);
    bool            boolYCoordinate(int const & quadrant);
    XYCoordinate    findXYCoordinate();

public:
    FragmentQuadrant(int const & digit, string const & number);
    FragmentQuadrant(FragmentQuadrant const & src);
    ~FragmentQuadrant();

    int             getDigit() const;
    string          getNumber() const;
    XYCoordinate    getXY() const;

    void            moveXY(long long const & x, long long const & y);

    FragmentQuadrant &  operator=(FragmentQuadrant const & rhs);
};

FragmentQuadrant::FragmentQuadrant() {};
FragmentQuadrant::FragmentQuadrant(int const & digit, string const & number) : digit(digit), number(number), xy(findXYCoordinate()) {};
FragmentQuadrant::FragmentQuadrant(FragmentQuadrant const & src) : digit(src.getDigit()), number(src.getNumber()), xy(src.getXY()) {};
FragmentQuadrant::~FragmentQuadrant() {};

int FragmentQuadrant::getDigit() const { return this->digit; };
string  FragmentQuadrant::getNumber() const { return this->number; };
XYCoordinate    FragmentQuadrant::getXY() const { return this->xy; };

void    FragmentQuadrant::setDigit(int const & digit) { this->digit = digit; };
void    FragmentQuadrant::setNumber(string const & number) { this->number = number; };
void    FragmentQuadrant::setXY(XYCoordinate const & xy) { this->xy = xy; };

FragmentQuadrant &  FragmentQuadrant::operator=(FragmentQuadrant const & rhs)
{
    this->digit = rhs.getDigit();
    this->number = rhs.getNumber();
    this->xy = rhs.getXY();
    return *this;
}

bool    FragmentQuadrant::boolXCoordinate(int const & quadrant)
{
    return (quadrant == 1 || quadrant == 4) ? true : false;
}
bool    FragmentQuadrant::boolYCoordinate(int const & quadrant)
{
    return (quadrant == 1 || quadrant == 2) ? true : false;
}

XYCoordinate    FragmentQuadrant::findXYCoordinate()
{
    long long       x = 0;
    long long       y = 0;
    for (int i = 0; i < number.size(); i++)
    {
        int quadrant = number[i] - '0';
        x = (x << 1) + boolXCoordinate(quadrant);
        y = (y << 1) + boolYCoordinate(quadrant);
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

    string fixNumber(number.size(), 0);
    for (long long i = 0; i < number.size(); i++)
    {
        if ((nextX >> i & 1) == 1 && (nextY >> i & 1) == 1)
        {
            fixNumber[i] = '1';
        }
        else if ((nextX >> i & 1) == 0 && (nextY >> i & 1) == 1)
        {
            fixNumber[i] = '2';
        }
        else if ((nextX >> i & 1) == 0 && (nextY >> i & 1) == 0)
        {
            fixNumber[i] = '3';
        }
        else if ((nextX >> i & 1) == 1 && (nextY >> i & 1) == 0)
        {
            fixNumber[i] = '4';
        }
    }
    reverse(fixNumber.begin(), fixNumber.end());
    setNumber(fixNumber);
    setXY(XYCoordinate(x,y));
    return;
}