/* 백준 14681 사분면 고르기 */

#include <iostream>
using namespace std;

class   XYCoordinate
{
    private:
        int     x;
        int     y;
        int     quadrant;

        int     findQuadrant() const;

    public:
        XYCoordinate();
        XYCoordinate(int const & x, int const & y);
        XYCoordinate(XYCoordinate const & src);
        ~XYCoordinate();

        XYCoordinate &  operator=(XYCoordinate const & rhs);

        int     getX() const;
        int     getY() const;
        int     getQuadrant() const;

        void    setX(int const & x);
        void    setY(int const & y);
};

XYCoordinate::XYCoordinate() : x(0), y(0), quadrant(0)
{
    return;
}

XYCoordinate::XYCoordinate(int const & x, int const & y) : x(x), y(y), quadrant(findQuadrant())
{
    return;
}

XYCoordinate::XYCoordinate(XYCoordinate const & src) : x(src.getX()), y(src.getY()), quadrant(src.getQuadrant())
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
    this->quadrant = rhs.getQuadrant();
    return *this;
}

int XYCoordinate::getX() const
{
    return this->x;
}

int XYCoordinate::getY() const
{
    return this->y;
}

int XYCoordinate::getQuadrant() const
{
    return this->quadrant;
}

void    XYCoordinate::setX(int const & x)
{
    this->x = x;
    return;
}

void    XYCoordinate::setY(int const & y)
{
    this->y = y;
    return;
}

int    XYCoordinate::findQuadrant() const
{
    if (x > 0 && y > 0)
    {
        return 1;
    }
    else if (x < 0 && y > 0)
    {
        return 2;
    }
    else if (x < 0 && y < 0)
    {
        return 3;
    }
    else if (x > 0 && y < 0)
    {
        return 4;
    }
    return 0;
}

int main(void)
{
    int x, y;
    cin >> x >> y;

    XYCoordinate    xyc(x, y);
    cout << xyc.getQuadrant();
}