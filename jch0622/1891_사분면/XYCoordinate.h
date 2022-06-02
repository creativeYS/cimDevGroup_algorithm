#ifndef XYCOORDINATE_H
#define XYCOORDINATE_H

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

#endif