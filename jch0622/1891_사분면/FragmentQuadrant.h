#ifndef FRAGMENTQUADRANT_H
#define FRAGMENTQUADRANT_H

#include "XYCoordinate.h"
#include <string>
using namespace std;

enum XY {X, Y};

class FragmentQuadrant
{
private:
    int             digit;
    string          number;
    XYCoordinate    xy;

    FragmentQuadrant();
    bool            boolXYcoordinate(XY const & axis, int const & quadrant);
    XYCoordinate    findXYCoordinate();
    void    setDigit(int const & digit);
    void    setNumber(string const & number);
    void    setXY(XYCoordinate const & XY);

public:
    FragmentQuadrant(int const & digit, string const & number);
    FragmentQuadrant(FragmentQuadrant const & src);
    ~FragmentQuadrant();

    FragmentQuadrant &  operator=(FragmentQuadrant const & rhs);

    int             getDigit() const;
    string          getNumber() const;
    XYCoordinate    getXY() const;
    void            moveXY(long long const & x, long long const & y);
};

#endif